#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
typedef struct{
   int pid,AT,BT,CT,TAT,RT,WT;
}Process;
int find_minIndex(Process P[],int n,int currentTime)
{
    int minIndex = -1;
    int shortestBT = INT_MAX;

    for(int i=0;i<n;i++)
    {
       if(P[i].BT!=0 && P[i].AT <=currentTime)
       {
          if(P[i].BT < shortestBT)
          {
            minIndex =i;
            shortestBT=P[i].BT;
          }
       }
    }
    return minIndex;
}
void SJF(Process P[],int n)
{
    int currentTime=0;
    int totaltat =0,totalwt=0,totalrt =0;
    float avgtat=0,avgwt=0,avgrt=0;
    int completed = 0;
    int tempBT[n];
    for(int i=0;i<n;i++)
    {
        tempBT[i] = P[i].BT;
    }
    while(completed < n)
    {
        int minIndex = find_minIndex(P,n,currentTime);
        if(minIndex == -1)
        {
           printf("|%d Idle till %d",currentTime);
           currentTime+=1;
           continue;
        }
        P[minIndex].RT = currentTime - P[minIndex].AT;
        int temp =currentTime;
        currentTime = currentTime + P[minIndex].BT;
        P[minIndex].CT = currentTime;
        P[minIndex].TAT = P[minIndex].CT - P[minIndex].AT;
        P[minIndex].WT = P[minIndex].TAT - P[minIndex].BT;
        totaltat += P[minIndex].TAT;
        totalwt += P[minIndex].WT;
        totalrt += P[minIndex].RT;
        printf("|%d P(%d) %d",temp,P[minIndex].pid,currentTime);
        completed++;
        P[minIndex].BT=0;
    }
    printf("\nObservation table:\n");
    printf("P_ID\tAT\tBt\tCT\tTAT\tWT\tRT\n");
    for(int i=0;i<n;i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",P[i].pid,P[i].AT,tempBT[i],P[i].CT,P[i].TAT,P[i].WT,P[i].RT);
    }
    avgtat = totaltat/n;
    avgwt = totalwt/n;
    avgrt=totalrt/n;
    printf("Avg TAT:%.2f",avgtat);
    printf("Avg WT:%.2f",avgwt);
    printf("Avg RT:%.2f",avgrt);
   
}
int main()
{
    int n;
    printf("Enter the number of process:");
    scanf("%d",&n);
    Process P[n];
    for(int i=0;i<n;i++)
    {
        printf("For process %d",(i+1));
        printf("Enter AT");
        scanf("%d",&P[i].AT);
        printf("Enter BT");
        scanf("%d",&P[i].BT);
        P[i].pid = i+1;
    }
    SJF(P,n);
    return 0;
}
