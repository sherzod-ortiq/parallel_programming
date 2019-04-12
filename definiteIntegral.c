#include<stdio.h>
#include<math.h>
#include<time.h>

double calculateIntegral(double dx,double a,double b);
double integratingFunction(double x);
clock_t start, end, iterStart, iterEnd;
double totalCpuTimeUsed, iterCpuTimeUsed;

void main(void){
  double a,b,eps,dx,n,s1,s2,b1; int k;
  a = 0;
  b = 1;
  n = 10;
/*
  printf("\t HELLO, THIS PROGRAM COUNTS DEFINITE INTEGRAL!\n\n");
  printf("Input a: "); scanf("%lf",&a);
  printf("Input b: "); scanf("%lf",&b);
  printf("Input the initial number of divisions n: "); scanf("%lf",&n);
*/
  printf("Input accuracy rate (epsilon): "); scanf("%lf",&eps);

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
        printf("\nn= %lf,Integral= %lf, Execution time: %f seconds",n,s1,iterCpuTimeUsed);
			  switch (k){
			    case (1): b1=fabs(s2-s1);
			    case (2): b1=fabs((s2-s1)/s2);
			  }
				    
			} while(b1>eps);
	    printf("\n\nINTEGRAL IS EQUAL TO: %lf\n\n\n",s2);
      end = clock();
      totalCpuTimeUsed = ((double)(end - start)) / CLOCKS_PER_SEC;
      printf("\n Total execution time is equal to: %f seconds\n\n\n",totalCpuTimeUsed);
    }else{
      printf("\t\tWHAT ARE YOU DOING???, n is always>0, reload");
	  }
 
  }
  

double calculateIntegral(double n,double a,double b){
  double a1,d,c,dx;
  c=0;
  d=0;
  dx=(b-a)/n;

  while(c<=n){
 	  a1=integratingFunction(a+c*(dx))*dx;
 	  d=d+a1;
 	  c=c+1;
  }

    return(d);
}


double integratingFunction(double x){
  double retval=exp(-1*pow(x,2));
  return(retval);
} 
