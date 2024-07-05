#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
void main()

{
    int nodes[10][10];
    int root,nodeCount,nodesAdded[10],nodesAddedCount;
    printf("Enter the node count");
    scanf("%d",&nodeCount);
    for (int i = 0; i < nodeCount; i++)
    {
        nodesAdded[i]=-1;
    }
    
    printf("Enter the cost matrix\n");
    for (int i = 0; i < nodeCount; i++)
    {
        for (int j = 0; j < nodeCount; j++)
        {
           scanf("%d",&nodes[i][j]);
        }
    }
    printf("Enter source node: ");
    scanf("%d", &root);

    nodesAdded[root] = 1;
    nodesAddedCount++;
    while(nodesAddedCount<nodeCount){
        int indexNode;
        int min= INT_MAX;

        for (int i = 0; i < nodeCount; i++)
        { 
                                                                //necessary since -1 will always be less than min.
           if (root!=i & nodes[root][i]<min & nodesAdded[i]!=1 & nodes[root][i]!=-1)
           {
             indexNode=i;
             min=nodes[root][i];
           }
           
        }

        nodesAdded[indexNode] = 1;
        nodesAddedCount++;

        for (int i = 0; i < nodeCount; i++)
        {
             //we dont want to use the revisited nodes...
            if(nodesAdded[i]==1)
            {continue;}
            
            int source_destination=nodes[root][i]==-1?INT_MAX:nodes[root][i];
            int interim_destination=nodes[indexNode][i]==-1?INT_MAX:nodes[indexNode][i];
                                                        //Could give error
            if(source_destination>interim_destination+min & interim_destination!=INT_MAX){
                nodes[root][i]=interim_destination+min;
            }
        }   

    }
    printf("After Link State Routing:\nShortest distance from node %d\nNode\tShortest path cost\n", root);
    for (int i = 0; i < nodeCount; ++i)
        printf("%d\t%d\n", i, nodes[root][i]);
    
} 