#include <stdio.h>

extern char *wbuf;
extern char rbuf[];
extern int nrbuf;
extern int fd_schar;
extern char hw_source_addr[];
extern char hw_dest_addr[];

int main(int argc,char *argv[]){
  int i,j;
  int n,l,lcnt;
  int hex;
  int EventToPrint;

  eth_open("schar3");
  usleep(1);
  eth_register_mac();
   
  printf("\n--------------------------------\n");
  printf("Enter Event Number to print: ");
  scanf("%d", &EventToPrint);
  printf("--------------------------------\n");

  for(i=1;i<=EventToPrint;i++){
    n=eth_readmm();
    printf(" Event %d has %d words\n",i,n/2);
    if(n>50 || 1){
      for(j=0; j<n; j = j+2){
	printf(" %02x%02x",rbuf[j+1]&0xff,rbuf[j]&0xff); 
	if(j%16 == 14)   //print words in 24 columns, in three sets of 8 
	  printf("   ");
	if(j%48 == 46)   //if header for odmb go to next event  
	  printf("\n"); 
	//if((rbuf[j]&0xF000)==0xF001) printf("X");
      }
      printf("\n\n");

    }
     
  }
  eth_close();

  return 1;
}
