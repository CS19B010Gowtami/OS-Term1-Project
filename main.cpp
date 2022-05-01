#include <bits/stdc++.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <dirent.h>
#include <iostream>
#include <libgen.h>
#include <string.h>
// #define STUDENTS 3
// #define EVALUATORS 3
using namespace std;

int main(int argc, char *argv[])
{
    DIR *dir;
    struct dirent *dp;
    int STUDENTS=-2,EVALUATORS=-2;
    if((dir = opendir("../../root/admin/teachers/")) == NULL){
        printf ("Cannot open .");
        exit(1);  
    }
    while ((dp = readdir(dir)) != NULL) {
        // printf("%i\n",(*dp).d_ino);
        // printf("%s\n",(*dp).d_name);
        EVALUATORS++;
    }
    if((dir = opendir("../../root/admin/students/")) == NULL){
        printf ("Cannot open .");
        exit(1);  
    }
    while ((dp = readdir(dir)) != NULL) {
        // printf("%i\n",(*dp).d_ino);
        // printf("%s\n",(*dp).d_name);
        STUDENTS++;
    }
    int bytes_read = 0;
    char *readStream = new char[3];
    char *writeStream = new char[3];
    int readFD[STUDENTS][EVALUATORS];
    int writeFD[STUDENTS][EVALUATORS];
    char *marksinfo[STUDENTS][EVALUATORS];
    bool inProgram = true;
    string sid, pid;
    char *path;
    string sidp = "sid", pidp = "pid";
    int total_files = STUDENTS * EVALUATORS;
    string students_info[STUDENTS], evaluators_info[EVALUATORS];


    // char *work[STUDENTS];
    // Read FD for student Strings()
    int readFD_forStudents[STUDENTS];
    int writeFD_forStudents[STUDENTS];
    
    for (int i = 0; i < STUDENTS; i++)
    {
        students_info[i] = sidp + to_string(i);
    }
    for (int i = 0; i < EVALUATORS; i++)
    {
        evaluators_info[i] = pidp + to_string(i);
    }
    while (inProgram)
    {
        // read FD
        for(int i=0; i < STUDENTS && inProgram == true; i++){
            string s = "../../root/admin/students/" + students_info[i] + "/" + "work.txt";
            readFD_forStudents[i] = open(const_cast<char *>(s.c_str()), O_RDONLY);
        }
        for (int i = 0; i < STUDENTS && inProgram == true; i++)
        {
            for (int j = 0; j < EVALUATORS && inProgram == true; j++)
            {
                string s = "../../root/admin/teachers/" + evaluators_info[j] + "/" + students_info[i] + ".txt";
                readFD[i][j] = open(const_cast<char *>(s.c_str()), O_RDONLY);
            }
        }
        // display
        // First Work of all the students...
        for (int i = 0; i < STUDENTS && inProgram == true; i++)
        {
            string wk = "";
            char *buff = new char[1];
            cout << "Work Of Student " << i << endl;
            if (readFD_forStudents[i] > -1)
            {
                while(bytes_read = read(readFD_forStudents[i], buff, sizeof(char))!=0){
                    // marksinfo[i][j] = readStream;
                    wk += buff;
                    // cout << "Evaluator-" << j << "   " << readStream  <<endl;
                }
                cout<< wk << endl << endl;
            }
            else
            {
                string s = "This Person has no work Yet";
                marksinfo[i][j] = const_cast<char *>(s.c_str());
                cout << s  ;
            }
            cout << "\n";
        }
        // Followed By marks of all the students
        for (int i = 0; i < STUDENTS && inProgram == true; i++)
        {
            cout << "Student " << i << endl;
            for (int j = 0; j < EVALUATORS && inProgram == true; j++)
            {
                if (readFD[i][j] > -1)
                {
                    bytes_read = read(readFD[i][j], readStream, sizeof(int));
                    if (bytes_read)
                    {
                        marksinfo[i][j] = readStream;
                        cout << "Evaluator-" << j << "   " << readStream  <<endl;
                    }
                }
                else
                {
                    string s = "_";
                    marksinfo[i][j] = const_cast<char *>(s.c_str());
                    cout << s  ;
                }
            }
            cout << "\n";
        }
        //write FD
        for(int i=0; i < STUDENTS && inProgram == true; i++){
            string s = "../../root/admin/students/" + students_info[i] + "/" + "work.txt";
            writeFD_forStudents[i] = open(const_cast<char *>(s.c_str()), O_WRONLY);
        }
        for (int i = 0; i < STUDENTS && inProgram == true; i++)
        {
            for (int j = 0; j < EVALUATORS && inProgram == true; j++)
            {
                sid = sidp + to_string(i);
                pid = pidp + to_string(j);
                string s = "../../root/admin/teachers/" + pid + "/" + sid + ".txt";
                writeFD[i][j] = open(const_cast<char *>(s.c_str()), O_WRONLY);
            }
        }
        //edit
        // First Give Option to edit student..!
        // Then Give option to edit Marks
        bool access = false;
        for (int i = 0; i < STUDENTS && inProgram == true; i++)
        {
            for (int j = 0; j < EVALUATORS && inProgram == true; j++)
            {
                access=access || writeFD[i][j] ;
            }
        }
        
        int stuAcc = 0;
        for (int i = 0; i < STUDENTS && inProgram == true; i++)
        {
            if( writeFD_forStudents[i]!=-1){
                stuAcc += 1;
            }
        }

        if(access && inProgram)
        {
            if(stuAcc == 1){

                for (int i = 0; i < STUDENTS && inProgram == true; i++)
                {
                    if(writeFD_forStudents[i]!=-1)
                    {
                        // cout << "Please Enter the Student Roll Number" << i <<"  or -1 to exit the program "<< endl;
                        // int option;
                        // cin >> option;
                        cout << "Enter Work for Student " << i << " Here : ";
                        char *buff;
                        // Need To Get an input stream
                        cin >> buff;
                        // work[i] = buff

                        lseek(writeFD_forStudents[i] , 0 , SEEK_SET);
                        write(writeFD_forStudents[i] , buff , sizeof(buff));
                
                        // if(option>-1 && option < STUDENTS)
                        // {
                        // }
                        // else if (option == -1)
                        // {
                        //     inProgram = false;
                        // }
                        // else
                        // {
                        //     cout << "Please Enter A Valid Option" << endl;
                        // }
                        cout << endl;
                    }
                }
            }

            for (int i = 0; i < EVALUATORS && inProgram == true; i++)
            {
                if(writeFD[0][i]!=-1)
                {
                    cout << "Enter roll no. to change marks of that student for evaluator-" <<i<<"  or -1 to exit the program "<< endl;
                    int option;
                    cin >> option;
                    if(option>-1 && option < STUDENTS)
                    {
                        cout << "Enter marks To Replace : ";
                        cin >> writeStream;
                        marksinfo[option][i] = writeStream;
                        lseek(writeFD[option][i] , 0 , SEEK_SET);
                        write(writeFD[option][i] , writeStream , 3);
                    }
                    else if (option == -1)
                    {
                        inProgram = false;
                    }
                    else
                    {
                        cout << "Please Enter A Valid Option" << endl;
                    }
                    cout << endl;
                }
            }
        }
        // // read
        // for (int i = 0; i < STUDENTS && inProgram == true; i++)
        // {
        //     for (int j = 0; j < EVALUATORS && inProgram == true; j++)
        //     {
        //         string s = "../../root/admin/teachers/" + evaluators_info[j] + "/" + students_info[i] + ".txt";
        //         readFD[i][j] = open(const_cast<char *>(s.c_str()), O_RDONLY);
        //     }
        // }
        // // display
        // for (int i = 0; i < STUDENTS && inProgram == true; i++)
        // {
        //     cout << "Student " << i << endl;
        //     for (int j = 0; j < EVALUATORS && inProgram == true; j++)
        //     {
        //         if (readFD[i][j] > -1)
        //         {
        //             bytes_read = read(readFD[i][j], readStream, sizeof(int));
        //             if (bytes_read)
        //             {
        //                 marksinfo[i][j] = readStream;
        //                 cout << "Evaluator-" << j << "   " << readStream <<endl;
        //             }
        //         }
        //         else
        //         {
        //             string s = "_";
        //             marksinfo[i][j] = const_cast<char *>(s.c_str());
        //             cout << s ;
        //         }
        //     }
        //     cout << "\n";
        // }

        // read FD
        for(int i=0; i < STUDENTS && inProgram == true; i++){
            string s = "../../root/admin/students/" + students_info[i] + "/" + "work.txt";
            readFD_forStudents[i] = open(const_cast<char *>(s.c_str()), O_RDONLY);
        }
        for (int i = 0; i < STUDENTS && inProgram == true; i++)
        {
            for (int j = 0; j < EVALUATORS && inProgram == true; j++)
            {
                string s = "../../root/admin/teachers/" + evaluators_info[j] + "/" + students_info[i] + ".txt";
                readFD[i][j] = open(const_cast<char *>(s.c_str()), O_RDONLY);
            }
        }
        // display
        // First Work of all the students...
        for (int i = 0; i < STUDENTS && inProgram == true; i++)
        {
            string wk = "";
            char *buff = new char[1];
            cout << "Work Of Student " << i << endl;
            if (readFD_forStudents[i] > -1)
            {
                while(bytes_read = read(readFD_forStudents[i], buff, sizeof(char))!=0){
                    // marksinfo[i][j] = readStream;
                    wk += buff;
                    // cout << "Evaluator-" << j << "   " << readStream  <<endl;
                }
                cout<< wk << endl << endl;
            }
            else
            {
                string s = "This Person has no work Yet";
                marksinfo[i][j] = const_cast<char *>(s.c_str());
                cout << s  ;
            }
            cout << "\n";
        }
        // Followed By marks of all the students
        for (int i = 0; i < STUDENTS && inProgram == true; i++)
        {
            cout << "Student " << i << endl;
            for (int j = 0; j < EVALUATORS && inProgram == true; j++)
            {
                if (readFD[i][j] > -1)
                {
                    bytes_read = read(readFD[i][j], readStream, sizeof(int));
                    if (bytes_read)
                    {
                        marksinfo[i][j] = readStream;
                        cout << "Evaluator-" << j << "   " << readStream  <<endl;
                    }
                }
                else
                {
                    string s = "_";
                    marksinfo[i][j] = const_cast<char *>(s.c_str());
                    cout << s  ;
                }
            }
            cout << "\n";
        }
        // close
        for (int i = 0; i < STUDENTS; i++)
        {
            for (int j = 0; j < EVALUATORS; j++)
            {
                close(readFD[i][j]);
                close(writeFD[i][j]);
            }
        }

        for(int i=0; i< STUDENTS; i++){
            close(readFD_forStudents[i]);
            close(writeFD_forStudents[i]);
        }
    }
}