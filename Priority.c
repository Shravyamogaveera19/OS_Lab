#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
typedef struct{
    int pid,AT,BT,CT,TAT,RT,WT,Priority;
}Process;
int find_minIndex(Process P[],int n,int curTime)
{
    int minPriority =INT_MAX;
    int minIndex=-1;
    for(int i=0;i<n;i++)
    {
        if(P[i].BT>0 && P[i].AT<=curTime)
        {
            if(P[i].Priority < minPriority)
            {
                minPriority = P[i].Priority;
                minIndex =i;
            }
        }
    }
    return minIndex;
}
void Priority(Process P[],int n)
{
    int completed=0;
    int totalTAT=0,totalWT=0,totalRT=0;
    float avgTAT=0,avgWT=0,avgRT=0;
    int minIndex=-1;
    int curTime=0;
    int tempBT[n];
    for(int i=0;i<n;i++)
     tempBT[i]=P[i].BT;
    while(completed != n)
    {
        minIndex=find_minIndex(P,n,curTime);
        if(minIndex == -1)
        {
            printf("|Idle %d",curTime);
            curTime++;
            continue;
        }
        P[minIndex].RT=curTime-P[minIndex].AT;
        curTime+=P[minIndex].BT;
        completed++;
        printf("|%d P(%d) %d",curTime-P[minIndex].BT,P[minIndex].pid,curTime);
        P[minIndex].CT=curTime;
        P[minIndex].TAT=P[minIndex].CT-P[minIndex].AT;
        P[minIndex].WT=P[minIndex].TAT-P[minIndex].BT;
        totalTAT+=P[minIndex].TAT;
        totalWT+=P[minIndex].WT;
        totalRT+=P[minIndex].RT;
        P[minIndex].BT=0;
    }
    printf("Observation table:\n");
    printf("P_ID\tAT\tBt\tCT\tTAT\tWT\tRT\n");
    for(int i=0;i<n;i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",P[i].pid,P[i].AT,tempBT[i],P[i].CT,P[i].TAT,P[i].WT,P[i].RT);
    }
    avgTAT =(float)totalTAT/n;
    avgWT = (float)totalWT/n;
    avgRT=(float)totalRT/n;
    printf("Avg TAT:%.2f",avgTAT);
    printf("Avg WT:%.2f",avgWT);
    printf("Avg RT:%.2f",avgRT);
}
int main()
{
    int n;
    printf("Enter the value of n");
    scanf("%d",&n);
    Process P[n];
    printf("Enter AT BT and Priority");
    for(int i=0;i<n;i++)
    {
      printf("Process %d",(i+1));
      scanf("%d",&P[i].AT);
      scanf("%d",&P[i].BT);
      scanf("%d",&P[i].Priority);
      P[i].pid =i+1;
    }
    Priority(P,n);
    return 0;
}
