#include<stdio.h>
#include<stdlib.h>
#include<math.h>
int n,r,sent,win_size,range;
struct frame
{
	int data;
	char ack;
}frm[10];
void sender(void);
void sender_sr(void);
void recvack(void);
void resend_sr(void);
void resend_gb(void);	
void selective(void);
void goback(void);
int main()
{
	int c;
	do
	{
		printf("\n1.Selective Repeat ARQ\n2.Go Back ARQ\n3.Exit\n");
		printf("Enter your ch:");
		scanf("%d",&c);
		switch(c)
		{
			case 1:
				selective();
				break;
			case 2:
				goback();
				break;
			case 3:
				exit(0);
				break;
			default:
				printf("Invalid choice!!");
				break;
		}
	}
	while(c!=4);
}

void goback()
{
	sender();
	recvack();
	resend_gb();
	printf("\nAll frames sent successfully\n");
}

void selective()
{
	sender();
	sender_sr();
	//recvack();
	//resend_sr();
	printf("\nAll frames sent successfully\n");
}

void sender()
{
	int i;
	printf("\nEnter the sequence no:");
	scanf("%d",&n);
	range=pow(2,n)-1;
	printf("\nRange is 0-%d",range);
	for(i=0;i<=range;i++)
	{
		frm[i].data=i;
		printf("\nData for frames is %d",frm[i].data);
		//scanf("%d",&frm[i].data);
		frm[i].ack='y';//we consider all frames are acknowledged
		//printf("frm[i].ack is %c\n",frm[i].ack);
	}
	
}
void sender_sr(void)
{
	int i,j,k,a=0;
	win_size=pow(2,n-1);
	printf("\nMaximum window size is: %d\n",win_size);
	while(a<=range)
	{
		for(i=0;i<win_size;i++)
		{
			printf("\nframes send is %d\n",frm[a].data);
			a++;
		}
		//a=i;
		//k=i;
		recvack();
		resend_sr();
		j=0;
		while(frm[r].ack=='n')
		{
			resend_sr;
			j++;
		}
	}
}
void recvack()
{
	int i,ra;
	ra=rand();
	//printf("rand is %d\n",ra);
	r=ra%n;
	//printf("r is %d\n",r);
	frm[r].ack='n';
	//printf("frm[r].ack is %c\n",frm[r].ack);
	for(i=1;i<=n;i++)
	{
		if(frm[i].ack=='n')
		{
			printf("\nThe frames number %d is not received\n",r);
		}
	}
}

void resend_sr()
{
	printf("\nResedning frame %d\n",r);
	sleep(2);
	frm[r].ack='y';
	printf("\nThe received frame is %d\n",frm[r].data);
}

void resend_gb()
{
	int i;
	win_size=range;
	printf("\nMaximum window size is: %d",win_size);
	//scanf("%d",&win_size);
	printf("\nResending from frame %d\n",r);
	for(i=r;i<win_size;i++)
	{
		sleep(2);
		frm[i].ack='y';
		printf("Received data of frame %d is %d\n",i,frm[i].data);
	}
}
