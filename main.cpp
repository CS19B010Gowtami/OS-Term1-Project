#include<bits/stdc++.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#define STUDENTS 100
#define EVALUATORS 100
using namespace std;

int main(int argc,char *argv[])
{
   int bytes_read=0;
   char *readStream = new char[sizeof(int)];
   char *writeStream = new char[sizeof(int)];
   int readFD[STUDENTS][EVALUATORS];
   int writeFD[STUDENTS][EVALUATORS];
   bool inProgram = true;
   string sid,pid;
   char* path;
   string sidp="SID",pidp="PID";
   int total_files=STUDENTS*EVALUATORS;

   while(inProgram)
   {
      //read
      for(int i=0;i<STUDENTS;i++)
      {
          for(int j=0;j<EVALUATORS;j++)
          {
             sid=sidp+to_string(i);
             pid=pidp+to_string(j);
             path="./Admin/teachers/"+pid+"/"+sid+".txt";
             readFD[i][j]=open(path,O_RDONLY);
          }
      }
      //display
      for(int i=0;i<STUDENTS;i++)
      {
          for(int j=0;j<EVALUATORS;j++)
          {
             if(readFD[i][j]>-1)
             {
               bytes_read = read(readFD[i][j],readStream,sizeof(int));
               if(bytes_read)
                  cout<<readStream<< "    ";
             }
             else
               cout<<"_ ";
          }
          cout<<"\n";
      }
      //close
      for(int i=0;i<STUDENTS;i++)
      {
          for(int j=0;j<EVALUATORS;j++)
          {
             close(readFD[i][j]);
          }
      }
      //write
      for(int i=0;i<STUDENTS;i++)
      {
          for(int j=0;j<EVALUATORS;j++)
          {
             sid=sidp+to_string(i);
             pid=pidp+to_string(j);
             path="./Admin/teachers/"+pid+"/"+sid+".txt";
             writeFD[i][j]=open(path,O_WRONLY);
          }
      }
     
   }
}