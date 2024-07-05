#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>
#define packetcount 3
int main()
{
    int packets[packetcount],i,rate,bucketSize,remainingSize=0,timeToTransmit,clk,op;
    srand(time(0));
    for (i = 0; i < packetcount; i++)
    {
       packets[i]=(rand()%9+1)*10;
    }
    printf(" \nEnter the Output rate : ");
	scanf("%d", &rate);
	printf(" Enter the Bucket Size : ");
	scanf("%d", &bucketSize);
	i = 0;
    while(i<packetcount || remainingSize>0)//remainingSize param is important...
    {
        if(i<packetcount)
        {
            if((packets[i]+remainingSize)>bucketSize)
            {
                printf(" Bucket capacity exceeded ! Packet %d overflow \n ", packets[i]);
            }
            else
            {
                remainingSize += packets[i];
				printf("\n \nIncoming Packet size : %d ", packets[i]);
				printf("\nBytes remaining to Transmit : %d ", remainingSize);
            }
            i++;
        }
        timeToTransmit = (rand() % 4 + 1) * 10;
		printf("\nTime left for transmission : %d units \n", timeToTransmit);
        for (int clk = 10; clk < timeToTransmit; clk+=10)
        {
            sleep(1);
            if (remainingSize)
			{
				if (remainingSize <= rate)
					op = remainingSize, remainingSize = 0;
				else
					op = rate, remainingSize -= rate;
				printf(" \nPacket % d transmitted \n ", op);
				printf(" Bytes Remaining to Transmit : %d \n ", remainingSize);
			}
			else
			{
				printf(" \nTime left for transmission : %d units ", timeToTransmit - clk);
				printf(" \nNo packets to transmit !!\n ");
			}
        }
        
    }

}