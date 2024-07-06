#include<stdio.h>

void main()
{
	int dist[10][10];
	int n;
    int flag;
	printf("Enter number of routers: ");
	scanf("%d",&n);
	printf("Enter cost matrix:\n");
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			scanf("%d",&dist[i][j]);
		}
	}
	
	do{
        flag=0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                for (int k = 0; k < n; k++)
                {
                    if(dist[i][j]>dist[i][k]+dist[k][j])
                    {
                        dist[i][j]=dist[i][k]+dist[k][j];
                        flag=1;
                    }
                }
                
            }
            
        }
        
        
    }while(flag!=0);
	printf("\nDISTANCE VECTOR TABLE\n");
	printf("  | ");
	for(int i=0;i<n;i++)
		printf("%c ",i+65);
	printf("\n--------------\n");
	for(int i=0;i<n;i++)
	{
		printf("%c | ",i+65);
		for(int j=0;j<n;j++)
		{
			printf("%d ",dist[i][j]);
		}
		printf("\n");
	}
}
