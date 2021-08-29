#include<unistd.h>
#include<sys/types.h>
#include<linux/fcntl.h>
#include<stdio.h>
#include<stdlib.h>

int main()
{

   int fd,ret,buf[1024],rt,ret2;
   int fd1,ret1,buf1[1024],rt1,ret3;

   //opening/testing of test1
   fd = open("/sys/kernel/kobject_test/test1",O_RDWR); 
      
      if(fd<0){	//error checking
           perror("error in opening");
           exit(1);
   }
   
   //we are printing value of a handle to 
   //an active file, known as active file handle
   printf("data obtained from path [/sys/kernel/kobject_test/test1]\n");
   printf("value of fd is %d\n", fd);
    
	//reading from file  
	ret = read(fd,buf,64); 
	if(ret<0) { perror("error in read"); exit(6); }
	if(ret>0) { write(STDOUT_FILENO,buf,ret); }	//printing it in terminal
	printf("the no. characters read and returned is %d\n", ret);
 	puts(" ");
	
	lseek(fd,0,SEEK_SET);		//bringing file pointer to start of file
	rt=write(fd,"50",4);		//writing data to the file 
	printf("Using Write(fd-->%d,value written--->\"50\",size of val written(%d)""\nit returned characters: %d\n",fd,4,rt);

	lseek(fd,0,SEEK_SET);		//bringing file pointer to start of file      
	ret2 = read(fd,buf,64);	//reading from the same file again    
	if(ret2<0) { perror("error in read"); exit(6); }
	printf("again reading from the same file \n");	
	if(ret2>0) { write(STDOUT_FILENO,buf,ret2); }	//printing data in terminal
	puts(" ");

 
  
	//opening/testing of test2
	//fd1 = open("/sys/kernel/kobject_test/test2",O_RDWR);//it will never give permission
	//refer dmesg_data.txt
	fd1 = open("/sys/kernel/kobject_test/test2",O_RDONLY);
	//refre dmesg_test2.txt 
	
      if(fd1<0){
           perror("error in opening");
           exit(1);
   }
   
   //we are printing value of a handle to 
   //an active file, known as active file handle
   printf("data obtained from path [/sys/kernel/kobject_test/test2]\n");
   printf("value of fd is %d\n", fd1); 
   ret1 = read(fd1,buf1,64);    
  
   if(ret1<0) { perror("error in read"); exit(6); }
   if(ret1>0) { write(STDOUT_FILENO,buf1,ret1); }	//printing it in terminal
   printf("the no. characters read and returned is %d\n", ret1);
   puts(" ");

	lseek(fd1,0,SEEK_SET);		//bringing file pointer to start of file
	
	rt1=write(fd1,"100",4);	//writing data to the file
	if(rt1<0) { perror("error in write"); exit(6); }	//error checking
	printf("Using Write(fd-->%d,value written--->\"100\",size of val written(%d)""\nit returned characters: %d\n",fd1,4,rt1);

     exit(0);

}
