#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define w 1
int main()
{
int i,f,frames[50];
printf("\nEnter number of frames to transmit: ");
scanf("%d",&f);
printf("\nEnter %d frames: ",f);
for(i=1;i<=f;i++)
scanf("%d",&frames[i]);
printf("\nWith stop and wait protocol the frames will be sent in the following manner (assuming no corruption of frames)\n\n");
printf("After sending %d frames at each stage sender waits for acknowledgement sent by the receiver\n\n",w);
printf("if error occur negative acknowledge is detected same frame is resend back\n");  
for(i=1;i<=f;i++)
{
if((random()%2)==1)
  {
	if(i%w==0)
	{
		printf("%d\n",frames[i]);
		printf("Acknowledgement of above frames sent is received by sender\n\n");
	}
	else
		printf("%d ",frames[i]);
  }
  else
  {
	sleep(3);
         printf("negative acknowledge resend %d frame\n",i);
	i=i-1;
	sleep(1);
   }

}
return 0;
}
