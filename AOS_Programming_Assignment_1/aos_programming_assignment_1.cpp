/**
  * AOS Programming Assignment 1
  * Author: Brihat Ratna Bajracharya
  * Roll No.: 19/075
  * CDCSIT
  */

#include<iostream>
#include<cstdlib>
#include<conio.h>

#define MAX 999999
using namespace std;

int choice = 0;

class cpuschedule {
    int n;
    float burst_time[20], service_time[10];
    float arrival_time[10], w;
    float wait_time[10], total_wait_time, avg_wait_time;
    float turn_around_time[10], total_turn_around_time, avg_turn_around_time;

    public:
        void Getdata();         //Getting the No of processes & burst time
        void Fcfs();            //First come First served Algorithm
        void Sjf();             //Shortest job First Algorithm
        void Priority();        //Priority Algorithm
        void SjfP();            //Shortest job First Algorithm with Preemption
        void RoundRobin();      //Round Robin Algorithm
};

/**
  * Get Data
  */
void cpuschedule::Getdata() {
    int i;
    cout<<"Enter the no of processes: ";
    cin>>n;
    for(i=1;i<=n;i++) {
        cout<<"Enter Arrival time for Process p"<<i<<": ";
        cin>>arrival_time[i];
        cout<<"Enter Burst time for Process p"<<i<<": ";
        cin>>burst_time[i];
        cout<<endl;
    }
}

/**
  * First Come First Serve
  */
void cpuschedule::Fcfs() {
    int i,B[10];
    total_wait_time = 0.0;
    total_turn_around_time = 0.0;

    cout<<endl<<endl<<"FCFS"<<endl<<endl;
    //cout<<"ASSUMES arrival time of all process 'zero'\n"<<endl;

    service_time[1] = 0;
    wait_time[1] = 0;

    turn_around_time[1] = burst_time[1];

    // calculates wait time and turn around time for each process
    for(i=2; i<=n; i++) {
        service_time[i] = service_time[i-1] + burst_time[i-1];
        wait_time[i] = service_time[i] - arrival_time[i];
        if(wait_time[i] < 0) {
            wait_time[i] = 0;
        }
        turn_around_time[i] = burst_time[i] + wait_time[i];
        //cout<<wait_time[i]<<endl;
    }

    // Prints turn around time for each process
    /*for(i=1; i<=n; i++) {
        cout<<"\nTurn around time for process p"<<i<<": ";
        cout<<turn_around_time[i];
    }*/

    //Calculating total waiting and turn around time
    for(i=1; i<=n; i++) {
        total_wait_time = total_wait_time + wait_time[i];
        total_turn_around_time = total_turn_around_time + turn_around_time[i];
    }

    avg_wait_time = total_wait_time / n;
    avg_turn_around_time = total_turn_around_time / n;

    // RESULTS
    cout<<endl<<"Total Waiting Time = "<<total_wait_time<<endl;
    cout<<"Average Waiting Time = "<<avg_wait_time<<endl;
    cout<<endl<<"Total Turn Around Time = "<<total_turn_around_time<<endl;
    cout<<"Average Turn Around Time = "<<avg_turn_around_time<<endl;
}

/**
  * Shortest Job First
  */
void cpuschedule::Sjf(){
    int i, j, temp, B[10];      //here B[] stores the sorted burst time of process.
    total_wait_time = 0.0;
    total_turn_around_time = 0.0;

    cout<<endl<<endl<<"SJF"<<endl<<endl;
    cout<<"ASSUMES arrival time of all process 'zero'\n"<<endl;

    // prints entered burst time
    for(i=1; i<=n; i++) {
        B[i] = burst_time[i];
        //cout<<"\nBurst time for process p"<<i<<": ";
        //cout<<B[i];
    }

    // sorts the process according to the increasing order of burst time i.e bubble sort
    for(i=1; i<=n; i++){
        for(j=i+1; j<=n; j++){
            //If there is a smaller element found on right of the array then swap it.
            if(B[j] < B[i]){
                temp = B[i];
                B[i] = B[j];
                B[j] = temp;
            }
        }
    }

    wait_time[1] = 0;
    turn_around_time[1] = B[1];

    // calculates wait time and turn around time for each process
    for(i=2; i<=n; i++) {
        wait_time[i] = B[i-1] + wait_time[i-1];
        turn_around_time[i] = B[i] + wait_time[i];
        //cout<<wait_time[i]<<endl;
        //cout<<turn_around_time[i]<<endl;
    }

    //calculating Average waiting Time and turn around time
    for(i=1; i<=n; i++) {
        total_wait_time=total_wait_time + wait_time[i];
        total_turn_around_time = total_turn_around_time + turn_around_time[i];
    }

    avg_wait_time = total_wait_time / n;
    avg_turn_around_time = total_turn_around_time / n;

    // RESULTS
    cout<<endl<<"Total Waiting Time = "<<total_wait_time<<endl;
    cout<<"Average Waiting Time = "<<avg_wait_time<<endl;
    cout<<endl<<"Total Turn Around Time = "<<total_turn_around_time<<endl;
    cout<<"Average Turn Around Time = "<<avg_turn_around_time<<endl;
}

/**
  * priority scheduling
  */
void cpuschedule::Priority()
{
    int i, j, B[10], priority[10], temp;
    total_wait_time = 0.0;
    total_turn_around_time = 0.0;

    cout<<endl<<endl<<"PRIORITY"<<endl<<endl;
    //cout<<"ASSUMES arrival time of all process 'zero'\n"<<endl;

    for(i=1;i<=n;i++) {
        B[i]=burst_time[i];
        cout<<" Burst time for process p"<<i<<"= ";
        cout<<B[i];
        cout<<" Enter the priority for process P"<<i<<"= ";
        cin>>priority[i];
    }

    // sorts the process according to priority (lower-value first)
    for(i=1; i<=n; i++){
        for(j=i+1; j<=n; j++){
            if(arrival_time[j] < arrival_time[i]) {
                temp = B[i];
                B[i] = B[j];
                B[j] = temp;

                temp = arrival_time[i];
                arrival_time[i] = arrival_time[j];
                arrival_time[j] = temp;

                temp = priority[i];
                priority[i] = priority[j];
                priority[j] = temp;
            }
            if(arrival_time[j] == arrival_time[i]){
                if(priority[j] < priority[i]){
                    temp = B[i];
                    B[i] = B[j];
                    B[j] = temp;

                    temp = arrival_time[i];
                    arrival_time[i] = arrival_time[j];
                    arrival_time[j] = temp;

                    temp = priority[i];
                    priority[i] = priority[j];
                    priority[j] = temp;
                }
            }
        }
    }

    /*for(int i = 1; i <=n;i++){
        cout<<"arrival of p"<<i<<" is "<<arrival_time[i]<<endl;
    }
    for(int i = 1; i <=n;i++){
        cout<<"burst of p"<<i<<" is "<<B[i]<<endl;
    }
    for(int i = 1; i <=n;i++){
        cout<<"priority of p"<<i<<" is "<<priority[i]<<endl;
    }*/

    service_time[1] = 0;
    wait_time[1] = 0;
    turn_around_time[1] = B[1];

    // calculates wait time and turn around time for each process
    for(i=2; i<=n; i++) {
        service_time[i] = service_time[i-1] + B[i-1];
        wait_time[i] = service_time[i] - arrival_time[i];
        /*cout<<"service time of p"<<i-1<<" is "<<service_time[i-1]<<endl;
        cout<<"burst time of p"<<i-1<<" is "<<burst_time[i-1]<<endl;
        cout<<"service time of p"<<i<<" is "<<service_time[i]<<endl;
        cout<<"wait time of p"<<i<<" is "<<wait_time[i]<<endl;
        */
        if(wait_time[i] < 0) {
            wait_time[i] = 0;
        }
        turn_around_time[i] = B[i] + wait_time[i];
        //cout<<"tat time of p"<<i<<" is "<<turn_around_time[i]<<endl;
        //cout<<"wt "<<wait_time[i]<<endl;
        //cout<<"tat "<<turn_around_time[i]<<endl;
    }

    //calculating Average waiting Time and turn around time
    for(i=1; i<=n; i++) {
        total_wait_time=total_wait_time + wait_time[i];
        total_turn_around_time = total_turn_around_time + turn_around_time[i];
    }

    avg_wait_time = total_wait_time / n;
    avg_turn_around_time = total_turn_around_time / n;

    // RESULTS
    cout<<endl<<"Total Waiting Time = "<<total_wait_time<<endl;
    cout<<"Average Waiting Time = "<<avg_wait_time<<endl;
    cout<<endl<<"Total Turn Around Time = "<<total_turn_around_time<<endl;
    cout<<"Average Turn Around Time = "<<avg_turn_around_time<<endl;
}

/**
  * for round robin
  */
void cpuschedule::RoundRobin() {
    int i, j, quantum = 2;
    total_wait_time = 0.0;
    total_turn_around_time = 0.0;

    cout<<endl<<endl<<"ROUND ROBIN"<<endl<<endl;
    cout<<"ASSUMES arrival time of all process 'zero'\n"<<endl;

    // take time quantum from user
    cout<<"Enter time quantum: ";
    cin>>quantum;

    int remaining_burst_time[n];

    for (int i = 1; i <= n; i++)
        remaining_burst_time[i] =  burst_time[i];

    int current_time = 0; // Current time

    // Keep traversing processes in round robin manner
    // until all of them are not done.
    while (1)
    {
        bool done = true;

        // Traverse all processes one by one repeatedly
        for (int i = 1; i <= n; i++)
        {
            // If burst time of a process is greater than 0
            // then only need to process further
            if (remaining_burst_time[i] > 0)
            {
                done = false; // There is a pending process

                if (remaining_burst_time[i] > quantum)
                {
                    // Increase the value of t i.e. shows
                    // how much time a process has been processed
                    current_time += quantum;

                    // Decrease the burst_time of current process
                    // by quantum
                    remaining_burst_time[i] -= quantum;
                }

                // If burst time is smaller than or equal to
                // quantum. Last cycle for this process
                else
                {
                    // Increase the value of t i.e. shows
                    // how much time a process has been processed
                    current_time = current_time + remaining_burst_time[i];

                    // Waiting time is current time minus time
                    // used by this process
                    wait_time[i] = current_time - burst_time[i];

                    // As the process gets fully executed
                    // make its remaining burst time = 0
                    remaining_burst_time[i] = 0;
                }
            }
        }

        // If all processes are done
        if (done == true)
          break;
    }

    // calculates wait time and turn around time for each process
    for(i=1; i<=n; i++) {
        turn_around_time[i] = burst_time[i] + wait_time[i];
        //cout<<"tat "<<turn_around_time[i]<<endl;
    }

    //calculating Average waiting Time and turn around time
    for(i=1; i<=n; i++) {
        total_wait_time=total_wait_time + wait_time[i];
        total_turn_around_time = total_turn_around_time + turn_around_time[i];
    }

    avg_wait_time = total_wait_time / n;
    avg_turn_around_time = total_turn_around_time / n;

    // RESULTS
    cout<<endl<<"Total Waiting Time = "<<total_wait_time<<endl;
    cout<<"Average Waiting Time = "<<avg_wait_time<<endl;
    cout<<endl<<"Total Turn Around Time = "<<total_turn_around_time<<endl;
    cout<<"Average Turn Around Time = "<<avg_turn_around_time<<endl;
}

/**
  * Shortest Job First Pre-emptive
  */
void cpuschedule::SjfP() {
    int i, j;
    total_wait_time = 0.0;
    total_turn_around_time = 0.0;

    cout<<endl<<endl<<"SJF Pre-emptive"<<endl<<endl;

    int remaining_burst_time[n];
    for (int i = 1; i <= n; i++)
        remaining_burst_time[i] =  burst_time[i];

    int complete = 0, current_time = 0, minm = MAX; //some max value
    int shortest = 0, finish_time;
    bool check = false;

    // Process until all processes gets completed
    while (complete != n) {
        // Find process with minimum remaining time among the
        // processes that arrives till the current time`
        for (int i = 1; i <= n; i++) {
            if ((arrival_time[i] <= current_time) && (remaining_burst_time[i] < minm) && remaining_burst_time[i] > 0) {
                minm = remaining_burst_time[i];
                shortest = i;
                check = true;
            }
        }

        if (check == false) {
            current_time++;
            continue;
        }

        // Reduce remaining time by one
        remaining_burst_time[shortest]--;

        // Update minimum
        minm = remaining_burst_time[shortest];
        if (minm == 0)
            minm = MAX;

        // If a process gets completelyexecuted
        if (remaining_burst_time[shortest] == 0) {
            // Increment complete
            complete++;
            check = false;

            // Find finish time of current process
            finish_time = current_time + 1;

            // Calculate waiting time
            wait_time[shortest] = finish_time - burst_time[shortest] - arrival_time[shortest];

            if (wait_time[shortest] < 0)
                wait_time[shortest] = 0;
        }
        // Increment time
        current_time++;
    }

    // calculates wait time and turn around time for each process
    for(i=1; i<=n; i++) {
        turn_around_time[i] = burst_time[i] + wait_time[i];
        //cout<<"tat "<<turn_around_time[i]<<endl;
    }

    //calculating Average waiting Time and turn around time
    for(i=1; i<=n; i++) {
        total_wait_time=total_wait_time + wait_time[i];
        total_turn_around_time = total_turn_around_time + turn_around_time[i];
    }

    avg_wait_time = total_wait_time / n;
    avg_turn_around_time = total_turn_around_time / n;

    // RESULTS
    cout<<endl<<"Total Waiting Time = "<<total_wait_time<<endl;
    cout<<"Average Waiting Time = "<<avg_wait_time<<endl;
    cout<<endl<<"Total Turn Around Time = "<<total_turn_around_time<<endl;
    cout<<"Average Turn Around Time = "<<avg_turn_around_time<<endl;
}

/**
  * MAIN-MENU
  */
void menu(void) {
    system("cls");
    cout<<"AOS Programming Assignment 1"<<endl<<endl<<endl;
    cout<<" MENU"<<endl<<endl;
    cout<<" 1. FCFS"<<endl;
    cout<<" 2. SJF"<<endl;
    cout<<" 3. Priority"<<endl;
    cout<<" 4. Round Robin"<<endl;
    cout<<" 5. SJF-Preemptive"<<endl<<endl;
    cout<<" 9. Exit"<<endl;
    cout<<endl<<" Choice -> ";
    cin>>choice;
}

int main(void) {
    cout<<"AOS Programming Assignment 1"<<endl<<endl<<endl;
    cpuschedule c;
    c.Getdata();

    bool loop = true;

    while(loop == true) {
        switch(choice) {
        case 1:
            c.Fcfs(); getch(); menu();
            break;
        case 2:
            c.Sjf(); getch(); menu();
            break;
        case 3:
            c.Priority(); getch(); menu();
            break;
        case 4:
            c.RoundRobin(); getch(); menu();
            break;
        case 5:
            c.SjfP(); getch(); menu();
            break;
        case 9:
            loop = false;
            break;
        default:
            menu();
        }
    }
    getch();
    return 0;
}
