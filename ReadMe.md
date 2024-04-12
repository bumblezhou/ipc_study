# ipc study

## How to build

vscode -> CTRL+SHIFT+P -> Cmake::Configure
vscode -> CTRL+SHIFT+P -> Cmake::Build Targe -> all

## How to run

1. fifo with fd:
```bash
[1st terminal]
cd build
./fifo_server

[2nd terminal]
cd build
./fifo_client
```

2. select with fd:
```bash
[1st terminal]
cd build
./select_with_fd_server

[2nd terminal]
cd build
./select_with_fd_client
```

3. socket:
```bash
[1st terminal]
cd build
./socket_server

[2nd terminal]
cd build
./socket_client
```