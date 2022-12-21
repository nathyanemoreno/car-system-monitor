import { Socket } from "socket.io";
import crypto from "crypto";
import { Client, ControllerResponse } from ".";
import net from "net"

let client: Client = {};
let clients: Client[] = [{ name: "admin" }];

export function clientController(
  socket: Socket | net.Socket,
  options: string[],
): ControllerResponse<Client> {
  switch (options[1]) {
    case "register":
      //client.address = options.slice(3, options.length).join(" ");
      client.name = options[2];
      //console.log(options[3]);
      
      if (!client.name) {
        //if (!client.name || !client.address) {
        return {
          message: "REGISTER: missing argument: name|address; no client registered;\n Use CREATE command to register a client.",
          error: "MISSING_ARGUMENT",
        };
      }
      clients.push(client);
      client = {};
      return {
        message: `Client #${clients.length} registered successfully`,
        data: clients[clients.length - 1],
      };

    default:
      return { message: "Invalid argument" };
  }
}
