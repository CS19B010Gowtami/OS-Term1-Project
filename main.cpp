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
    int no_of_stu=-2, no_of_tea=-2;
    DIR *dir;
    struct dirent *dp;
    if((dir = opendir("../../root/admin/teachers/")) == NULL){
        printf ("Cannot open ../../root/admin/teachers/");
        exit(1);  
    }
    while ((dp = readdir(dir)) != NULL) {
        // printf("%i\n",(*dp).d_ino);
        printf("filename :     %s\n",(*dp).d_name);
        no_of_tea++;
    }
    if((dir = opendir("../../root/admin/students/")) == NULL){
        printf ("Cannot open ../../root/admin/students/");
        exit(1);  
    }
    while ((dp = readdir(dir)) != NULL) {
        // printf("%i\n",(*dp).d_ino);
        printf("filename :     %s\n",(*dp).d_name);
        no_of_stu++;
    }
    printf("no.of teachers: %d\nno.of students: %d\n",no_of_tea,no_of_stu);
    int bytes_read = 0;
    char *readStream = new char[3];
    char *writeStream = new char[3];
    int readFD[no_of_stu][no_of_tea];
    int writeFD[no_of_stu][no_of_tea];
    char *marksinfo[no_of_stu][no_of_tea];
    bool inProgram = true;
    string sid, pid;
    char *path;
    string sidp = "sid", pidp = "pid";
    int total_files = no_of_stu * no_of_tea;
    string students_info[no_of_stu], evaluators_info[no_of_tea];
    char *work[no_of_stu];
    int index=0;
    if((dir = opendir("../../root/admin/teachers/")) == NULL){
        printf ("Cannot open ../../root/admin/teachers/");
        exit(1);  
    }
    while ((dp = readdir(dir)) != NULL) {
        // printf("%i\n",(*dp).d_ino);
        // printf("%s\n",(*dp).d_name);
        string temp = (*dp).d_name;
        string s1=".", s2="..";
        if(temp != s1&& temp != s2){
            evaluators_info[index] = temp;
            printf("evaluators_info[%d] = %s\n",index,evaluators_info[index]);
            index++;
        }
    }
    index=0;
    if((dir = opendir("../../root/admin/students/")) == NULL){
        printf ("Cannot open ../../root/admin/students/");
        exit(1);  
    }
    while ((dp = readdir(dir)) != NULL) {
        // printf("%i\n",(*dp).d_ino);
        // printf("%s\n",(*dp).d_name);
        string temp = (*dp).d_name;
        string s1=".", s2="..";
        if(temp != s1&& temp != s2){
            students_info[index] = temp;
            printf("students_info[%d] = %s\n",index,students_info[index]);
            index++;
        }
    }

    for (int i = 0; i < no_of_stu; i++)
    {
        printf("%s",students_info[i]);
        printf("\n");
    }
    for (int i = 0; i < no_of_tea; i++)
    {
        printf("%s",evaluators_info[i]);
        printf("\n");
    }
    while (inProgram)
    {
        // read
        for (int i = 0; i < no_of_stu && inProgram == true; i++)
        {
            for (int j = 0; j < no_of_tea && inProgram == true; j++)
            {
                string s = "../../root/admin/teachers/" + evaluators_info[j] + "/" + students_info[i] + ".txt";
                printf(s);
                printf("\n");
                readFD[i][j] = open(const_cast<char *>(s.c_str()), O_RDONLY);
            }
        }
        // display
        for (int i = 0; i < no_of_stu && inProgram == true; i++)
        {
            cout << "Student " << students_info[i] << endl;
            for (int j = 0; j < no_of_tea && inProgram == true; j++)
            {
                if (readFD[i][j] > -1)
                {
                    bytes_read = read(readFD[i][j], readStream, sizeof(int));
                    if (bytes_read)
                    {
                        marksinfo[i][j] = readStream;
                        cout << "Evaluator-" << evaluators_info[j] << "   " << readStream  <<endl;
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
        //write
        for (int i = 0; i < no_of_stu && inProgram == true; i++)
        {
            for (int j = 0; j < no_of_tea && inProgram == true; j++)
            {
                sid = sidp + to_string(i);
                pid = pidp + to_string(j);
                string s = "../../root/admin/teachers/" + evaluators_info[j] + "/" + students_info[i] + ".txt";
                printf(s);
                printf("\n");
                writeFD[i][j] = open(const_cast<char *>(s.c_str()), O_WRONLY);
            }
        }
        //edit
        bool access = false;
        for (int i = 0; i < no_of_stu && inProgram == true; i++)
        {
            for (int j = 0; j < no_of_tea && inProgram == true; j++)
            {
                access=access || writeFD[i][j] ;
            }
        }
        if(access && inProgram)
        {
            for (int i = 0; i < no_of_tea && inProgram == true; i++)
            {
                if(writeFD[0][i]!=-1)
                {
                    cout << "Enter roll no. to change marks of that student for evaluator-" <<i<<"  or -1 to exit the program "<< endl;
                    int option;
                    cin >> option;
                    if(option>-1 && option < no_of_stu)
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
        // read
        for (int i = 0; i < no_of_stu && inProgram == true; i++)
        {
            for (int j = 0; j < no_of_tea && inProgram == true; j++)
            {
                string s = "../../root/admin/teachers/" + evaluators_info[j] + "/" + students_info[i] + ".txt";
                printf(s);
                printf("\n");
                readFD[i][j] = open(const_cast<char *>(s.c_str()), O_RDONLY);
            }
        }
        // display
        for (int i = 0; i < no_of_stu && inProgram == true; i++)
        {
            cout << "Student " << i << endl;
            for (int j = 0; j < no_of_tea && inProgram == true; j++)
            {
                if (readFD[i][j] > -1)
                {
                    bytes_read = read(readFD[i][j], readStream, sizeof(int));
                    if (bytes_read)
                    {
                        marksinfo[i][j] = readStream;
                        cout << "Evaluator-" << j << "   " << readStream <<endl;
                    }
                }
                else
                {
                    string s = "_";
                    marksinfo[i][j] = const_cast<char *>(s.c_str());
                    cout << s ;
                }
            }
            cout << "\n";
        }
        // close
        for (int i = 0; i < no_of_stu; i++)
        {
            for (int j = 0; j < no_of_tea; j++)
            {
                close(readFD[i][j]);
            }
        }
        // close
        for (int i = 0; i < no_of_stu; i++)
        {
            for (int j = 0; j < no_of_tea; j++)
            {
                close(writeFD[i][j]);
            }
        }
    }
}