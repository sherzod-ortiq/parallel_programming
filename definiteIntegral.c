/*
Code for calculating definite integral.
Task source:
http://libweb.kpfu.ru/ebooks/06-IPh/06_45_A5-000912.pdf
Chapter 3, "rectangle method", task 1.
Use "gcc -o definiteIntegral definiteIntegral.c -lm" to compile.
*/

#include<stdio.h>
#include<math.h>
#include<time.h>


double calculateIntegral(int divisionsNum,double a,double b);
double integratingFunction(double x); 

void main(){
  double a, b, dx, sum, totalCpuTimeUsed;
  int divisionsNum;
  clock_t startTime, endTime;
  a = 0;
  b = 1;
  divisionsNum = 211000000;

  printf("\n\t HELLO, THIS PROGRAM COUNTS DEFINITE INTEGRAL!\n\n");
  printf("a = %lf\n", a);
  printf("b = %lf\n", b);
  printf("Initial number of divisions divisionsNum = %i\n", divisionsNum);
  
  startTime = clock();

    sum = calculateIntegral(divisionsNum,a,b);

  endTime = clock();
  totalCpuTimeUsed = ((double)(endTime - startTime)) / CLOCKS_PER_SEC;

  printf("Integral is equal to: %lf\n",sum);      
  printf("Total execution time is equal to: %lf seconds\n\n",totalCpuTimeUsed);
}
  

double calculateIntegral(int divisionsNum,double a,double b){
  int i;
  double sum, dx;
  sum = 0;
  dx=(b-a)/(double)divisionsNum;

  for(i=0; i<divisionsNum; i++){
    sum += integratingFunction(a+i*(dx))*dx;
  }

  return(sum);
}


double integratingFunction(double x){
  double retval=exp(-1*pow(x,2));
  return(retval);
} 
