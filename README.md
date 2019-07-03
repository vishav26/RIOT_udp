# RIOT_udp

## Steps followed
1. Cloned the RIOT repo from https://github.com/RIOT-OS/RIOT
2. Created a new project as per the instructions

## Sequence of operations

1. First a UDP socket is created. 
2. It is binded to port 4369.
3. Receive the UDP frame from a client.
4. Wait for 1 seocnd.
5. Echo back the frame to client.

## Testing

Testing has been done using netcat. The native machine is connected to port 4369. User types a message. The message is echoed back in 1s. 
