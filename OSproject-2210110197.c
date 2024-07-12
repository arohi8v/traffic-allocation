#include <stdio.h>

typedef struct {
    char nodeID;
    int maxCap;
    int numAlloc;
    double totalWait;
} WaitNode;

void calculateAverageWaitTime(WaitNode waitNodes[], int numNodes) {
    double totalWaitTime = 0;
    int totalAllocations = 0;

    for (int i = 0; i < numNodes; i++) {
        totalWaitTime += waitNodes[i].totalWait;
        totalAllocations += waitNodes[i].numAlloc;
    }

    double averageWaitTime = totalWaitTime / totalAllocations;

    printf("Average Wait Time at Nodes:\n");
    for (int i = 0; i < numNodes; i++) {
        printf("Node %c: %.2f seconds\n", waitNodes[i].nodeID, averageWaitTime);
    }
}

typedef struct {
    char nodeID;
    int numAlloc;
    double totalAllocationTime;
} TrafficNode;

void calculateAverageTokenAllocationTime(TrafficNode trafficNodes[], int numNodes) {
    for (int i = 0; i < numNodes; i++) {
        double averageAllocationTime = trafficNodes[i].totalAllocationTime / trafficNodes[i].numAlloc;
        printf("Average Token Allocation Time for Node %c: %.2f seconds\n", trafficNodes[i].nodeID, averageAllocationTime);
    }
}

typedef struct {
    char nodeID;
    double timeToFirstVeh;
} TimeToFirstVehicleNode;

void calculateTimeToDestinationFirstVehicle(TimeToFirstVehicleNode nodes[], int numNodes) {
    for (int i = 0; i < numNodes; i++) {
        printf("Time to Destination for First Vehicle at Node %c: %.2f seconds\n", nodes[i].nodeID, nodes[i].timeToFirstVeh);
    }
}

typedef struct {
    char nodeID;
    double timeToLastVeh;
} TimeToLastVehicleNode;

void calculateTimeToDestinationLastVehicle(TimeToLastVehicleNode nodes[], int numNodes) {
    for (int i = 0; i < numNodes; i++) {
        printf("Time to Destination for Last Vehicle at Node %c: %.2f seconds\n", nodes[i].nodeID, nodes[i].timeToLastVeh);
    }
}

typedef struct {
    char nodeID;
    double totalWaitTime;
    double totalDestTime;
} ThroughputNode;

void calculateAverageThroughput(ThroughputNode nodes[], int numNodes, double totalElapsed) {
    for (int i = 0; i < numNodes; i++) {
        double totalNodeTime = nodes[i].totalWaitTime + nodes[i].totalDestTime;
        double throughput = totalNodeTime / totalElapsed;
        printf("Average Throughput at Node %c: %.2f vehicles per second\n", nodes[i].nodeID, throughput);
    }
}

double calculateOverallAverageTokenAllocationTime(double tokenAllocTimes[], int numNodes) {
    double totalTokenAllocationTime = 0.0;
    
    for (int i = 0; i < numNodes; i++) {
        totalTokenAllocationTime += tokenAllocTimes[i];
    }
    
    double overallAverageTokenAllocationTime = totalTokenAllocationTime / numNodes;
    
    return overallAverageTokenAllocationTime;
}

double calculateCongestionPercentage(int maxCapacities[], int filledCapacities[], int numNodes) {
    int congestedNodes = 0;

    for (int i = 0; i < numNodes; i++) {
        if (filledCapacities[i] >= maxCapacities[i]) {
            congestedNodes++;
        }
    }

    double congestionPercentage = (double) congestedNodes / numNodes * 100;

    return congestionPercentage;
}

double calculateAverageTrafficDensity(int filledCapacities[], int maxCapacities[], int numNodes) {
    double totalDensity = 0;

    for (int i = 0; i < numNodes; i++) {
        double density = (double) filledCapacities[i] / maxCapacities[i];
        totalDensity += density;
    }

    double averageDensity = totalDensity / numNodes;

    return averageDensity;
}

// New function to calculate priority allocation
double calculatePriorityAllocation(int maxCapacities[], int filledCapacities[], int numNodes, double time, double wa, double wf, double w1, double w2) {
    double priority = w1 * time; // Initialize with time factor

    // Density factor calculation
    double densityFactor = 0.0;
    for (int i = 0; i < numNodes; i++) {
        densityFactor += (wa * maxCapacities[i] + wf * maxCapacities[i] + filledCapacities[i]) / maxCapacities[i];
    }
    densityFactor /= numNodes;
    priority += w2 * densityFactor;

    return priority;
}

int main() {
    // Example data for wait nodes
    WaitNode waitNodes[] = {
        {'X', 15, 30, 60.5}, // Modified data
        {'Y', 10, 20, 45.2}, // Modified data
        {'Z', 20, 40, 80.0}, // Modified data
        {'W', 8, 25, 55.0},  // Modified data
        // Add more nodes as needed
    };
    int numWaitNodes = sizeof(waitNodes) / sizeof(waitNodes[0]);

    // Example data for traffic nodes
    TrafficNode trafficNodes[] = {
        {'X', 18, 22.5}, // Modified data
        {'Y', 15, 18.3}, // Modified data
        {'Z', 25, 30.0}, // Modified data
        {'W', 12, 21.8}, // Modified data
        // Add more nodes as needed
    };
    int numTrafficNodes = sizeof(trafficNodes) / sizeof(trafficNodes[0]);

    // Example data for time to first vehicle nodes
    TimeToFirstVehicleNode timeToFirstVehicleNodes[] = {
        {'X', 11.8}, // Modified data
        {'Y', 9.5},  // Modified data
        {'Z', 13.2}, // Modified data
        {'W', 10.7}, // Modified data
        // Add more nodes as needed
    };
    int numFirstVehicleNodes = sizeof(timeToFirstVehicleNodes) / sizeof(timeToFirstVehicleNodes[0]);

    // Example data for time to last vehicle nodes
    TimeToLastVehicleNode timeToLastVehicleNodes[] = {
        {'X', 16.2}, // Modified data
        {'Y', 13.5}, // Modified data
        {'Z', 19.8}, // Modified data
        {'W', 15.4}, // Modified data
        // Add more nodes as needed
    };
    int numLastVehicleNodes = sizeof(timeToLastVehicleNodes) / sizeof(timeToLastVehicleNodes[0]);

    // Example data for throughput nodes
    ThroughputNode throughputNodes[] = {
        {'X', 24.0, 52.5}, // Modified data
        {'Y', 30.0, 61.3}, // Modified data
        {'Z', 35.0, 70.0}, // Modified data
        {'W', 40.0, 78.1}, // Modified data
        // Add more nodes as needed
    };
    int numThroughputNodes = sizeof(throughputNodes) / sizeof(throughputNodes[0]);

    // Example data for token allocation times
    double tokenAllocationTimes[] = {0.12, 0.18, 0.14, 0.17}; // Modified data
    int numTokenAllocationNodes = sizeof(tokenAllocationTimes) / sizeof(tokenAllocationTimes[0]);

    // Example data for congestion calculation
    int maxCapacities[] = {15, 20, 25, 12}; // Modified data
    int filledCapacities[] = {10, 18, 22, 9}; // Modified data
    int numCongestionNodes = sizeof(maxCapacities) / sizeof(maxCapacities[0]);

    // Example data for traffic density calculation
    int filledCapacitiesDensity[] = {10, 18, 22, 9}; // Modified data
    int maxCapacitiesDensity[] = {15, 20, 25, 12};   // Modified data
    int numDensityNodes = sizeof(filledCapacitiesDensity) / sizeof(filledCapacitiesDensity[0]);

    calculateAverageWaitTime(waitNodes, numWaitNodes);
    calculateAverageTokenAllocationTime(trafficNodes, numTrafficNodes);
    calculateTimeToDestinationFirstVehicle(timeToFirstVehicleNodes, numFirstVehicleNodes);
    calculateTimeToDestinationLastVehicle(timeToLastVehicleNodes, numLastVehicleNodes);
    calculateAverageThroughput(throughputNodes, numThroughputNodes, 1000.0); // Example total elapsed time in seconds, replace with actual value

    double overallAvgTokenAllocationTime = calculateOverallAverageTokenAllocationTime(tokenAllocationTimes, numTokenAllocationNodes);
    printf("Overall Average Token Allocation Time: %.2f seconds\n", overallAvgTokenAllocationTime);

    double congestionPercentage = calculateCongestionPercentage(maxCapacities, filledCapacities, numCongestionNodes);
    printf("Percentage of Nodes with Congestion: %.2f%%\n", congestionPercentage);

    double averageTrafficDensity = calculateAverageTrafficDensity(filledCapacitiesDensity, maxCapacitiesDensity, numDensityNodes);
    printf("Average Traffic Density: %.2f%%\n", averageTrafficDensity * 100);

    // Calculate and print priority allocation
    double time = 2.0;                // Modified data
    double wa = 7.0, wf = 7.0, w1 = 0.5, w2 = 0.5; // Modified data
    double priority = calculatePriorityAllocation(maxCapacities, filledCapacities, numCongestionNodes, time, wa, wf, w1, w2);
    printf("Priority Allocation: %.2f\n", priority);

    return 0;
}
