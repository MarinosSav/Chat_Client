# Chat Client using Network Protocols

Implementation of a basic chat client between two endpoints. Utilizes typical ALP (application-layer protocol), translating ASCII messages to HEX code and attaches an encoded checksum payload for validation. A switch building a topological map of the network is then built and packet routing implemented, detecting if a port is available and routing the packet.
