/*
    纯粹的使用C，完成一个简单的小的学生系统
    功能：
        增删改查
        目前只实现了增
    目的：
        锻炼使用指针，和结构体
        强化关于文件的读写操作
    后期改善目标：
        完善删除和修改功能
        完成头文件和.c文件的分离
        是否可以和CJSON进行整合
        没有处理关于内存泄露问题
    今天：
        完成删查改
*/
#include"stdio.h"
#include"stdlib.h"
#include"string.h"
#include"student.h"


studentTypeDef * studentList;   //全局的链表指针
studentTypeDef * node;          //在进行链表操作的时候，需要的中间变量
char option;                    //取得用户操作选项


int main(int argc, char ** argv)    //这里的参数暂时没有使用
{
    if( initSys()==-1 ) 
    {
	return -1;
    }
    //1.初始化链表
    //initList();
    //2.进行功能选择
    manageList();
    //3.功能处理
    option = getchar();
    getchar();
    while(option!='q' && option!='Q')   //前台程序
    {
      switch(option)
      {
          case '1' : addStudent(); break;
          case '2' : delStudentList(studentList); studentList = NULL; break;
          case '3' : showAllStudent(studentList); break;
          case '4' : delStudent(); break;
          case '5' : find(); break;
   	  case '6' : modifyStudent(); break;
          default : break;
      }
      printf("1--Add  \t\t2--Empty\t\t3--ShowAll\n4--Delete\t\t5--Find  \t\t6--Modify\n");
      option = getchar();
      getchar();
    }
    writeToDoc();
	return 0;
}

//初始化学生链表
void initList()
{
    studentList = (studentTypeDef *)malloc(sizeof(studentTypeDef));
    studentList->name = (char*)malloc(sizeof(char));
    studentList->age = -1;
    studentList->next = NULL;
    studentList->previous = NULL;
    node = studentList;
}


void manageList(void)
{
    printf("**************\n");
    printf("this is students manage system\n");
    printf("1----添加学生\n");
    printf("2----删除列表\n");
    printf("3----显示所有信息\n");
    printf("4----删除学生信息\n"); 
    printf("5----查找学生信息\n");
    printf("6----修改学生信息\n");
    printf("q----退出系统");
    printf("**************\n");
}


void addStudent(void)
{
    if( studentList==NULL )
    {
	initList();
    }
    if( studentList->age == -1 )    //此时对应链表为空的时候
    {
        printf("the name of the student: ");
        scanf("%s", studentList->name);
        studentList->n_len = strlen(studentList->name);
        printf("the age of the studnet: ");
        scanf("%d", &(studentList->age));
        getchar();                  //这里可不可以换一种处理方法
        printf("add successfully\n");
    }
    else                            //进行节点的创建和连接
    {
    studentTypeDef * newStudent;
    newStudent = (studentTypeDef*)malloc(sizeof(studentTypeDef));
    newStudent->name = (char*)malloc(sizeof(char));
    printf("the name of the student: ");
    scanf("%s", newStudent->name);
    newStudent->n_len = strlen(newStudent->name);
    printf("the age of the student: ");
    scanf("%d", &(newStudent->age));
    getchar();
    newStudent->previous = node;
    node->next = newStudent;
    newStudent->next = NULL;
    node = newStudent;
    printf("add successfully\n");
    }
}

void delStudent(void)
{
    char name[10];
    studentTypeDef* temp;
    fprintf(stdout, "%s", "print the name of the student you want to delete: \n");
    scanf("%s", name);
    getchar();
    if( (temp=findStudent(name))!=NULL )
    {
       showStudent(temp);
       fprintf(stdout, "%s", "delete this student? \n");
       option = getchar();
       getchar();
       if(option=='y' || option=='Y')
       {
	   if( temp->previous == NULL )		//如果是头指针
	   {
		studentList = temp->next;
		temp->next->previous = NULL;
	   }
	  else if( temp->next == NULL )		//如果是尾指针
	  {
		temp->previous->next = NULL;
		node = temp->previous;
	  }
	  else 
	  {
           	temp->previous->next = temp->next;
           	temp->next->previous = temp->previous;
	  }
           free(temp);                  //这里进行指针的释放
           fprintf(stdout, "%s", "Done\n");
       }
       else
       {
           return ;
       }
    }
    return ;
}

//实现查找功能
studentTypeDef* findStudent(const char * name)
{
    studentTypeDef * temp = studentList;
    if(temp==NULL)
    {
        fprintf(stdout, "%s", "the list is empty!\n");
        return NULL;
    }
    while(temp!=NULL)
    {
        if( strcmp(name, temp->name)==0 )
        {
	    showStudent(temp);
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}


//包装函数
void find(void)
{
    char name[10];
    studentTypeDef * temp;
    fprintf(stdout, "%s", "please input the name of the student you want to find: \n");
    scanf("%s", name);
    getchar();
    temp = findStudent(name);
    if( temp==NULL ) 
    {
	fprintf(stdout, "%s", "NO SUCH STUDENT!!!\n");
    }
}


void modifyStudent(void)
{
    studentTypeDef * temp;
    char name[10];
    fprintf(stdout, "%s", "please input the name of the student you want to modify: \n");
    scanf("%s", name);
    getchar();
    temp = findStudent(name);
    if( temp==NULL ) 
    {
	fprintf(stdout, "%s", "No such student!!!!\n");
	return ;
    }
    else 
    {
	
        printf("the name of the student: ");
        scanf("%s", temp->name);
        temp->n_len = strlen(temp->name);
        printf("the age of the studnet: ");
        scanf("%d", &(temp->age));
        getchar();                  
    }
    fprintf(stdout, "%s", "MODIFY SUCCESSFULLY!!!\n");
}

void delStudentList(studentTypeDef* students)
{
   if(students->next == NULL)
   {
       free(students->name);
        free(students);
   }
    else 
    {
        delStudentList(students->next);     //使用递归来处理节点空间的释放
        free(students->name);
        free(students);
    }
    printf("delete list successfully\n");
    students = NULL;			   
}
/*
    进行显示学生信息
*/
void showStudent(studentTypeDef* student)
{
    if( student->age == -1)
    {
        printf("链表为空\n");
    }
    else
    {
	    printf("**** **************** ***********\n");
	    printf("**** name: %10s **********\n", student->name);
	    printf("**** age : %10d **********\n", student->age);
	    printf("**** **************** ***********\n");
    }
    
}

/*
    进行显示所有的学生信息
    使用递归
*/
void showAllStudent(studentTypeDef* students)
{
    if(students==NULL)
    {
        printf("链表已删除\n");
        return ;
    }
    else if(students->next!=NULL)
    {
        showAllStudent(students->next);
    }
   showStudent(students); 
}


/*
    对系统完成初始化
    1.  当数据文件不存在的时候
            创建空的数据文件，然后返回，等待退出系统的时候像文件中写入数据
    2.  当数据文件存在的时候
            根据文件中的数据来创建链表
*/
int initSys(void)
{
    FILE * fp;
    studentTypeDef * temp;
    char option;

    temp = (studentTypeDef*)malloc(sizeof(studentTypeDef));
    temp->name = (char*)malloc(sizeof(char));
    fp = fopen("student.dat", "rb");
    if( fp==NULL )
    {
        fprintf(stdout, "%s", "数据文件不存在，是否要创建新的数据文件\n");
        option = getchar();
        getchar();
        if(option == 'y' || option == 'Y')
        {
            createNewDoc();
            return 0;
        }
        else
        {
            return -1;
        }
    }
    else
    {
        initList();
        /*
            这里对头指针进行数据的初始化，之前的initLis只是对指针进行分配了内存空间
        */
        fread(studentList, sizeof(studentTypeDef), 1, fp);
        studentList->name = (char*)malloc(sizeof(char));
        fread(studentList->name, sizeof(char), studentList->n_len, fp);

        while(fread(temp, sizeof(studentTypeDef), 1, fp)==1) //判断是否已经将结构体数据读取完毕
        {
            temp->name = (char*)malloc(sizeof(char));
            fread(temp->name, sizeof(char), temp->n_len, fp);
            node->next = temp;
            temp->previous = node;
            node = temp;
            temp = (studentTypeDef*)malloc(sizeof(studentTypeDef)); //这里需要对temp进行分配新的地址空间，负责只是对空一个地址的内容进行操作
            temp->name = (char*)malloc(sizeof(char));
        }
    }
    fclose(fp); 
    return 0;
}


void createNewDoc(void)
{
    FILE * fp ;
    fp = fopen("student.dat", "wb");
    fclose(fp);
    initList();
}


void writeToDoc(void)
{
    studentTypeDef * temp;
    FILE * fp;
    fp = fopen("student.dat", "wb");
    if(fp==NULL)
    {
        fprintf(stdout, "%s", "文件打开失败\n");
        return;
    }
    temp = studentList;
    while(temp->next!=NULL)
    {
        fwrite(temp, sizeof(studentTypeDef), 1, fp);
        fwrite(temp->name, sizeof(char), temp->n_len, fp);
        temp = temp->next;
    }
    fwrite(temp, sizeof(studentTypeDef), 1, fp);
    fwrite(temp->name, sizeof(char), temp->n_len, fp);
    fclose(fp);
    fprintf(stdout, "%s", "数据写入完成\n");
}
