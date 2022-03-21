#include<bits/stdc++.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#define STUDENTS 3
#define EVALUATORS 3
using namespace std;

int main(int argc,char *argv[])
{
   int bytes_read=0;
   char *readStream = new char[3];
   char *writeStream = new char[3];
   int readFD[STUDENTS][EVALUATORS];
   int writeFD[STUDENTS][EVALUATORS];
   char *marksinfo[STUDENTS][EVALUATORS];
   bool inProgram = true;
   string sid,pid;
   char* path;
   string sidp="sid",pidp="pid";
   int total_files=STUDENTS*EVALUATORS;
  string students_info[STUDENTS],evaluators_info[EVALUATORS];
   char* work[STUDENTS];
   for(int i=0;i<STUDENTS;i++)
   {
       students_info[i]=sidp+to_string(i);
   }
   for(int i=0;i<EVALUATORS;i++)
   {
       evaluators_info[i]=pidp+to_string(i);
   }
   while(inProgram)
   {
      //read
      for(int i=0;i<STUDENTS;i++)
      {
          for(int j=0;j<EVALUATORS;j++)
          {
             string s="./admin/teachers/"+evaluators_info[j]+"/"+students_info[i]+".txt";
             readFD[i][j]=open(const_cast<char*>(s.c_str()),O_RDONLY);
          }
      }
      //display
      for(int i=0;i<STUDENTS;i++)
      {
        //   cout<<stu
        cout << "Student " << i << endl;
          for(int j=0;j<EVALUATORS;j++)
          {
             if(readFD[i][j]>-1)
             {
               bytes_read = read(readFD[i][j],readStream,sizeof(int));
               if(bytes_read)
               {
                  marksinfo[i][j]=readStream;
                  cout<<readStream<< "    ";
               }
             }
             else
             {
                 string s = "_";
                 marksinfo[i][j]=const_cast<char*>(s.c_str());
                 cout<<"_";
             }
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
             string s="./admin/teachers/"+pid+"/"+sid+".txt";
             writeFD[i][j]=open(const_cast<char*>(s.c_str()),O_WRONLY);
          }
      }
      //Display
      for(int i=0;i<STUDENTS && inProgram==true;i++)
      {
          for(int j=0;j<EVALUATORS;j++)
          {
             sid=sidp+to_string(i);
             pid=pidp+to_string(j);
             string s="./admin/teachers/"+pid+"/"+sid+".txt";
             if(writeFD[i][j]>-1)
             {
                cout<< "Enter "<<i<< " to Change marks of student- "<<sid<<endl;
             }
            cout<<"Enter -1 to Exit The Program"<<endl;
            cout << endl;
            // Show Options For editing  
            int option;
            cin>> option; 
            cin.ignore();    
            if(option>=0 && option<=STUDENTS && writeFD[i][j]>-1)
            {
                cout<<"Enter marks To Replace : ";
                cin>>writeStream;  
                cout<<writeStream<<endl;
                marksinfo[i][j]=writeStream;
                lseek(writeFD[option-1][j],0,SEEK_SET);
                write(writeFD[option-1][j],writeStream,sizeof(int));
            }
            else if(option==-1)
            {
                inProgram = false;
            }
            else
            {
                cout<<"Please Enter A Valid Option"<<endl;
            }
            cout<<endl;
          }
      }
      //close
      for(int i=0;i<STUDENTS;i++)
      {
          for(int j=0;j<EVALUATORS;j++)
          {
             close(writeFD[i][j]);
          }
      }
   }
}