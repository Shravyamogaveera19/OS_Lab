#include<stdio.h>
#include<stdlib.h>
typedef struct{
    int pid,AT,BT,CT,TAT,WT,flag;
}Process;
void swap(Process *a,Process *b)
{
    Process temp =*a;
    *a=*b;
    *b = temp;
}
void sort(Process P[],int n)
{
    for(int i=0;i<n-1;i++)
    {
        for(int j=0;j<n-i-1;j++)
        {
           if(P[j].AT>P[j+1].AT)
             swap(&P[j],&P[j+1]);
        }
    }
}
int main()
{
    int n,quantum;
    printf("Enter the number of process");
    scanf("%d",&n);
    Process P[n];
    int tempBT[n];
    printf("Enter AT and BT:");
    for(int i=0;i<n;i++)
    {
        printf("Process:%d\n",i+1);
        scanf("%d%d",&P[i].AT,&P[i].BT);
        tempBT[i] = P[i].BT;
        P[i].pid = i+1;
        P[i].flag =0;
    }
    sort(P,n);
    printf("Enter the time quantum:");
    scanf("%d",&quantum);
    int completed=0,totalTAT=0,totalWT=0,*waitQueue;
    float avgTAT=0,avgWT=0;
    int curIndex =0,curTime =0;
    int rear=0,front=0;
    waitQueue=(int *)malloc(n*sizeof(int));
    waitQueue[rear]=0;
    P[0].flag =1;
    while(completed!=n)
    {
        curIndex = waitQueue[front];
        front=(front+1)%n;
        if(P[curIndex].BT > quantum)
        {
            curTime+=quantum;
            P[curIndex].BT-=quantum;
            printf("|P%d (%d) %d",P[curIndex].pid,quantum,curTime);
        }
        else{
            curTime+=P[curIndex].BT;
            printf("|P%d (%d) %d",P[curIndex].pid,P[curIndex].BT,curTime);
            P[curIndex].BT=0;
            P[curIndex].CT =curTime;
            P[curIndex].TAT = P[curIndex].CT-P[curIndex].AT;
            P[curIndex].WT=P[curIndex].TAT -tempBT[P[curIndex].pid -1];
            totalTAT+=P[curIndex].TAT;
            totalWT+=P[curIndex].WT;
        }
        for(int i=0;i<n && P[i].AT<=curTime;i++)
        {
            if(i==curIndex || P[i].BT==0 ||P[i].flag==1)
            {
                continue;
            }
            rear=(rear+1)%n;
            P[i].flag =1;
            waitQueue[rear]=i;
        }
        if(P[curIndex].BT>0)
        {
            rear=(rear+1)%n;
            waitQueue[rear]=curIndex;
        }
        else{
            completed++;
        }
    }
    printf("Observation table:\n");
    printf("P_ID\tAT\tBt\tCT\tTAT\tWT\n");
    for(int i=0;i<n;i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",P[i].pid,P[i].AT,tempBT[i],P[i].CT,P[i].TAT,P[i].WT);
    }
    avgTAT =(float)totalTAT/n;
    avgWT = (float)totalWT/n;
    printf("Avg TAT:%.2f",avgTAT);
    printf("Avg WT:%.2f",avgWT);
}