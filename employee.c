#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct employee
{
    int num;
    char duty[10];
    char name[10];
    char sex[3];
    int age;
    char edu[10];
    int salary;
    char tel_office[13];
    char tel_home[13];
    char mobile[13];
    char qq[11];
    char address[31];
    struct employee *next;    
}EMP;
    
    char password[9];
    EMP *emp_first,*emp_end;
    char gsave,gfirst;
    
    void addemp(void);
    void findemp(void);
    void listemp(void);
    void modifyemp(void);
    void summaryemp(void);
    void delemp(void);
    void resetpwd(void);
    void readdata(void);
    void savedata(void);
    int modi_age(int s);
    int modi_salary(int s);
    char *modi_field(char *field,char *s,int n);
    EMP *findname(char *name);
    EMP *findnum(int num);
    EMP *findtelephone(char *name);
    EMP *findqq(char *name);
    void displayemp(EMP *emp,char *field,char *name);
    void checkfirst(void);
    void bound(char ch,int n);
    void login();
    void menu();



void addemp()
{
    FILE *fp;
    EMP *emp1;
    int i=0;
    char choice='y';
    
    if((fp=fopen("employee.dat","ab"))==NULL)
    {
        printf("error can't find employee.dat！\n");
        getchar();
        return;                                         
    }     
    
    do{
         i++;
         emp1=(EMP *)malloc(sizeof(EMP));
         
         if(emp1==NULL)
         {
             printf("Memory allocation failure, press any key to exit!\n");
             getchar();
             return;              
         }
         printf("Please enter number %d information of the employees,\n",i);
         bound('_',30);
         printf("number：");
         scanf("%d",&emp1->num);
         
         printf("duty：");
         scanf("%s",&emp1->duty);
         
         printf("name：");
         scanf("%s",&emp1->name);
         
         printf("sex：");
         scanf("%s",&emp1->sex);
         
         printf("age：");
         scanf("%d",&emp1->age);
         
         printf("edu：");
         scanf("%s",&emp1->edu);
         
         printf("salary：");
         scanf("%d",&emp1->salary);
         
         printf("tel_office：");
         scanf("%s",&emp1->tel_office);
         
         printf("tel_home：");
         scanf("%s",&emp1->tel_home);
         
         printf("mobile：");
         scanf("%s",&emp1->mobile);
         
         printf("QQ:");
         scanf("%s",&emp1->qq);
         
         printf("address：");
         scanf("%s",&emp1->address);
         
         emp1->next=NULL;
         if(emp_first==NULL)
         {
             emp_first=emp1;
             emp_end=emp1;                   
         }else {
             emp_end->next=emp1;
             emp_end=emp1;      
         }
         
         fwrite(emp_end,sizeof(EMP),1,fp);
         
         gfirst=0;
         printf("\n");
         bound('_',30);
         printf("\n continue or not?(y/n)");
         fflush(stdin);
         choice=getchar();
         
         if(toupper(choice)!='Y')
         {
             fclose(fp);
             printf("\n finished,press any key to exit\n");
             getchar();
             return;                        
         }
         
         system("cls");      
    }while(1);
}



void bound(char ch,int n)
{
   while(n--)
       putchar(ch);
       
   printf("\n");
   return;     
}


/*首次使用，进行用户信息初始化*/
void checkfirst()
{
    FILE *fp,*fp1; 
    char pwd[9],pwd1[9],pwd2[9],pwd3[9],ch;
    int i;
    char strt='8';    
    
    if((fp=fopen("config.bat","rb"))==NULL)
    {
        printf("\n please initialize！\n");
        bound('_',50);
        getchar();
        
        do{
            printf("\nSet the password, Don't more than eight numbers,please");
            for(i=0;i<8&&((pwd[i]=getchar())!=13);i++)
                putchar('*');
            printf("\n confirm password:");
            for(i=0;i<8&&((pwd1[i]=getchar())!=13);i++) 
                putchar('*');    
                
            pwd[i]='\0';  
            pwd1[i]='\0';
            
            if(strcmp(pwd,pwd1)!=0)
                printf("\n Enter the password twice inconsistent, please try again!\n\n");
            else break;
            
        }while(1);
        
        if((fp1=fopen("config.bat","wb"))==NULL)
        {
            printf("\n The system creates failure, press any key to exit!");
            getchar();
            exit(1);                                        
        }
        
        i=0;
        while(pwd[i])
        {
                 
            pwd2[i]=(pwd[i]^ strt);        
            putw(pwd2[i],fp1);
            i++;             
        }
        
        fclose(fp1);
        printf("\n\n System initialization is successful, press any key to exit and re-enter!\n");
        getchar();
        exit(1);
        
    }else{
        i=0;
        while(!feof(fp)&&i<8)
            pwd[i++]=(getw(fp)^strt);
            
            
        pwd[i]='\0';
        
        if(i>=8) i--;
        while(pwd[i]!=-1&&i>=0)
            i--;
        
        pwd[i]='\0';
        strcpy(password,pwd); 
    } 
}


void delemp()
{
    int findok=0;
    EMP *emp1,*emp2;
    char name[10],choice;
    
    system("cls");
    printf("\n Enter the name of the employee to be deleted：");
    scanf("%s",name);
    
    emp1=emp_first;
    emp2=emp1;
    while(emp1)
    {
        if(strcmp(emp1->name,name)==0)
        {
            findok=1;
            system("cls");
            
            printf("employee:there are the information of %s",emp1->name);
            bound('_',40);
            printf("job number:%d\n",emp1->num);
            printf("duty:%s\n",emp1->duty);
            printf("name:%s\n",emp1->name);
            printf("sex:%s\n",emp1->sex);
            printf("age:%d\n",emp1->age);
            printf("edu:%s\n",emp1->edu);
            printf("salary:%d\n",emp1->salary);
            printf("tel_office：%s\n",emp1->tel_office);
            printf("tel_home：%s\n",emp1->tel_home);
            printf("mobile:%s\n",emp1->mobile);
            printf("QQ:%s\n",emp1->qq);
            printf("address:%s\n",emp1->address);  
            bound('_',40);
            printf("Are you sure you want to delete the employee?(y/n)");
            
			fflush(stdin);
            choice=getchar();
            
            if(choice!='y' && choice!='Y') return;
            if(emp1==emp_first) emp_first=emp1->next;
            else emp2->next=emp1->next;
            
            free(emp1);
            gsave=1;
            savedata();
            return;                           
        }  else{        
            emp2=emp1;
            emp1=emp1->next;
        }
    }    
    if(!findok)
    {
        bound('_',40);
        printf("\n can't find the information of %s!\n",name);
        getchar();           
    } 
    return;
}


void displayemp(EMP *emp,char *field,char *name)
{
    if(emp)
    {
        printf("\n %s:%s as followed:\n",field,name);
        bound('_',30); 
        printf("job number:%d\n",emp->num);
        printf("duty:%s\n",emp->duty);
        printf("name:%s\n",emp->name);
        printf("sex:%s\n",emp->sex);
        printf("age:%d\n",emp->age);
        printf("edu:%s\n",emp->edu);
        printf("salary:%d\n",emp->salary);
        printf("tel_office：%s\n",emp->tel_office);
        printf("tel_home：%s\n",emp->tel_home);
        printf("mobile:%s\n",emp->mobile);
        printf("QQ：%s\n",emp->qq);
        printf("address:%s\n",emp->address);
        bound('_',30);      
    }else {
    bound('_',40);
    printf("No%s:we can't find %s in the library ! please confirm!",field,name);
    }
    return;
}


EMP *findname(char *name)
{
    EMP *emp1;
    emp1=emp_first;
    
    while(emp1)
    {
        if(strcmp(name,emp1->name)==0)  return emp1;
        emp1=emp1->next;          
    }    
    return NULL;
}


EMP *findnum(int num)
{
   EMP *emp1;
   
   emp1=emp_first;
   while(emp1)
   {
       if(num==emp1->num)  return emp1;
       emp1=emp1->next;           
   }  
   return NULL;  
}

EMP *findtelephone(char *name)
{
     EMP *emp1;
     
     emp1=emp_first;
     while(emp1)
     {
         if((strcmp(name,emp1->tel_office)==0)||
         (strcmp(name,emp1->tel_home)==0)||
         (strcmp(name,emp1->mobile)==0))
         return emp1;
         emp1=emp1->next;
                 
     }  
      return NULL;       
}


EMP *findqq(char *name)
{
    EMP *emp1;
    
    emp1=emp_first;
    while(emp1)
    {
        if(strcmp(name,emp1->qq)==0)  return emp1;
        emp1=emp1->next;           
    }  
    return NULL;  
}


void findemp()
{
     int choice,ret=0,num;
     char str[13];
     EMP *emp1;
     
     system("cls");
     
     do{
         printf("\t Check employee information \n");
         bound('_',30);
         printf("\t1.Query by name\n");
         printf("\t2.Query by number\n");
         printf("\t3.Query by phone number\n");
         printf("\t4.Query by QQ\n");
         printf("\t0.Return to main menu\n");
         bound('_',30);
         printf("\n Please select the menu:");
         
         do{
             fflush(stdin);
             choice=getchar();
             system("cls");
             
             switch(choice)
             {
                 case '1':
                      printf("\n Enter the employee's name:");
                      scanf("%s",str);
                      
                      emp1=findname(str);
                      displayemp(emp1,"姓名",str);
                      getchar();
                      break; 
                      
                 case '2':
                      printf("\n Enter the employee's job number"); 
                      scanf("%d",&num);  
                      emp1=findnum(num);
                      sprintf(num,str,10);
                      displayemp(emp1,"job number",str);
                      getchar();
                      break;
                      
                  case '3':
                       printf("\n Enter the employee's phone number:");
                       scanf("%s",str);  
                       emp1=findtelephone(str); 
                       displayemp(emp1,"phone number",str);
                       getchar();
                       break;
                       
                  case '4':
                       printf("\n Enter the employee's QQ:");
                       scanf("%s",str);
                       
                       emp1=findqq(str);
                       displayemp(emp1,"QQ",str);
                       getchar();
                       break;
                       
                   case '0':
                        ret=1;
                        break;          
             }                         
         }while(choice<'0'||choice>'4');
         
         system("cls");
         if(ret) break;
     }while(1);         
}


void listemp()
{
    EMP *emp1;
    
    printf("\n Library staff list\n");
    bound('_',40);
    emp1=emp_first;
    
    while(emp1) 
    {
        printf("job number：%d\n",emp1->num);
        printf("duty：%s\n",emp1->duty);
        printf("name：%s\n",emp1->name);
        printf("sex：%s\n",emp1->sex);
        printf("age：%d\n",emp1->age);
        printf("edu：%s\n",emp1->edu);
        printf("salary：%d\n",emp1->salary);
        printf("tel_office：%s\n",emp1->tel_office);
        printf("tel_home：%s\n",emp1->tel_home);
        printf("mobile：%s\n",emp1->mobile);
        printf("QQ：%s\n",emp1->qq);
        printf("address:%s\n",emp1->address);  
        bound('_',40);
        emp1=emp1->next;      
    }    
    printf("\n press any key to exit !\n");
    getchar();
    return;
}


/*检测登录密码*/
void login()
{
    int i,n=3;
    char pwd[9];
    
    do{
        printf("please enter the password:");
        for(i=0;i<8 && ((pwd[i]=getchar())!=13);i++)
            putchar('*');
        
        pwd[i]='\0';
        if(strcmp(pwd,password))
        {
            printf("\n error please try again!\n");
            system("cls");
            n--;                        
        }else break;
    } while(n>0);
    
    if(!n)
    {
        printf("Please quit, you enter the wrong password three times！");
        getchar();
        exit(1);      
    }
}


void menu()
{
    char choice;
    
    system("cls");
    
    do{
        printf("\t Employee Management System\n");
        bound('_',40);
        printf("\t1.Enter employee information\n");
        printf("\t2.Check employee information\n");
        printf("\t3.Display employee information\n");
        printf("\t4.Modify Employee Information\n");
        printf("\t5.Delete employee information\n");
        printf("\t6.Statistics Employee Information\n");
        printf("\t7.Resetting the system password\n");
        printf("\t0.Exit system\n");
        bound('_',40);
        printf("\n Please select!");
        
        do{
            fflush(stdin);
            choice=getchar();
            system("cls");
            
            switch(choice)
            {
                case '1':
                   addemp();
                   break;
                case '2':
                   if(gfirst)
                   {
                       printf("No employee information system information, please add employee information!\n");
                       getchar();
                       break;          
                   }  
                   
                   findemp();
                   break;
                case '3':
                   if(gfirst)
                   {
                       printf("No employee information system information, please add employee information!\n");
                       getchar();
                       break;       
                   }
                   
                   listemp();
                   break;
               case '4':
                   if(gfirst)
                   {
                       printf("No employee information system information, please add employee information!\n");
                       getchar();
                       break;       
                   }
                   
                   modifyemp();
                   break;
               case '5':
                    if(gfirst)
                   {
                       printf("No employee information system information, please add employee information!\n");
                       getchar();
                       break;       
                   }
                   
                   delemp();
                   break;
               case '6':
                    if(gfirst)
                   {
                       printf("No employee information system information, please add employee information!\n");
                       getchar();
                       break;       
                   }
                   
                   summaryemp();
                   break; 
               case '7':
                   resetpwd();
                   break;
               case '0':
                   savedata();
                   exit(0);        
            }                             
        } while(choice<'0'||choice>'7');  
        
        
         system("cls");        
    }while(1);    
}


int modi_salary(int salary){
    int newsalary;
    printf("The original number of salary:%d",salary);
    printf("The new salary:");
    scanf("%d",&newsalary);
    
    return(newsalary);
}



int modi_age(int age){
    int newage;
    printf("The original age：%d",age);
    printf("new age：");
    scanf("%d",&newage);
    
    return(newage);
}

char *modi_field(char *field,char *content,int len)
{
     char *str;
     str=malloc(sizeof(char)*len);
     if(str==NULL)
     {
         printf("Memory allocation failed, press any key to exit!");
         getchar();
         return NULL;             
     }
     printf("%s was:%s before\n",field,content);
     printf("Modified to(Not more than %d characters!):",len);
     scanf("%s",str);
     
     return str;
}

void modifyemp()
{
     EMP *emp1;
     char name[10],*newcontent;
     int choice;
     
     printf("\n please enter the name of the employee who you want to modify:");
     scanf("%s",&name);
     
     emp1=findname(name);
     displayemp(emp1,"name",name);
     
     if(emp1)
     {
         printf("\n please select\n");
         bound('_',40);
         printf("1.duty                    2.age\n");
         printf("3.edu                     4.salary\n");
         printf("5.tel_office              6.tel_home\n");
         printf("7.mobile                  8.QQ \n");
         printf("9.address                 0.exit\n  ");
         bound('_',40);
         
         do{
             fflush(stdin);
             choice=getchar();
             switch(choice) 
             {
                 case '1':
                      newcontent=modi_field("duty",emp1->duty,10);
                      if(newcontent!=NULL)
                      {
                          strcpy(emp1->duty,newcontent);
                          free(newcontent);                    
                      } 
                      break;
                 case '2':
                      emp1->age=modi_age(emp1->age);
                      break;
                  case '3':
                      newcontent=modi_field("edu",emp1->edu,10);
                      if(newcontent!=NULL)
                      {
                          strcpy(emp1->edu,newcontent);
                          free(newcontent);                    
                      } 
                      break;
                  case '4':
                      emp1->salary=modi_salary(emp1->salary);
                      break;
                 case '5':
                      newcontent=modi_field("tel_office",emp1->tel_office,13);
                      if(newcontent!=NULL)
                      {
                          strcpy(emp1->tel_office,newcontent);
                          free(newcontent);                    
                      } 
                      break;
                 case '6':
                      newcontent=modi_field("tel_home",emp1->tel_home,13);
                      if(newcontent!=NULL)
                      {
                          strcpy(emp1->tel_home,newcontent);
                          free(newcontent);                    
                      } 
                      break;
                  case '7':
                      newcontent=modi_field("mobile",emp1->mobile,12);
                      if(newcontent!=NULL)
                      {
                          strcpy(emp1->mobile,newcontent);
                          free(newcontent);                    
                      } 
                      break;
                  case '8':
                      newcontent=modi_field("QQ",emp1->qq,10);
                      if(newcontent==NULL)
                      {
                          strcpy(emp1->qq,newcontent);
                          free(newcontent);                    
                      } 
                      break;  
                  case '9':
                      newcontent=modi_field("address",emp1->address,30);
                      if(newcontent!=NULL)
                      {
                          strcpy(emp1->address,newcontent);
                          free(newcontent);                    
                      } 
                      break;     
                  case '0':
                      return;             
             }             
         }while(choice<'0' || choice>'9');
         
         gsave=1;
         savedata();
         printf("\n finished press any key to exit\n");
         getchar();
     }  
     return;   
}



/*读取数据*/ 
void readdata(void)
{
    FILE *fp;
    EMP *emp1;
    
    if((fp=fopen("employee.dat","rb"))==NULL)
    {
        gfirst=1;
        return;                                        
    }     
    
    while(!feof(fp))
    {
        emp1=(EMP *)malloc(sizeof(EMP));
        if(emp1==NULL)
        {
            printf("Memory allocation failure!\n");
            getchar();
            return;              
        }          
        
        fread(emp1,sizeof(EMP),1,fp);
        if(feof(fp))  break;
        
        if(emp_first==NULL)
        {
           emp_first=emp1;
           emp_end=emp1;                   
        }else{
            emp_end->next=emp1;
            emp_end=emp1;   
        }
        emp_end->next=NULL;
    }
    gfirst=0;
    fclose(fp);
}


void resetpwd()
{
    char pwd[9],pwd1[9],ch;
    int i;
    FILE *fp1;
    
    system("cls");
    
    printf("\n Please enter your old password:\n");
     for(i=0;i<8 && ((pwd[i]=getchar())!=13);i++)
            putchar('*');
            
        pwd[i]='\0';
        if(strcmp(password,pwd)!=0)
        {
            printf("\n error,press any key to exit!\n");
            getchar();
            return;             
        }   
     do{
         printf("\n set a new password, please don't beyond 8 numbers:");
            for(i=0;i<8&&((pwd[i]=getchar())!=13);i++)
                putchar('*');
            printf("\n confirm the password:");
            for(i=0;i<8&&((pwd1[i]=getchar())!=13);i++) 
                putchar('*');    
                
            pwd[i]='\0';  
            pwd1[i]='\0';
            
            if(strcmp(pwd,pwd1)!=0)
                printf("\n Enter the password twice inconsistent, please try again!\n\n");
            else break;
            
        }while(1);
        
        if((fp1=fopen("config.bat","wb"))==NULL)
        {
            printf("\n The system creates failure, press any key to exit!");
            getchar();
            exit(1);                                        
        }
        
        i=0;
        while(pwd[i])
        {
            putw(pwd[i],fp1);
            i++;             
        }
        
        fclose(fp1);
        printf("\n Password changed successfully, press any key to exit!\n");
        getchar();
        return;       
}


void savedata()
{
      FILE *fp;
      EMP *emp1;
      
      if(gsave==0) return;
      
      if((fp=fopen("employee.dat","wb"))==NULL)
      {
          printf(" Open the file employee.dat wrong!\n");
          getchar();
          return;                                         
      }   
      
      emp1=emp_first;
      while(emp1)
      {
          fwrite(emp1,sizeof(EMP),1,fp);
          emp1=emp1->next;          
      }
      
      gsave=0;
      fclose(fp);
}


void summaryemp()
{
   EMP *emp1;
   int sum=0,num=0,man=0,woman=0;
   
   emp1=emp_first;
   while(emp1)
   {
       num++;
       sum+=emp1->salary;
       char strw[2];
       strncpy(strw,emp1->sex,2);
       if((strcmp(strw,"ma")==0)||(strcmp(emp1->sex,"man")==0)) man++;
       else woman++;
       emp1=emp1->next;          
   }     
   
   printf("\n There are statistics related to the staff!\n");
   bound('_',40);
   printf("Total number of employees:%d\n",num);
   printf("The total number of salary employees are:%d\n",sum);
   printf("Male employees are:%d\n",man);
   printf("Number of female employees:%d\n",woman);
   bound('_',40);
   printf("Press any key to exit!\n");
   getchar();
   return;
}


int main(void)
{
  emp_first=emp_end=NULL;
  gsave=gfirst=0;
  
  checkfirst();
  login();
  readdata();
  menu();
  system("PAUSE");	
  return 0;
}
