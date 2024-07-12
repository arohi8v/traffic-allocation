Graph-based Multi-threaded Traffic Management System Goal

This project aims to create the best multi-threaded graph-based (density-based) traffic management system possible, which can effectively control traffic flow in a condensed road network. The system's objectives are to maximize traffic flow throughout the network, minimize congestion, and shorten travel times. The project is going to be carried out in C.


Specific Node Types:
Wait Nodes: Stand in for places where cars line up to receive access tokens before moving forward.
Traffic Nodes: These are sections of road or intersections where access tokens are used to control traffic flow.
Allocation of Access Tokens: In every token allocation cycle, connected wait nodes receive access tokens from traffic nodes.
Allocation takes into account variables including capacity limitations, traffic demand, the state of the flow of traffic, and emergency vehicle priority.

Traffic Flow Management:
Emergency Vehicle Priority: Immediate access tokens are given based on traffic density and priority.
Delays Introduction: Delays are added post-token allocation to mimic real-world traffic conditions.
Capacity Constraints: If a node can't accommodate all vehicles, priorities are recalculated.
Multithreading and Mutex Handling:
Each traffic node operates in a separate thread to boost efficiency.
Mutexes ensure data integrity, especially in wait nodes.
Input Method:
Data is taken from a file named traffic_input.txt, including the adjacency matrix, node capacities, controller nodes, initial allocations, and destination node.

Input Format:
# Adjacency Matrix
<Size>
<Matrix>
# Wait Node Capacities
<Node Label>: <Capacity>
# Traffic Controller Nodes
<Comma-separated Node Labels>
# Initial Traffic Allocation
<Node Label>: <Number of Vehicles>
# Destination Nodes
<Source Node>:<Destination Node>


Output
The program generates various metrics such as average wait times, token allocation durations, throughput, congestion percentages, and traffic density.
