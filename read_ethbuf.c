#include <stdio.h>

extern int nwbuf;
extern char *wbuf;
extern char rbuf[];
extern int nrbuf;
extern int fd_schar;
extern char hw_source_addr[];
extern char hw_dest_addr[];

int main(int argc,char *argv[])
{

  // This test should transmit one packet, and receive one packet.  
  // This is a way of testing whether the card is working correctly.  

  int i,j;
  int n,l,lcnt;
  int hex;

  eth_open("schar3");

  //    eth_reset();
  
  usleep(1);

  eth_register_mac();
   
  nwbuf=100;
  for(i=0;i<nwbuf;i++)wbuf[i]=i&0x00ff;
  n=0;
  n=eth_write();
  printf("written %d \n",n);
  for(l=0;l<8000;l++)lcnt++; // a pause
  usleep(1000);
    n=0;
    //    eth_enableBlock();
  printf(" about to call nreadmm \n");
  for(i=0;i<10;i++){
    n=eth_readmm();
   printf(" %d nread %d \n",i,n);
   if(n>50){
     for(j=0; j<n; j = j+2){
       printf(" %02x%02x",rbuf[j+1]&0xff,rbuf[j]&0xff); 
       if(j%16 == 14) //if header for odmb go to next event
	 printf("\n");
     }
     printf("\n");

   }
     
  }
  eth_close();

  return 1;
}
