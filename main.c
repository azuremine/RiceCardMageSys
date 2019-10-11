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
struct foodcard *Create_fc_Doc();                                        //���������ļ���������Ϣ
struct foodcard *buy(struct foodcard *head);                             //��
struct foodcard *xuqian(struct foodcard *head);                          //��Ǯ
struct foodcard *increasenfc(struct foodcard *head);                     //����·���
struct foodcard *deleteDoc(struct foodcard *head);                       //ע���ɷ���
struct foodcard *set_or_relieve(struct foodcard *head);                  //���úͽ����ʧ
void Print_foodcard(struct foodcard *head);                              //����
struct foodcard *insertDoc(struct foodcard *head,struct foodcard *stud); //�������ϵĲ���
struct foodcard *read_Doc();                                             //��ȡ����
void save_Doc(struct foodcard*head);                                     //�������ݲ��ر��ļ�
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
        printf("����������������������������������������\n");
        printf(".         ��ѡ��ѡ����(0~7)           .\n");
        printf("����������������������������������������\n");
        printf(".         1�������������ļ�             .\n");
        printf(".         2������                     .\n");
        printf(".         3������Ǯ                     .\n");
        printf(".         4��������·���               .\n");
        printf(".         5����ע���ɷ���               .\n");
        printf(".         6��������������ʧ           .\n");
        printf(".         7�����鿴���з�������         .\n");
        printf(".         0�����˳�ϵͳ                 .\n");
        printf("����������������������������������������\n");
        printf("�������ţ�");
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
    printf("��������˳�����\n");
    save_Doc(head);
    return 0;
}
struct foodcard*Create_fc_Doc()                                          //���������ļ�(��鷹�����Ѵ��ڣ�
{
    struct foodcard *head,*p,*p1;
    int num;
    char name[20];
    int money;
    char guashi[5];
    int size=sizeof(struct foodcard);
    head=NULL;
    printf("ע����������Ϊ0�������򷵻����˵���\n");
    printf("�����뷹���ţ�\n");
    scanf("%d",&num);
    if(num<=0)
        return NULL;                                      //�����һ�η����ž�����0���򷵻�NULL������Creat_fc_Doc������������������û�����ݱ���
    else{
            printf("������������\n");
            scanf("%s",name);
            printf("�������\n");
            scanf("%d",&money);
            printf("�������ʧ��Ϣ��y/n����\n");
            scanf("%s",guashi);
            while(strcmp(guashi,"y")!=0&&strcmp(guashi,"n")!=0){
                printf("��ʧ��Ϣֻ�������루y/n�������������룡��\n");
                scanf("%s",guashi);
            }
    }
    while(num>0){
            p=(struct foodcard *)malloc(size);            //���ڴ涯̬�洢������һ���Ŀռ䣬�ɹ��򷵻�ָ������ڴ�ռ����ʼ��ַ��ָ��
            p1=p;
            p->num=num;
            strcpy(p->name,name);
            p->money=money;
            strcpy(p->guashi,guashi);
            head=insertDoc(head,p);
            printf("ע������������0�����򷵻����˵���\n");
            printf("�����뷹���ţ�\n");
            scanf("%d",&num);
            while(p1!=NULL){
                while(p1->num==num){
                    printf("ע������������0�����򷵻����˵���\n");
                    printf("�������Ѵ��ڣ����������뷹���ţ�\n");
                    scanf("%d",&num);
                }
                p1=p1->next;
                if(p1==NULL)break;
            }
            if(num<=0)
                return head;                       //��һ��¼�뷹�����ϳɹ����Ѿ����������ڶ������뷹����Ϊ0������0������Creat_fc_Doc����������������
            printf("������������\n");
            scanf("%s",name);
            printf("�������\n");
            scanf("%d",&money);
            printf("�������ʧ��Ϣ��y/n����\n");
            scanf("%s",guashi);
            while(strcmp(guashi,"y")!=0&&strcmp(guashi,"n")!=0){
                printf("��ʧ��Ϣֻ�������루y/n�������������룡��\n");
                scanf("%s",guashi);
            }
    }
    return head;
}
struct foodcard *insertDoc(struct foodcard *head,struct foodcard *stud)  //�������
{
    struct foodcard *ptr,*ptr1,*ptr2;
    ptr2=head;
    ptr=stud;                       //ptrָ���������µķ�����¼�ڵ�
    //ԭ����Ϊ��ʱ�Ĳ���
    if(head==NULL){
        head=ptr;                   //�²���ڵ�Ϊͷ���
        head->next=NULL;
    }
    //ԭ����Ϊ��ʱ�Ĳ��루�����������ֻ��һ�������ж�����������
    else {
        while((ptr->num>ptr2->num)&&(ptr2->next!=NULL)){                        //��while����ǰ���Ǵ��ݽ�����numֵ�������нڵ��numֵ����Ҵ����������������Ͻ��
            ptr1=ptr2;               //ptr1ָ��ptr2
            ptr2=ptr2->next;         //ptr2ָ����һ�����,��ptr1��pyr2������һ��λ��
        }
        if(ptr->num<=ptr2->num){     //���ptrָ��Ľ����ptr2ָ�����ǰ��
            if(head==ptr2)head=ptr;  //ǰ�᣺ptrָ��Ľ����ptr2ָ�����ǰ�档
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
struct foodcard *deleteDoc(struct foodcard *head)                        //ע���ɷ���(��鷹���治���ڣ�
{
    struct foodcard *ptr1,*ptr2,*ptr3,*p1;
    int num1;
    if(head==NULL){
        printf("û�з����ļ���\n");
        return head;
    }
    printf("��������Ҫע���ķ����ţ�\n");
    scanf("%d",&num1);
    p1=head;
    while(p1!=NULL){
        if(p1->num==num1)break;
        p1=p1->next;
        while(p1==NULL){
            printf("�����Ų����ڣ�\n");
            return head;
        }
    }
    while(head!=NULL&&head->num==num1){               //�������˼������Ϊ�գ�����Ҫɾ����Ϊͷ��㣬ptr2=head��headָ��next��Ȼ���ͷ�ptr2
        ptr2=head;
        head=head->next;
        free(ptr2);
        printf("����ע���ɹ���\n");
    }
    if(head==NULL){                //���ֻ��һ������Ǿ���������
        return NULL;
    }
    ptr1=head;
    ptr2=head->next;
    while(ptr2!=NULL){               //�����ǰ�᣺���������������������Ͻ��
        if(ptr2->num==num1){         //���ΪҪɾ�Ľ��
            ptr1->next=ptr2->next;   //��һ������β��ַָ��ptr2��next��
            free(ptr2);              //�ͷ�ptr2ָ��Ľ��
            printf("����ע���ɹ���\n");
        }
        else ptr1=ptr2;              //��㲻��Ҫɾ���Ľ��  ����Ѱ��
        ptr2=ptr1->next;             //ptr2ָ��ptr1��next��
    }
    return head;
}
void Print_foodcard(struct foodcard *head)                               //�������ϱ���
{
    struct foodcard *ptr;
    if(head==NULL){
        printf("û�з������ݣ�\n");
       return;
    }
    printf("\n������          ����            ���            �Ƿ��ʧ\n");
    for(ptr=head;ptr!=NULL;ptr=ptr->next)
        printf("%d\t\t%s\t\t%d\t\t%s\n",ptr->num,ptr->name,ptr->money,ptr->guashi);
}
void save_Doc(struct foodcard *head)                                     //д�������ļ�
{
    struct foodcard *p;
    FILE *fp;
    p=head;
    if((fp=fopen("card.dat","wb"))==NULL){
        printf("���ļ�ʧ�ܣ�\n");
        exit(0);
    }
    while(p!=NULL){
        fprintf(fp,"%d %s %d %s ",p->num,p->name,p->money,p->guashi);
        p=p->next;
    }
    fprintf(fp,"\n");
    fclose(fp);
}
struct foodcard *read_Doc()                         //���ļ���������
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
        printf("û�з����ļ����뽨�������ļ���\n");
        return NULL;
    }
    else printf("���з����ļ���\n");
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
struct foodcard *increasenfc(struct foodcard *head)                      //����·���(��鷹�����Ѵ��ڣ�
{
    struct foodcard *p,*p1;
    int num;
    char name[20];
    int money;
    char guashi[5];
    int size=sizeof(struct foodcard);
    p1=head;
    if(p1==NULL){
        printf("û�з����ļ���\n");
        return head;
    }
    printf("������Ҫ��ӵ��·����Ŀ���:\n");
    scanf("%d",&num);
    while(p1!=NULL){
        if(p1->num==num){
            printf("�������Ѵ��ڣ�\n");
            return head;
        }
        p1=p1->next;
        if(p1==NULL)break;
    }
    while(num<=0){
         printf("�����Ų���Ϊ0���������������뷹���ţ�\n");
         scanf("%d",&num);
    }
    printf("������������\n");
    scanf("%s",name);
    printf("�������\n");
    scanf("%d",&money);
    printf("�������ʧ��Ϣ��y/n)��\n");
    scanf("%s",guashi);
    while(strcmp(guashi,"y")!=0&&strcmp(guashi,"n")!=0){
          printf("��ʧ��Ϣֻ�������루y/n�������������룡��\n");
          scanf("%s",guashi);
    }
    p=(struct foodcard *)malloc(size);
    p->num=num;
    strcpy(p->name,name);
    p->money=money;
    strcpy(p->guashi,guashi);
    head=insertDoc(head,p);
    printf("��ӳɹ���\n");
    return head;
}
struct foodcard *buy(struct foodcard *head)                              //��(��鷹���治���ڣ�
{
    int num,num1,money;
    struct foodcard *p;
    p=head;
    if(p==NULL){
        printf("û�з����ļ���\n");
        return head;
    }
    printf("��������Ҫ�򷹵ķ����ţ�");
    scanf("%d",&num1);
    while(p!=NULL){
        if(p->num==num1)break;
        p=p->next;
        while(p==NULL){
            printf("�����Ų����ڣ�\n");
            return head;
        }
    }
    if(p->num==num1){
        if(strcmp(p->guashi,"y")==0){
            printf("�����ѹ�ʧ�������򷹣�\n");
            return head;
        }
            printf(">>> ������%d <<<\n",p->money);
        if(p->money<5){
            printf("���㣬����Ǯ��\n");
            return head;
        }
        else{
            printf("�������򷹷��ѣ�");
            scanf("%d",&money);
            if(money>p->money){
                printf("���ѳ�����\n");
                return head;
            }
            p->money=p->money-money;
            printf(">>> �򷹺󷹿���%d <<<\n",p->money);
        }
    }
    return head;
}
struct foodcard *xuqian(struct foodcard *head)                           //��Ǯ(��鷹���治���ڣ�
{
    int num,num1,money;
    struct foodcard *p;
    p=head;
    if(p==NULL){
        printf("û�з����ļ���\n");
        return head;
    }
    printf("�����뷹�����ţ�");
    scanf("%d",&num1);
    while(p!=NULL){
        if(p->num==num1)break;
        p=p->next;
        while(p==NULL){
            printf("�����Ų����ڣ�\n");
            return head;
        }
    }
    if(p->num==num1){
        if(strcmp(p->guashi,"y")==0){
            printf("�����ѹ�ʧ��������Ǯ��\n");
            return head;
        }
        printf(">>> ������%d <<<\n",p->money);
        printf("��������Ǯ��\n");
        scanf("%d",&money);
        p->money=p->money+money;
        printf(">>> ��Ǯ�󷹿���%d <<<\n",p->money);
    }
    return head;
}
struct foodcard *set_or_relieve(struct foodcard *head)                   //���úͽ����ʧ(��鷹���治���ڣ�
{
    struct foodcard *p;
    int num1;
    char guashi[5];
    p=head;
    if(p==NULL){
        printf("û�з����ļ���\n");
        return head;
    }
    printf("��������Ҫ���û�����ʧ�ķ����ţ�\n");
    scanf("%d",&num1);
    while(p!=NULL){
        if(p->num==num1)
            break;
        p=p->next;
        while(p==NULL){
            printf("�����Ų����ڣ�\n");
            return head;
        }
    }
    if(p->num==num1){
        printf("������y�����ù�ʧ����n�������ʧ����\n");
        scanf("%s",guashi);
        while(strcmp(guashi,"y")!=0&&strcmp(guashi,"n")!=0){
            printf("��ʧ��Ϣֻ�������루y/n�������������룡��\n");
            scanf("%s",guashi);
        }
        if(strcmp(guashi,"y")==0){
            if(strcmp(p->guashi,"y")==0){
               printf("�˿��Ѿ����ڹ�ʧ״̬��\n");
                return head;
            }
            else
                strcpy(p->guashi,guashi);
        }
        else{
            if(strcmp(p->guashi,"n")==0){
                printf("�˿��Ѿ����ڲ���ʧ״̬��\n");
                return head;
            }
            else
                strcpy(p->guashi,guashi);
        }
        printf("���¹�ʧ��Ϣ�ɹ���\n");
    }
    return head;
}
