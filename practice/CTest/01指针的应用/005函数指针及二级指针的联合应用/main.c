#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

typedef struct
{
    uint32_t ID;
    char name[30];
    char *ExName;
    bool WM;
}Student;

Student *student_one;


void change_Info(Student **stu)
{
 
    (*stu)->ID=321;
    (*stu)->ExName="sun";
    
    strncpy( (*stu)->name,"Redchen",29);
    (*stu)->name[29]='\0';
    (*stu)->WM=1;
}
void (*func)(Student **stu);
int main(void)
{
    func=change_Info;
    student_one=malloc(sizeof(Student));
    func(&student_one);
    printf("ID:%d\n",student_one->ID);
    printf("name:%s\n",student_one->name);
    printf("Ex:%s\n",student_one->ExName);
    printf("WM:%d\n",student_one->WM);
    free(student_one);//释放内存
    student_one=NULL;//指针悬空
    return 0;
}