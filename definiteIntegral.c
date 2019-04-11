/*
Code for calculating definite integral.
Task source:
http://libweb.kpfu.ru/ebooks/06-IPh/06_45_A5-000912.pdf
Chapter 3, "rectangle method", task 1.
Use "gcc -o definiteIntegral definiteIntegral.c -lm" to compile.
*/

#include<stdio.h>
#include<math.h>

float calculateIntegral(float dx,float a,float b);
float integratingFunction(float x);

void main(void){
  float a,b,eps,dx,n,s1,s2,b1; int k;
  printf("\t HELLO, THIS PROGRAM COUNTS DEFINITE INTEGRAL!\n\n");
  printf("Input a: "); scanf("%f",&a);
  printf("Input b: "); scanf("%f",&b);
  printf("Input the initial number of divisions n: "); scanf("%f",&n);
  printf("Input accuracy rate (epsilon): "); scanf("%f",&eps);
    
    if (n>0){	  
    
      s2=calculateIntegral(n,a,b);

      if (fabs(s2)<1){
        k=1;
      }else{
        k=2;
      }
      
      do{
			  s1=s2;
			  n=n*2;
			  s2=calculateIntegral(n,a,b);
        printf("\nn= %f,Integral= %f",n,s1);
			  switch (k){
			    case (1): b1=fabs(s2-s1);
			    case (2): b1=fabs((s2-s1)/s2);
			  }
				    
			} while(b1>eps);
	    printf("\n\nINTEGRAL IS EQUAL TO: %f\n\n\n",s2);
   
    }else{
      printf("\t\tWHAT ARE YOU DOING???, n is always>0, reload");
	  }
 
  }
  

float calculateIntegral(float n,float a,float b){
  float a1,d,c,dx;
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


float integratingFunction(float x){
  float retval=exp(-1*pow(x,2));
  return(retval);
} 
