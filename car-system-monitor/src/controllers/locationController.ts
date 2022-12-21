import { Socket } from "socket.io";
import { ControllerResponse } from ".";

export const locationController = (
  socket: Socket,
  options: string[],
): ControllerResponse<any> => {
  switch (options[1]) {
    case "speed":
      return {
      };
    default:
      return { message: "Invalid argument" };
  }
};
