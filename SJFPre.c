#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
typedef struct{
    int pid,AT,BT,CT,TAT,WT,RT,remainingTime;
}Process;
int find_minIndex(Process P[],int n,int currentTime)
{
   int minIndex =-1;
   int shortestBT = INT_MAX;
   for(int i=0;i<n;i++)
   {
     if(P[i].AT <= currentTime && P[i].remainingTime > 0 )
     {
        if(P[i].remainingTime < shortestBT)
        {
            minIndex = i;
            shortestBT =P[i].remainingTime;
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
    int minIndex;
    for(int i=0;i<n;i++)
    {
        P[i].remainingTime = P[i].BT;
    }
    while(completed<n)
    {
      minIndex = find_minIndex(P,n,currentTime);
      if(minIndex == -1)
      {
         printf("|Idle till %d",currentTime);
         currentTime++;
         continue;
      }
      if(P[minIndex].remainingTime == P[minIndex].BT)
      {
        P[minIndex].RT = currentTime - P[minIndex].AT;
      }
      currentTime ++;
      P[minIndex].remainingTime --;
      printf("|%d P(%d) %d",currentTime-1,P[minIndex].pid,currentTime);
      if(P[minIndex].remainingTime == 0)
      {
        completed ++;
        P[minIndex].CT= currentTime;
        P[minIndex].TAT =P[minIndex].CT -P[minIndex].AT;
        P[minIndex].WT =P[minIndex].TAT -P[minIndex].BT;
        totaltat += P[minIndex].TAT;
        totalwt += P[minIndex].WT;
        totalrt += P[minIndex].RT;
      }
    }
      printf("\nObservation table:\n");
    printf("P_ID\tAT\tBt\tCT\tTAT\tWT\tRT\n");
    for(int i=0;i<n;i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",P[i].pid,P[i].AT,P[i].BT,P[i].CT,P[i].TAT,P[i].WT,P[i].RT);
    }
    avgtat = (float)totaltat/n;
    avgwt = (float)totalwt/n;
    avgrt=(float)totalrt/n;
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