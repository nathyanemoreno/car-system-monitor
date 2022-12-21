# Sistemas Distribuídos (2022.2)
![Typescript](https://img.shields.io/badge/-TypeScript-000?&logo=TypeScript&=) ![Node.js](https://img.shields.io/badge/-Node.js-000?&logo=node.js) ![Arduino](https://img.shields.io/badge/Arduino-blue)

### Atividade 3 - Car System Monitor
A system to monitor car accidents which uses a NodeMCU component alongside with an Arduino Mega and a React application to provide information to a NodeJS server via Socket.

## Run locally

Install dependencies:
- Command `yarn install`
or
- Command `npm install`

Server:
- **PRODUCTION**: Command `npm server:start`
- **DEVELOPMENT**: Command `npm run server:dev`

Client:
- **PRODUCTION**: Command `npm run client:start`
- **DEVELOPMENT**: Command `npm run client:dev`

**Obs:** The socket server must be running on the port specified in the file _.env_.

## Protocol commands
**Obs:** The commands of the DSP protocol are _case sensitive_.

### Command CLIENT
#### Structure
```sh
> client register *name* *address*
```

#### Params
Param name|Type|Obligatory|Description
-|-|-|-
_NAME_|`string`|No|Name of the client (default: `admin`).

### Command EXIT
Disconnects the socket client.

#### Structure
```sh
> exit
```

## Contribuitors
<table>
  <tr>
    <td align="center">
      <a href="https://github.com/nathyanemoreno">
        <img src="https://avatars.githubusercontent.com/u/40841909?s=100" width="100px;" alt="Nathyane Moreno"/>
        <br />
        <b>Nathyane Moreno</b>
      </a>
    </td>
  </tr>
</table>