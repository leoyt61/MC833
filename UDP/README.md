# HTTP-like API with a terminal interface client in C
## Install
Run the following command to compile the server and client code:
```bash
make all
```
Run the server application providing a port of your choice:
```bash
make run-server PORT=8080
```
On another terminal, export the variables for the ip and port in which the client application should connect with:
```bash
export MC833_P2_ENV_HOST=YOUR_IP
export MC833_P2_ENV_PORT=8080
```
On the same terminal, run the client application:
```bash
make run-client
```
