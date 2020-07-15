/*Disk Scheduling 
    -required to simulate both 
        - First come First serve (FCFS) Scheduling Algorithm
        - shortest seek time  fist (SSTF)
    - disk with 800 tracks (0-799)
    -  uses an array as the queue

Main Function:
    - should contain a loop which begins by picking random # between 0 and 5
        -this represents the number of track requests for current file
    -Assume over 10000 file requests
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Global Variables
int QUEUE[1];
int QUEUENUM = 1;


void AddToList();
int FirstComeFirstServe();
int ShortestSeekTimeFirst();

int main(){
    int totalReqs, i = 0;
    int numFileReqs = 0;
    int numTrackReqs = 0; 
    int totalHeadMove = 0;
    int trackNum = 0; // starting postion of the head disk
    float average;
    char choice = 'F';
    int fileReqChoice = 0;
    
    //change to a random number as seed
    int head = 0;
     
    srand(time(0));


    printf("\nEnter F for FSFC and S for SSTF: ");
    scanf("%c", &choice);
     printf("\nEnter Random Seed: ");
    scanf("%d", &head);
    printf("\nEnter number 10, 100, 1000, or 10000 for# of file requests: ");
    scanf("%d", &fileReqChoice);


    QUEUE[0] = head;

    while(numFileReqs < fileReqChoice){
        // #1-5 represents the current number of track requests
        //      for the current file request
        numTrackReqs = (rand() % 5 + 1);
     
        QUEUE[numTrackReqs-1];

        for (i= 0; i < numTrackReqs; i++){
            //generate that number of track requests
            // random number: 0-799
            trackNum = (rand() % 800);
            AddToList(trackNum);
            QUEUENUM++;
        }
        //testing purposes
        /*
        for (i = 0; i < QUEUENUM; i++){
            printf("%d ", QUEUE[i]);
        }
        */
        if (choice == 'F'){
            //printf("\nFSFC chosen\n");
            totalHeadMove += FirstComeFirstServe();
        }
        else if(choice == 'S')
        { 
            //printf("\nSSTF chosen\n");
            totalHeadMove += ShortestSeekTimeFirst();
        }
        else
        {
            printf("Error\n");
        }
        QUEUENUM = 1;

       numFileReqs++; 
    } 
    printf("\nTotal Seek Time: %d\n", totalHeadMove);
    average = totalHeadMove/(float) numFileReqs;
    printf("\nAverage Seek Time: %f\n", average);
    return 0;
}

//first come first serve
int FirstComeFirstServe(){
    int HeadMove = 0;
    int diff = 0;
    int i, j = 0; 
    //cycles through queue
        for(i = 0; i < QUEUENUM - 1;i++){
            for ( j = 1; j < QUEUENUM ; j++)
            {   //adds abosulte differences together
                diff = abs(QUEUE[i] - QUEUE[j]);
                //printf("\nDiff: %d ", diff);
                i++;
                HeadMove += diff;
            } 
        }
        //makes the last track in queue the first number
        QUEUE[0] = QUEUE[QUEUENUM-1];
    return HeadMove;
}

//Shortest Seek Time First
//while 
int ShortestSeekTimeFirst(){
    int headMove = 0;
    int i = 0;
    int j = 0;
    int k = 0;
    int diff = 0;
    int seek = 800;
    int saved = 0;
    int index = 0;

    while (i < QUEUENUM-1)
    {      
        for(j = 1; j < QUEUENUM; j++){

            diff = abs(QUEUE[0]- QUEUE[j]); 
            //printf("\nDiff: %d ", diff);
            if(diff < seek){
                seek = diff;
                saved = QUEUE[j];
                index = j;
            }
        }
        //Adding the seek number to number of head Moves
        headMove += seek;
        for (k  = index ; k < QUEUENUM; k++)
        {
            QUEUE[k] = QUEUE[k+1];
        }
        // making the saved number the new head
        QUEUE[0] = saved;
        QUEUENUM --;
        
        //resetting the seek number
        seek = 800;
    }
    //printf("HeadMove: %d", headMove);
    return headMove;
}

//Adds number to queue
void AddToList(int num){

    QUEUE[QUEUENUM] = num; 
    return;
}