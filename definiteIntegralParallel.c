/*
Code for calculating definite integral with OpenMP applied.
Task source:
http://libweb.kpfu.ru/ebooks/06-IPh/06_45_A5-000912.pdf
Chapter 3, "rectangle method", task 1.
Use "gcc -fopenmp definiteIntegralParallel.c -o definiteIntegralParallel -lm" to compile and ./definiteIntegralParallel to execute
*/

#include<stdio.h>
#include<math.h>
#include<time.h>
#include<omp.h>

#define availableThreadsNum  omp_get_max_threads()

double calculateIntegral(int divisionsNum,double a,double b, int useThreadsNum);
double integratingFunction(double x); 

void main(){
  double a, b, dx, sum, start_time, end_time, totalCpuTimeUsed;
  int useThreadsNum, divisionsNum;
  a = 0;
  b = 1;
  divisionsNum = 211000000;

  printf("\n\t HELLO, THIS PROGRAM COUNTS DEFINITE INTEGRAL!\n\n");
  printf("Input amount of threads to be used: "); scanf("%i",&useThreadsNum);
  printf("a = %lf\n", a);
  printf("b = %lf\n", b);
  printf("Initial number of divisions divisionsNum = %i\n", divisionsNum);
  printf("Total number of CPU cores %i\n", availableThreadsNum);

  if(useThreadsNum > availableThreadsNum || useThreadsNum <= 0){
    useThreadsNum = availableThreadsNum;
  }
  
  printf("Number of threads in use %i\n", useThreadsNum);

  start_time = omp_get_wtime();

    sum = calculateIntegral(divisionsNum,a,b,useThreadsNum);

  end_time = omp_get_wtime();
  totalCpuTimeUsed = end_time - start_time;

  printf("Integral is equal to: %lf\n",sum);      
  printf("Total execution time is equal to: %lf seconds\n\n",totalCpuTimeUsed);
}
  

double calculateIntegral(int divisionsNum,double a,double b, int useThreadsNum){
  double local_sum,global_sum,dx;
  int i;

  omp_set_dynamic(0);// Explicitly disable dynamic teams
  omp_set_num_threads(useThreadsNum); // Set number of cores to be used
  #pragma omp parallel default(none) private(local_sum,i) shared(global_sum, a, b, dx, divisionsNum)
  {
    local_sum=0;
    global_sum = 0;
    dx=(b-a)/(double)divisionsNum;

    #pragma omp for schedule(static)
    for(i=0; i<divisionsNum; i++){
      local_sum += integratingFunction(a+i*(dx))*dx;
    }

    #pragma omp critical 
      global_sum += local_sum;

  }
    return(global_sum);
}


double integratingFunction(double x){
  double retval=exp(-1*pow(x,2));
  return(retval);
} 
