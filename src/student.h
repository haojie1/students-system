#ifndef STUDENT_H
#define STUDENT_H
typedef struct student{
    struct student * next;  
    struct student * previous;  //定义链表所需要的先后指针
    char * name;
    int n_len;                  //在进行将文件重新读取到链表的时候，进行动态分配内存的时候需要
    int age;
}studentTypeDef;                //定义学生的结构体

void initList(void);            
void manageList(void);          //用户界面

void addStudent(void);
void delStudent(void);
void find(void);                //一个包装函数
studentTypeDef* findStudent(const char * name);
void modifyStudent(void);

void showStudent(studentTypeDef* student);
void showAllStudent(studentTypeDef* students);
void delStudentList(studentTypeDef* students);
int initSys(void);              //读取文件中的数据到链表
void createNewDoc(void);        //创建一个新的文件 
void writeToDoc(void);          //将链表中的数据写入到文件
#endif
