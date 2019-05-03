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

#define availableCoresNum  omp_get_max_threads()

double calculateIntegral(int n,double a,double b);
double integratingFunction(double x);
double totalCpuTimeUsed, iterCpuTimeUsed;
clock_t start, end, iterStart, iterEnd;
int useCoresNum;

int main(int argc, char *argv[]){
  double a,b,eps,dx,s1,s2,b1;
  int k, n;
  a = 0;
  b = 1;
  n = 10;
  eps = 0.00000001;

/*
  printf("\t HELLO, THIS PROGRAM COUNTS DEFINITE INTEGRAL!\n\n");
  printf("Input a: "); scanf("%lf",&a);
  printf("Input b: "); scanf("%lf",&b);
  printf("Input the initial number of divisions n: "); scanf("%i",&n);
  printf("Input accuracy rate (epsilon): "); scanf("%lf",&eps);
*/

  printf("\t HELLO, THIS PROGRAM COUNTS DEFINITE INTEGRAL!\n\n");
  printf("Input amount of threads: "); scanf("%i",&useCoresNum);
  printf("a = %lf\n", a);
  printf("b = %lf\n", b);
  printf("Initial number of divisions n = %i\n", n);
  printf("Accuracy rate (epsilon) = %lf\n", eps);
  printf("Cores number %i\n", availableCoresNum);


  if(useCoresNum > availableCoresNum || useCoresNum <= 0){
    useCoresNum = availableCoresNum;
  }
  
  printf("Number of threads %i", useCoresNum);


    if (n>0){      
      start = clock();
      s2=calculateIntegral(n,a,b);

      if (fabs(s2)<1){
        k=1;
      }else{
        k=2;
      }
      
      do{
        s1=s2;
        n=n*2;
        iterStart = clock();
        s2=calculateIntegral(n,a,b);
        iterEnd = clock();
        iterCpuTimeUsed = ((double)(iterEnd - iterStart)) / CLOCKS_PER_SEC;
        printf("\nn= %i,Integral= %lf, Execution time: %lf seconds",n,s1,iterCpuTimeUsed);
        switch (k){
          case (1): b1=fabs(s2-s1);
          case (2): b1=fabs((s2-s1)/s2);
        }
            
      } while(b1>eps);
      printf("\n\nINTEGRAL IS EQUAL TO: %lf\n\n\n",s2);
      end = clock();
      totalCpuTimeUsed = ((double)(end - start)) / CLOCKS_PER_SEC;
      printf("\n Total execution time is equal to: %lf seconds\n\n\n",totalCpuTimeUsed);
    }else{
      printf("\t\tWHAT ARE YOU DOING???, n is always>0, reload");
    }

  return(0);
}
  

double calculateIntegral(int n,double a,double b){
  double a1,d,dx,c;
  int i;
  c=0;
  d=0;

  #pragma omp parallel private(a1,dx) reduction(+:d)
  {
    omp_set_dynamic(0);
    omp_set_num_threads(useCoresNum);
    dx=(b-a)/(double)n;
    a1=integratingFunction(a+c*(dx))*dx;

    #pragma omp for
    for(i=0; i<n; i++){
      a1=integratingFunction(a+i*(dx))*dx;
      d+=a1;
    }

  }
    return(d);
}


double integratingFunction(double x){
  double retval=exp(-1*pow(x,2));
  return(retval);
} 
