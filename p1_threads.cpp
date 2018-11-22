#include "p1_threads.h"
using namespace std;

int pnum,psize;
double aver,median,var;
void *runner(void *param);
value data[1000000];
double *sum=new double[pnum];
value c[1000000];  //used for merge
//value b[1000001];
void start_thread(int num,int size,value *p){
psize=size-1;//999999
pnum=num;
pthread_t tid[num];
pthread_attr_t attr[num];
double total=0,total1=0;

for(int j=0;j<size;j++) data[j].grade=p[j].grade, data[j].id=p[j].id;

for(int i=0; i<num;i++){
 sum[i]=0;
 pthread_attr_init(&attr[i]);
 pthread_create(&tid[i],&attr[i],runner,(void*)(&i));
pthread_join(tid[i],NULL);
 }


for(int i=0;i<pnum;i++)  total=total+sum[i];

aver=total/size;
//cout<<aver<<endl;
//merge(data,0,psize);

int index[num+1];
int tempsize=num;
for(int p=0;p<num;p++) index[p]=floor(p*psize/num);
index[num]=psize+1;
while(tempsize>1){

if(tempsize%2==0){
for(int p=0;p<tempsize;p=p+2){
 mergefinal(data,index[p],index[p+1]-1,index[p+2]-1);
}

for(int p=0;p<=tempsize/2;p++) index[p]=index[2*p];
tempsize=(tempsize/2);
}

else {

for(int p=0;p<tempsize-1;p=p+2){
 mergefinal(data,index[p],index[p+1]-1,index[p+2]-1);



}
for(int p=0;p<=(tempsize-1)/2;p++) index[p]=index[2*p];
index[(tempsize-1)/2+1]=index[tempsize];

tempsize=floor(tempsize/2)+tempsize%2;
}
}




for(int i=0;i<=psize;i++) total1=total1+(data[i].grade-aver)*(data[i].grade-aver);
var=sqrt(total1/size);
//cout<<data[0].grade<<endl;
//cout<<var<<endl;
median=(data[500000].grade+data[499999].grade)/2;
//cout<<median<<endl;


}







void*runner(void *param){
int j=*(int*)param;
//cout<<j<<endl;

if(j==pnum-1){
for(int l=floor(j*psize/pnum);l<psize+1;l++){

 sum[j]=sum[j]+data[l].grade;
}

}
else{
for(int l=floor(j*psize/pnum);l<floor((j+1)*psize/pnum);l++){

 sum[j]=sum[j]+data[l].grade;
}
}
//cout<<sum[j]<<endl;
if(j==pnum-1) merge(data,floor(j*psize/pnum),psize);
else merge(data,floor(j*psize/pnum),floor((j+1)*psize/pnum)-1);
pthread_exit(0);
}







void mergefinal(value a[],int x, int y, int z)
{
if(x<z){
int x1=x,y1=y+1,x2=x;
while(x1<=y &&  y1<=z ){
if(a[x1].grade<=a[y1].grade)   c[x2++]=a[x1++];
else c[x2++]=a[y1++];
}

if(x1>y){
for(int q=y1;q<=z;q++) c[x2++]=a[q];
}

else {
for(int q=x1;q<=y;q++) c[x2++]=a[q];
}

for(int q=x;q<=z;q++) a[q]=c[q];

}
}

void merge(value a[],int x,int z){


if(z>x){
int middle;
middle=(z+x)/2;
merge(a,x,middle);
merge(a,middle+1,z);
mergefinal(a,x,middle,z);
}
}











