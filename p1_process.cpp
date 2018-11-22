#include "p1_process.h"
#include <sys/wait.h>
#include<iomanip>
using namespace std;





value u[1000001];
void get_statistics(std::string class_name[], int num_processes, int num_threads) {

	// You need to create multiple processes here (each process
	// handles at least one file.)
    pid_t pid;
    int n;
    
    for(int i=0; i<num_processes; i++){
    pid=fork();
    
    if(pid==0){   
    int count;
    string line;
    printf("Child process is created. (pid: %d)\n", getpid()); 
    for(int w=i;w<5;w=w+num_processes){
    count=0;
    string filename = "./input/"+class_name[w]+".csv";
    ifstream file;
    file.open(filename.c_str()); 
    getline ( file, line);
    
 

  while (file.good())  
  {
     string temp;
     getline ( file, u[count].id, ',' );
     getline ( file, temp ); // read a string until next comma: 
     u[count].grade=atof(temp.c_str());
     count++;
 
    
    }
     
     n=count-1;
     //cout<<n<<endl; 1000000
     start_thread(num_threads,n,u);
     file.close();


      string ofilename1 = "./output/"+class_name[w]+"_stats.csv";
      string ofilename2 = "./output/"+class_name[w]+"_sorted.csv";
     
      ofstream ofile1,ofile2;
      ofile1.open(ofilename1.c_str()); 
      ofile2.open(ofilename2.c_str()); 
      ofile1<<"Average"<<","<<"Median"<<","<<"Std. Dev"<<endl;
      ofile1<<setprecision(5)<<aver<<","<<setprecision(5)<<median<<","<<setprecision(5)<<var<<endl;
      ofile2<<"Rank"<<","<<"Student ID"<<","<<"Grade"<<endl;
      for(int y=1;y<=1000000;y++){
      ofile2<<y<<","<<data[1000000-y].id<<","<<setprecision(12)<<data[1000000-y].grade<<endl;

}

      ofile1.close();
      ofile2.close();




}


    printf("Child process is terminated. (pid: %d)\n", getpid());     
      exit(1);
   }
   }

for(int i=0;i<num_processes;i++)wait(NULL);
   }
   


  	
   
	
	// Each process should use the sort function which you have defined  		
	// in the p1_threads.cpp for multithread sorting of the data. 
	
	// Your code should be able to get the statistics and generate
	// the required outputs for any number of child processes and threads.
	
