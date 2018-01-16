#include <stdio.h>

//Process struct to create an object with the attributes needed
struct Process {
    int processID;
    int processingTime;
    int waitTime;
    int turnAroundTime;
    int arrivingTime;
    int isProcessing;
};

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

//Shortest Job Next
struct Process * shortestJobNext(struct Process *queue, int size) {
    int iterator = 0;
    int flag = 0;
    int time = 0;   //The time variable to manage waiting, turnaround and incoming processes
    quickSort(queue, 0, size - 1);

    //This while loop is to control the whole scheduling
    while (flag == 0) {
        int temp = iterator;
        queue[iterator].isProcessing = 1;
        int flagProcessingTime = 0;

        //This loop is to make sure every process is considered each unit of time
        for (int k = 0; k < size; k++) {
            //This will make sure that we only affect the process that have actually arrive to the scheduler
            if (queue[k].arrivingTime <= time && queue[k].processingTime > 0) {
                flagProcessingTime++;

                /**
                 * If the process isProcessing, remove processing time.
                 * If is not processing, add to the wait time and check if the process has shorter execution time.
                 * Also, check if the iterator is over a process with 0 processing time and change it.
                 */
                switch (queue[k].isProcessing) {
                    case 1:
                        queue[k].processingTime--;
                        queue[k].turnAroundTime++;
                        break;
                    case 0:
                        queue[k].waitTime++;
                        queue[k].turnAroundTime++;
                        if ((queue[k].processingTime < queue[iterator].processingTime && queue[k].processingTime > 0) ||
                                queue[iterator].processingTime == 0) {
                            queue[iterator].isProcessing = 0;
                            temp = k;
                        }
                        break;
                }
            }
        }
        //Once al processes get to 0, this will finish execution of the scheduler
        if (flagProcessingTime == 0) {
            break;
        }
        time++;

        //This will check if the scheduler should process the same process or switch to a shorter one
        if (iterator != temp) {
            iterator = temp;
        }
    }

    averageWaitingTime(queue, size);

}

int main() {
    //Array with processes with their id and processing time
    struct Process queue[] = {{1, 6, 0, 0, 4, 0}, {2, 8, 0, 0, 2, 0}, {3, 7, 0, 0, 0, 0}, {4, 3, 0, 0, 6, 0}, {5, 1, 0, 0, 1, 0}};

    //This will help determine the number of items in the array
    int size = sizeof(queue)/sizeof(struct Process);

    shortestJobNext(queue, size);
    printf(" ProcessID  Processing Time  Wait Time  Turnaround Time  Arrival Time\n");

    for (int i = 0; i < size; i++) {
        printf("\t %d \t\t\t %d \t\t\t\t %d \t\t\t %d \t\t\t\t %d \n", queue[i].processID, queue[i].processingTime,
               queue[i].waitTime, queue[i].turnAroundTime, queue[i].arrivingTime);
    }
    return 0;
}