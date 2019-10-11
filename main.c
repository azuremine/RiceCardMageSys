#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<memory.h>
struct foodcard
{
    int num;
    char name[20];
    int money;
    char guashi[5];
    struct foodcard *next;
};
struct foodcard *Create_fc_Doc();                                        //建立饭卡文件并输入信息
struct foodcard *buy(struct foodcard *head);                             //买饭
struct foodcard *xuqian(struct foodcard *head);                          //续钱
struct foodcard *increasenfc(struct foodcard *head);                     //添加新饭卡
struct foodcard *deleteDoc(struct foodcard *head);                       //注销旧饭卡
struct foodcard *set_or_relieve(struct foodcard *head);                  //设置和解除挂失
void Print_foodcard(struct foodcard *head);                              //遍历
struct foodcard *insertDoc(struct foodcard *head,struct foodcard *stud); //饭卡资料的插入
struct foodcard *read_Doc();                                             //读取数据
void save_Doc(struct foodcard*head);                                     //保存数据并关闭文件
int main()
{
    FILE *fp,*fp1;
    struct foodcard *head,*p;
    int num;
    int choice,money;
    char name[20];
    char guashi[5];
    int size=sizeof(struct foodcard);
    head=read_Doc();
    do
    {
        printf("……………………………………………………\n");
        printf(".         请选择选项编号(0~7)           .\n");
        printf("……………………………………………………\n");
        printf(".         1——建立饭卡文件             .\n");
        printf(".         2——买饭                     .\n");
        printf(".         3——续钱                     .\n");
        printf(".         4——添加新饭卡               .\n");
        printf(".         5——注销旧饭卡               .\n");
        printf(".         6——设置与解除挂失           .\n");
        printf(".         7——查看所有饭卡资料         .\n");
        printf(".         0——退出系统                 .\n");
        printf("……………………………………………………\n");
        printf("请输入编号：");
        scanf("%d",&choice);
        switch(choice){
        case 1:
            head=Create_fc_Doc();
            save_Doc(head);
            break;
        case 2:
            head=buy(head);
            break;
        case 3:
            head=xuqian(head);
            break;
        case 4:
            head=increasenfc(head);
            break;
        case 5:
            head=deleteDoc(head);
            break;
        case 6:
            head=set_or_relieve(head);
            break;
        case 7:
            Print_foodcard(head);
            break;
        case 0:
            break;
        }
    }while(choice!=0);
    printf("按任意键退出程序！\n");
    save_Doc(head);
    return 0;
}
struct foodcard*Create_fc_Doc()                                          //简历发卡文件(检查饭卡号已存在）
{
    struct foodcard *head,*p,*p1;
    int num;
    char name[20];
    int money;
    char guashi[5];
    int size=sizeof(struct foodcard);
    head=NULL;
    printf("注：若饭卡号为0或负数，则返回主菜单！\n");
    printf("请输入饭卡号：\n");
    scanf("%d",&num);
    if(num<=0)
        return NULL;                                      //如果第一次饭卡号就输入0，则返回NULL，结束Creat_fc_Doc函数并返回主函数，没有数据保存
    else{
            printf("请输入姓名：\n");
            scanf("%s",name);
            printf("请输入金额：\n");
            scanf("%d",&money);
            printf("请输入挂失信息（y/n）：\n");
            scanf("%s",guashi);
            while(strcmp(guashi,"y")!=0&&strcmp(guashi,"n")!=0){
                printf("挂失信息只可以输入（y/n），请重新输入！！\n");
                scanf("%s",guashi);
            }
    }
    while(num>0){
            p=(struct foodcard *)malloc(size);            //在内存动态存储区申请一定的空间，成功则返回指向分配内存空间的起始地址的指针
            p1=p;
            p->num=num;
            strcpy(p->name,name);
            p->money=money;
            strcpy(p->guashi,guashi);
            head=insertDoc(head,p);
            printf("注：饭卡号输入0或负数则返回主菜单！\n");
            printf("请输入饭卡号：\n");
            scanf("%d",&num);
            while(p1!=NULL){
                while(p1->num==num){
                    printf("注：饭卡号输入0或负数则返回主菜单！\n");
                    printf("饭卡号已存在！请重新输入饭卡号：\n");
                    scanf("%d",&num);
                }
                p1=p1->next;
                if(p1==NULL)break;
            }
            if(num<=0)
                return head;                       //第一次录入饭卡资料成功，已经生成链表，第二次输入饭卡号为0，返回0，结束Creat_fc_Doc函数并返回主函数
            printf("请输入姓名：\n");
            scanf("%s",name);
            printf("请输入金额：\n");
            scanf("%d",&money);
            printf("请输入挂失信息（y/n）：\n");
            scanf("%s",guashi);
            while(strcmp(guashi,"y")!=0&&strcmp(guashi,"n")!=0){
                printf("挂失信息只可以输入（y/n），请重新输入！！\n");
                scanf("%s",guashi);
            }
    }
    return head;
}
struct foodcard *insertDoc(struct foodcard *head,struct foodcard *stud)  //插入操作
{
    struct foodcard *ptr,*ptr1,*ptr2;
    ptr2=head;
    ptr=stud;                       //ptr指向带插入的新的饭卡记录节点
    //原链表为空时的插入
    if(head==NULL){
        head=ptr;                   //新插入节点为头结点
        head->next=NULL;
    }
    //原链表不为空时的插入（分两种情况（只有一个结点和有多个结点的情况）
    else {
        while((ptr->num>ptr2->num)&&(ptr2->next!=NULL)){                        //进while语句的前提是传递进来的num值比链表有节点的num值大而且此链表有两个或以上结点
            ptr1=ptr2;               //ptr1指向ptr2
            ptr2=ptr2->next;         //ptr2指向下一个结点,即ptr1和pyr2个后移一个位置
        }
        if(ptr->num<=ptr2->num){     //如果ptr指向的结点在ptr2指向结点的前面
            if(head==ptr2)head=ptr;  //前提：ptr指向的结点在ptr2指向结点的前面。
            else ptr1->next=ptr;
            ptr->next=ptr2;
        }
        else {
            ptr2->next=ptr;
            ptr->next=NULL;
        }
    }
    return head;
}
struct foodcard *deleteDoc(struct foodcard *head)                        //注销旧饭卡(检查饭卡存不存在）
{
    struct foodcard *ptr1,*ptr2,*ptr3,*p1;
    int num1;
    if(head==NULL){
        printf("没有饭卡文件！\n");
        return head;
    }
    printf("请输入想要注销的饭卡号：\n");
    scanf("%d",&num1);
    p1=head;
    while(p1!=NULL){
        if(p1->num==num1)break;
        p1=p1->next;
        while(p1==NULL){
            printf("饭卡号不存在！\n");
            return head;
        }
    }
    while(head!=NULL&&head->num==num1){               //这里的意思是链表不为空，并且要删除的为头结点，ptr2=head，head指向next域，然后释放ptr2
        ptr2=head;
        head=head->next;
        free(ptr2);
        printf("饭卡注销成功！\n");
    }
    if(head==NULL){                //如果只有一个结点那就跳出函数
        return NULL;
    }
    ptr1=head;
    ptr2=head->next;
    while(ptr2!=NULL){               //进入的前提：该链表有两个或两个以上结点
        if(ptr2->num==num1){         //结点为要删的结点
            ptr1->next=ptr2->next;   //第一个结点的尾地址指向ptr2的next域
            free(ptr2);              //释放ptr2指向的结点
            printf("饭卡注销成功！\n");
        }
        else ptr1=ptr2;              //结点不是要删除的结点  继续寻找
        ptr2=ptr1->next;             //ptr2指向ptr1的next域
    }
    return head;
}
void Print_foodcard(struct foodcard *head)                               //饭卡资料遍历
{
    struct foodcard *ptr;
    if(head==NULL){
        printf("没有饭卡数据！\n");
       return;
    }
    printf("\n饭卡号          姓名            金额            是否挂失\n");
    for(ptr=head;ptr!=NULL;ptr=ptr->next)
        printf("%d\t\t%s\t\t%d\t\t%s\n",ptr->num,ptr->name,ptr->money,ptr->guashi);
}
void save_Doc(struct foodcard *head)                                     //写入链表到文件
{
    struct foodcard *p;
    FILE *fp;
    p=head;
    if((fp=fopen("card.dat","wb"))==NULL){
        printf("打开文件失败！\n");
        exit(0);
    }
    while(p!=NULL){
        fprintf(fp,"%d %s %d %s ",p->num,p->name,p->money,p->guashi);
        p=p->next;
    }
    fprintf(fp,"\n");
    fclose(fp);
}
struct foodcard *read_Doc()                         //从文件读入链表
{
    FILE *fp;
    int size=sizeof(struct foodcard);
    struct foodcard *head=(struct foodcard *)malloc(size);
    int num;
    char name[20];
    char guashi[5];
    int money;
    struct foodcard *p,*p1;
    p=head;
    fp=fopen("card.dat","rb");
    if(fp==NULL){
        printf("没有饭卡文件！请建立饭卡文件！\n");
        return NULL;
    }
    else printf("已有饭卡文件！\n");
    while(fscanf(fp,"%d%s%d%s",&num,name,&money,guashi)!=EOF){
            p1=(struct foodcard *)malloc(size);
            p1->num=num;
            strcpy(p1->name,name);
            p1->money=money;
            strcpy(p1->guashi,guashi);
            p->next=p1;
            p=p1;
        }
    p->next=NULL;
    fclose(fp);
    head=head->next;
    return head;
}
struct foodcard *increasenfc(struct foodcard *head)                      //添加新饭卡(检查饭卡号已存在）
{
    struct foodcard *p,*p1;
    int num;
    char name[20];
    int money;
    char guashi[5];
    int size=sizeof(struct foodcard);
    p1=head;
    if(p1==NULL){
        printf("没有饭卡文件！\n");
        return head;
    }
    printf("请输入要添加的新饭卡的卡号:\n");
    scanf("%d",&num);
    while(p1!=NULL){
        if(p1->num==num){
            printf("饭卡号已存在！\n");
            return head;
        }
        p1=p1->next;
        if(p1==NULL)break;
    }
    while(num<=0){
         printf("饭卡号不能为0或负数，请重新输入饭卡号！\n");
         scanf("%d",&num);
    }
    printf("请输入姓名：\n");
    scanf("%s",name);
    printf("请输入金额：\n");
    scanf("%d",&money);
    printf("请输入挂失信息（y/n)：\n");
    scanf("%s",guashi);
    while(strcmp(guashi,"y")!=0&&strcmp(guashi,"n")!=0){
          printf("挂失信息只可以输入（y/n），请重新输入！！\n");
          scanf("%s",guashi);
    }
    p=(struct foodcard *)malloc(size);
    p->num=num;
    strcpy(p->name,name);
    p->money=money;
    strcpy(p->guashi,guashi);
    head=insertDoc(head,p);
    printf("添加成功！\n");
    return head;
}
struct foodcard *buy(struct foodcard *head)                              //买饭(检查饭卡存不存在）
{
    int num,num1,money;
    struct foodcard *p;
    p=head;
    if(p==NULL){
        printf("没有饭卡文件！\n");
        return head;
    }
    printf("请输入需要买饭的饭卡号：");
    scanf("%d",&num1);
    while(p!=NULL){
        if(p->num==num1)break;
        p=p->next;
        while(p==NULL){
            printf("饭卡号不存在！\n");
            return head;
        }
    }
    if(p->num==num1){
        if(strcmp(p->guashi,"y")==0){
            printf("本卡已挂失！不能买饭！\n");
            return head;
        }
            printf(">>> 饭卡余额：%d <<<\n",p->money);
        if(p->money<5){
            printf("余额不足，请续钱！\n");
            return head;
        }
        else{
            printf("请输入买饭饭费：");
            scanf("%d",&money);
            if(money>p->money){
                printf("饭费超过余额！\n");
                return head;
            }
            p->money=p->money-money;
            printf(">>> 买饭后饭卡余额：%d <<<\n",p->money);
        }
    }
    return head;
}
struct foodcard *xuqian(struct foodcard *head)                           //续钱(检查饭卡存不存在）
{
    int num,num1,money;
    struct foodcard *p;
    p=head;
    if(p==NULL){
        printf("没有饭卡文件！\n");
        return head;
    }
    printf("请输入饭卡卡号：");
    scanf("%d",&num1);
    while(p!=NULL){
        if(p->num==num1)break;
        p=p->next;
        while(p==NULL){
            printf("饭卡号不存在！\n");
            return head;
        }
    }
    if(p->num==num1){
        if(strcmp(p->guashi,"y")==0){
            printf("本卡已挂失！不能续钱！\n");
            return head;
        }
        printf(">>> 饭卡余额：%d <<<\n",p->money);
        printf("请输入续钱金额：\n");
        scanf("%d",&money);
        p->money=p->money+money;
        printf(">>> 续钱后饭卡余额：%d <<<\n",p->money);
    }
    return head;
}
struct foodcard *set_or_relieve(struct foodcard *head)                   //设置和解除挂失(检查饭卡存不存在）
{
    struct foodcard *p;
    int num1;
    char guashi[5];
    p=head;
    if(p==NULL){
        printf("没有饭卡文件！\n");
        return head;
    }
    printf("请输入需要设置或解除挂失的饭卡号：\n");
    scanf("%d",&num1);
    while(p!=NULL){
        if(p->num==num1)
            break;
        p=p->next;
        while(p==NULL){
            printf("饭卡号不存在！\n");
            return head;
        }
    }
    if(p->num==num1){
        printf("请输入y（设置挂失）或n（解除挂失）：\n");
        scanf("%s",guashi);
        while(strcmp(guashi,"y")!=0&&strcmp(guashi,"n")!=0){
            printf("挂失信息只可以输入（y/n），请重新输入！！\n");
            scanf("%s",guashi);
        }
        if(strcmp(guashi,"y")==0){
            if(strcmp(p->guashi,"y")==0){
               printf("此卡已经处于挂失状态！\n");
                return head;
            }
            else
                strcpy(p->guashi,guashi);
        }
        else{
            if(strcmp(p->guashi,"n")==0){
                printf("此卡已经处于不挂失状态！\n");
                return head;
            }
            else
                strcpy(p->guashi,guashi);
        }
        printf("更新挂失信息成功！\n");
    }
    return head;
}
