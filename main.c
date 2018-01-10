#include <stdio.h>

//Process struct to create an object with the attributes needed
struct Process {
    int processID;
    int processingTime;
    int waitTime;
    int turnAroundTime;
    int arrivingTime;
};

//This will calculate the Wait Time for each Process according to the algorithm
struct Process * calculateWaitTime (struct Process queue[], int size) {
    for (int i = 1; i < size; i++) {
        queue[i].waitTime = queue[i - 1].processingTime + queue[i - 1].waitTime - queue[i].arrivingTime;
    }
    return queue;
}

//This will calculate how much time take a process to wait and be executed
struct Process * calculateTurnAround (struct Process queue[], int size) {
    for (int i = 0; i < size; i++) {
        queue[i].turnAroundTime = queue[i].processingTime + queue[i].waitTime;
    }
    return queue;
}

//This will give us an average of the waiting time for each process
void averageWaitingTime (struct Process queue[], int size) {
    float average = 0;
    int count = 0;
    for (int i = 0; i < size; i++) {
        average += queue[i].waitTime;
        count++;
    }
    average = average / count;
    printf("Average Waiting Time: %f\n", average);
}

//This function helps to swap items in an array
void swap(struct Process * a, struct Process * b)
{
    struct Process t = *a;
    *a = *b;
    *b = t;
}

//This method aids the pivot for Quick Sort
int partition (struct Process queue[], int low, int high) {
    int pivot = queue[high].arrivingTime;
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (queue[j].arrivingTime <= pivot) {
            i++;
            swap(&queue[i],&queue[j]);
        }
    }
    swap(&queue[i + 1], &queue[high]);
    return (i + 1);
}

//This is a recursive implementation of the Quick Sort
void quickSort (struct Process queue[], int low, int high) {
    if (low < high) {
        int pi = partition(queue, low, high);

        quickSort(queue, low, pi - 1);
        quickSort(queue, pi + 1, high);
    }
}

//First Server First Come scheduling algorithm
void firstServeFirstCome (struct Process queue[], int size) {
    quickSort(queue, 0, size - 1);
    queue = calculateWaitTime(queue, size);
    queue = calculateTurnAround(queue, size);
    averageWaitingTime(queue, size);
}

//Shortest Job Next scheduling algorithm
void shortestJobNext (struct Process queue[], int size) {
    quickSort(queue, 0, size - 1);
    queue = calculateWaitTime(queue, size);
    queue = calculateTurnAround(queue, size);
    averageWaitingTime(queue, size);
}

int main() {
    //Array with processes with their id and processing time
    struct Process queue[] = {{1, 6, 0, 0, 4}, {2, 8, 0, 0, 2}, {3, 7, 0, 0, 0}, {4, 3, 0, 0, 6}, {5, 1, 0, 0, 1}};

    //This will help determine the number of items in the array
    int size = sizeof(queue)/sizeof(struct Process);

    /*
     * Feel free to comment or uncomment the algorithm you want to use.
     * Note that you shouldn't use multiple at the same time since they will
     * affect the same array and you might get biased results
     */
    firstServeFirstCome(queue, size);
    //shortestJobNext(queue, size);
    printf(" ProcessID  Processing Time  Wait Time  Turnaround Time  Arrival Time\n");

    for (int i = 0; i < size; i++) {
        printf("\t %d \t\t\t %d \t\t\t\t %d \t\t\t %d \t\t\t\t %d \n", queue[i].processID, queue[i].processingTime,
               queue[i].waitTime, queue[i].turnAroundTime, queue[i].arrivingTime);
    }
    return 0;
}