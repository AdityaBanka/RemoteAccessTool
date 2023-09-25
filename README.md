This is a windows based project to showcase how dangerous it is to run someone else's code blindly, by implementing the decoySever.c code in any C program, we can in essence takeover control of the target machine. 

This is being accompolished by effectively first establishing a connection with a remote server that is then responsible to send another client file to the 'client' side using a TCP webSocket. This new 'client' file then runs in parallel in the background, maintain a bi-directional connection with the server.
Then from there it can take command to execute in the command line. The new 'client' since is being run by the user, can change registry access such that it is run at startup. The 'client' is also capable to keylog, capture screenshots and also access anyother peripherial input, including and not limited to webCam and microphones.

None of this is logged but can be accessed by the server in live mode if commanded, the server will be eventually hosted on a cloud platform in a container or on a virtual machine.

Below is a step by step timeline for all events as they happen:
1. The server is compiled and executed.
2. The decoy client code is added to the target code.
3. The decoy client is compiled and executed on the target's machine.
4. The decoy client connects with the server.
5. It downloads a 'client' file.
6. Complies and runs it in a seperate process. And terminates its own thread.
7. The 'client' sets registry permission.
8. It then connects to the server and awaits commands, while running in the background.
