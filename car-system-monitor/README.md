# Sistemas Distribuídos (2022.2)
![Typescript](https://img.shields.io/badge/-TypeScript-000?&logo=TypeScript&=) ![Node.js](https://img.shields.io/badge/-Node.js-000?&logo=node.js)

### Atividade 1 - Supermarket Socket - DSP Protocol
A supermarket delivery system which uses the fictional DSP protocol(_Delivery Supermarket Protocol_). Verify in [supermarket-socket](./supermarket-socket/README.md).

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
_ADDRESS_|`string`|No|Address of the client (default: `admin`).

### Command ORDER
#### Structure
```sh
> order *id* *option* *args*
```

#### Params
Param name|Type|Obligatory|Description
-|-|-|-
_id_|`string`|No*|The id of an order .
_option_|`string ('create'|'remove'|'payment'|'list'|'details')`|Yes|Option to execute over a order. 
_args_|`string|number`|No|Extra option.

#### Examples
```sh
order create *client_uuid*
```
```sh
order add *uuid* *product_id*
```
```sh
order remove *uuid*
```
```sh
order payment *uuid* *value*
```
```sh
order deliver *uuid* *name*
```
```sh
order list
```

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