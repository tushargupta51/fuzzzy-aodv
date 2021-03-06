
#include <aodv/fuzzy.h>
#include<stdio.h>


float fuzzy::fuzzify(unsigned int nreq, unsigned int nrep, unsigned int nau)
{
  
  float mu_nreq_l, mu_nreq_h, mu_nreq_vh, mu_nrep_l, mu_nrep_h, mu_nau_l, mu_nau_m, mu_nau_h, mu_vl, mu_l, mu_m, mu_h, mu_vh, trust2;
  
  mu_nreq_l=mem_fnc((float)nreq, 0, 0, 4,6);
  mu_nreq_h=mem_fnc((float)nreq, 5, 7, 7, 9);
  mu_nreq_vh=mem_fnc2((float)nreq,8,10);
 // mu_nreq=max(temp1,temp2, temp3);
  
  mu_nrep_l=mem_fnc((float)nrep, 0, 0, 1, 3);
  mu_nrep_h=mem_fnc2((float)nrep,1,3);
 // mu_nrep=max(temp1, temp2, 0);
  
  mu_nau_l=mem_fnc((float)nau,0,0,1,3);
  mu_nau_m=mem_fnc((float)nau,1,4,4,6);
  mu_nau_h=mem_fnc2((float)nau,5,7);
  //mu_nau=max(temp1, temp2, temp3);
  
  //printf(" %f,%f,%f,%f ",mu_nreq_l,mu_nrep_l,mu_nau_l);
  
  mu_vh=maxf(minf(mu_nreq_l,mu_nrep_l,mu_nau_l),0,0);
  mu_h=minf(mu_nreq_h,mu_nrep_l,mu_nau_m);
 
  mu_m=maxf(maxf(minf(mu_nreq_l,mu_nrep_h,mu_nau_l),minf(mu_nreq_h,mu_nrep_l,mu_nau_l),minf(mu_nreq_h,mu_nrep_h,mu_nau_l)),maxf(minf(mu_nreq_vh,mu_nrep_l,mu_nau_l),minf(mu_nreq_vh,mu_nrep_h,mu_nau_l),minf(mu_nreq_vh,mu_nrep_h,mu_nau_m)),maxf(minf(mu_nreq_l,mu_nrep_l,mu_nau_m),0,0));
 
  mu_l=maxf(maxf(minf(mu_nreq_l,mu_nrep_h,mu_nau_m),minf(mu_nreq_h,mu_nrep_l,mu_nau_h),minf(mu_nreq_h,mu_nrep_h,mu_nau_m)),minf(mu_nreq_vh,mu_nrep_l,mu_nau_m),minf(mu_nreq_vh,mu_nrep_l,mu_nau_h));
 
  mu_vl=maxf(maxf(minf(mu_nreq_l,mu_nrep_l,mu_nau_h),minf(mu_nreq_l,mu_nrep_h,mu_nau_h),minf(mu_nreq_h,mu_nrep_h,mu_nau_h)),minf(mu_nreq_vh,mu_nrep_h,mu_nau_h),0);

 // printf(" %f,%f,%f,%f,%f ",mu_vl,mu_l,mu_m,mu_h,mu_vh);
  trust2=defuzzify(mu_vl,mu_l,mu_m,mu_h,mu_vh);
  return trust2;
}

float fuzzy::defuzzify(float vl, float l,float m, float h, float vh)
{
  float trust;
 // printf("%f,%f,%f,%f,%f",vl,l,m,h,vh);
   
  trust=(6*vl+4*l+5*m+6*h+34*vh)/(3*vl+l+m+h+4*vh);
  return trust;
  
}
  
  
float fuzzy::mem_fnc(float x,float a,float b,float c,float d)
{
  float dom;
  if ( x>a && x<b)
  { 
    dom=(x-a)/(b-a); 
  }
  else if (x>c && x<d)
  { 
    dom=(d-x)/(d-c); 
  }
  else if (x>=b && x<=c)
  {
    dom=1.0; 
  }
  else
  { 
    dom=0; 
  }
  return dom;
}

float fuzzy::mem_fnc2(float x, float a, float b)
{
  float dom;
  if(x>a && x<b)
  {
    dom=(x-a)/(b-a);
  }
  else if(x>=b)
  {
    dom=1.0;
  }
  else
  {
    dom=0;
  }
  return dom;
}

float fuzzy::maxf(float temp1, float temp2, float temp3)
{
  if(temp1 >=temp2 && temp1 >= temp3)
  {
    return temp1;
  }
  else if(temp2 >= temp1 && temp2>=temp3)
  {
    return temp2;
  }
  else
    return temp3;
}

float fuzzy::minf(float temp1, float temp2, float temp3)
{
  if(temp1 <=temp2 && temp1 <= temp3)
  {
    return temp1;
  }
  else if(temp2 <= temp1 && temp2<=temp3)
  {
    return temp2;
  }
  else
    return temp3;
}