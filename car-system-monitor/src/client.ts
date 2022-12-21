import './config/dotenv'
import readline from "readline";
import net from "net";

const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout
});

const client = new net.Socket();

const connListener = () => {
  client.on("data", function (data) {
    const response = data.toString();

    console.log(response);
  });
  
  rl.on('line', line => {
    client.write(`${line} \n`);

    if (line === "exit") {
      client.end();
      rl.close();
    }
  });
}


client.connect(Number(process.env.SERVER_PORT), "0.0.0.0", connListener);