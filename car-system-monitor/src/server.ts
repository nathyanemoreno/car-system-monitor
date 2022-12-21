import { Server, Socket } from "socket.io";
import "./config/dotenv";
import { clientController } from "./controllers/clientController";
import { createServer } from "http";
import net from "net";

interface CarCrashReport {
  didBrakeWork: boolean;
  currentVelocity: number;
  crashVelocity: number;
  highestVelocity: number;
  targetDistance: number;
  isHonking: boolean;
  timestamp: number;
};

const cars = {} as Record<string, CarCrashReport>;

let sockets: Socket[] = [];

const connectionListener = (socket: net.Socket) => {
  socket.on("data", (data: string) => handleSensorData(socket, data));

  socket.on("error", (err: any) => {
    console.log("Caught flash policy server socket error: ");
    console.log(err);
  }
  )
}

const socketServer = net.createServer(connectionListener);
socketServer.listen(5000, "0.0.0.0", function () {
  console.log("Server is running");
});

// SocketIO server
const httpServer = createServer();
const server = new Server(httpServer);

server.on("connection", (socket: Socket) => {
  sockets.push(socket);

  socket.on("data", (data: string) => handleInput(socket, data));

  socket.emit("time-msg", { time: new Date().toString() });

  socket.on("close", () => {
    sockets = sockets.filter((s) => s !== socket);
    console.log("Disconnected");
  });
});

const handleInput = (socket: Socket, data: string) => {
  const request = data.toString().trim();
  const args = request.split(" ");
  let response = {};
  //console.log(socket.id, request);

  // UseCase Controller routes
  switch (args[0]) {
    case "client":
      args.push(socket.id);
      response = clientController(socket, args);
      break;
    case "location":
      const [id, payload] = JSON.parse(args[1]);
      if (!cars[id]) {
        cars[id] = {} as CarCrashReport;
      }
      Object.assign(cars[id], payload);

      console.log(cars);

      break;

    case "exit":
      response = { message: "Disconnected from server." };
      break;
    default:
      response = { message: "Missing or invalid command" };
      break;
  }
  socket.write(JSON.stringify(response));
};


const handleSensorData = (socket: net.Socket, data: string) => {
  const request = data.toString().trim();
  console.log(request);
  const args = JSON.parse(request);
  
  let response = {};

  const [id, payload] = args;
  if (!cars[id]) {
    cars[id] = {} as CarCrashReport;
  }

  const carInfo = {
    currentVelocity:payload.current_velocity ? parseFloat(payload.current_velocity) : cars[id].currentVelocity,
    crashVelocity: payload.crash_velocity ? parseFloat(payload.crash_velocity) : cars[id].crashVelocity,
    highestVelocity: payload.highest_velocity ? parseFloat(payload.highest_velocity) : cars[id].highestVelocity,
    targetDistance: payload.target_distance ? parseFloat(payload.target_distance) : cars[id].targetDistance,
    isHonking: payload.is_honking ? Boolean(payload.is_honking) : cars[id].isHonking,
    timestamp: parseInt(payload.timestamp) || cars[id].timestamp,
  }
  
  Object.assign(cars[id], carInfo);

  console.log(cars);

  socket.write(JSON.stringify(response));
};


httpServer.listen(4000);