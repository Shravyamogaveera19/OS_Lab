#include<stdio.h>
typedef struct node{
    int pid,at,bt,ct,tat,wt,rt;
}Process;
void fcfs(Process processes[],int n);
int main()
{
    int n;
    printf("Enter the number of processes\n");
    scanf("%d",&n);
    Process processes[n];
    for(int i=0;i<n;i++)
    {
        printf("\nProcess %d\n",(i+1));
        printf("Enter the arrival time and burst time");
        scanf("%d %d",&processes[i].at,&processes[i].bt);
        processes[i].pid=(i+1);
        //printf("\n");
    }
    for(int i=0;i<n-1;i++)
    {
        for(int j=0;j<n-i-1;j++)
        {
            if(processes[j].at>processes[j+1].at)
            {
                Process temp=processes[j];
                processes[j]=processes[j+1];
                processes[j+1]=temp;
            }
        }
    }
    fcfs(processes,n);
    return 0;
}
void fcfs(Process processes[],int n)
{
    int elapsed_time=0;
    float avgwt=0,avgtat=0,avgrt=0;
    int totalwt=0,totaltat=0,totalrt=0;
    printf("Gantt Chart:\n");
    for(int i=0;i<n;i++)
    {
        if(elapsed_time<processes[i].at)
        {
          elapsed_time=elapsed_time+(processes[i].at-elapsed_time);
        }
        int temp=elapsed_time;
        processes[i].rt=elapsed_time-processes[i].at;
        elapsed_time+=processes[i].bt;
        processes[i].ct=elapsed_time;
        processes[i].tat=processes[i].ct-processes[i].at;
        processes[i].wt=processes[i].tat-processes[i].bt;
        printf("|(%d) P%d (%d)",temp,processes[i].pid,elapsed_time);
       // printf("\n");
    }
    printf("Observation table\n");
    printf("PID\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for(int i=0;i<n;i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",processes[i].pid,processes[i].at,processes[i].bt,processes[i].ct,
        processes[i].tat,processes[i].wt,processes[i].rt);
        totaltat+=processes[i].tat;
        totalwt+=processes[i].wt;
        totalrt+=processes[i].rt;
    }
    avgtat=(float)totaltat/n;
    avgwt=(float)totalwt/n;
    avgrt=(float)totalrt/n;

    printf("Average wait time:%.2lf",avgwt);
    printf("Average tat:%.2lf",avgtat);
    printf("Average response time:%.2lf",avgrt);
}