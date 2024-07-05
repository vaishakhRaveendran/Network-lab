#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#define packetCount 3
int main()
{
	srand(time(0));
	int packets[packetCount], i, rate, bucketSize, remainingSize = 0, timeToTransmit, clk, op;
	for (i = 0; i < packetCount; ++i)
		packets[i] = (rand() % 9 + 1) * 10;
	printf(" \nEnter the Output rate : ");
	scanf("%d", &rate);
	printf(" Enter the Bucket Size : ");
	scanf("%d", &bucketSize);
	i = 0;
	//If the  transmission time combined for n packets not enough we will have to give extra transmission time...
	while (i < packetCount || remainingSize > 0)
	{
		if (i < packetCount)
		{
			if ((packets[i] + remainingSize) > bucketSize)
				printf(" Bucket capacity exceeded ! Packet %d overflow \n ", packets[i]);
			else
			{
				remainingSize += packets[i];
				printf("\n \nIncoming Packet size : %d ", packets[i]);
				printf("\nBytes remaining to Transmit : %d ", remainingSize);
			}
			++i;
		}
		timeToTransmit = (rand() % 4 + 1) * 10;
		printf("\nTime left for transmission : %d units \n", timeToTransmit);
		for (clk = 10; clk <= timeToTransmit; clk += 10)
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

/*
Using transmission time to simulate variable arrival times:
You're correct in your intuition. While the code doesn't explicitly model packet arrival times, the random transmission time does introduce variability that 
somewhat mimics irregular packet arrivals.

Peaceful transmission period:
Yes, you've understood this correctly. The transmission time essentially represents a period where the system can process the data in the bucket without i
nterference from new incoming packets. It's a simplification that allows the simulation to alternate between "receiving" and "transmitting" phases.

Removing transmission time with explicit arrival times:
You're absolutely right. If we were to implement explicit arrival times for each packet, we could indeed remove or significantly modify the current transmission time mechanism. This would lead to a more realistic simulation.
*/
