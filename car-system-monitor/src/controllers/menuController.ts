import { Socket } from "socket.io";
import { ControllerResponse } from ".";
import menu from "../data/menu.json";

export const menuController = (
  socket: Socket,
  options: string[],
): ControllerResponse<any> => {
  switch (options[1]) {
    case "list":
      return {
        data: menu.products,
      };
    default:
      return { message: "Invalid argument" };
  }
};
