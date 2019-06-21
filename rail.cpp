#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream.h>
#include<iomanip.h>
#include<fstream.h>
void create_database();
void modify_database();
void append_database();
void read_database();
void create_user();
void search_user();
void delete_user();
void railway();
void user();

class admin
{
    int t_no;
    char t_name[20];
    char bp[20];
    char dest[20];
    int cl,cl_f;
    int cl1,cl1_f;
    int d,m,y;
  public:
    void get_data()
    {
	     cout<<"Enter the details as follows\n";
	     cout<<"Train no:";
	     cin>>t_no;
	     cout<<"Train name:";
         gets(t_name);
	     cout<<"Boarding point:";
	     gets(bp);
	     cout<<"Destination point:";
	     gets(dest);
	     cout<<"No of seats in first class & fare per ticket:";
	     cin>>cl>>cl_f;
	     cout<<"No of seats in second class & fare per ticket:";
         cin>>cl1>>cl1_f;
	     cout<<"Date of travel:";
         cin>>d>>m>>y;
     }
    void display_data()
    {
         cout<<endl<<endl<<endl;
	     cout<<"Train no: "<<t_no<<"\n";
	     cout<<"Train name: "<<t_name<<"\n";
	     cout<<"boarding point: "<<bp<<"\n";
	     cout<<"destination point: "<<dest<<"\n";
	     cout<<"No of seats in first class & fare per ticket :"<<cl<<"\t"<<cl_f<<"\n";
	     cout<<"No of seats in second class & fare per ticket :"<<cl1<<"\t"<<cl1_f<<"\n";
	     cout<<"Date of travel:"<<d<<"-"<<m<<"-"<<y<<"\t"<<endl;
    }
    int get_train()
    {
	     return t_no;
    }

};

 class reserve
 {
    int t_no;
    char t_name[100];
    int id;
    char password[5];
    char bp[100];
    char dest[100];
    char clas;
    int d,m,y;
    int nos;
    public:
	void get_details()
	{
	    cout<<"Enter the details as follows\n";
	    cout<<"Give your id no:";
	    cin>>id;
	    cout<<"Train no:";
	    cin>>t_no;
	    cout<<"Train name:";
	    gets(t_name);
	    cout<<"Boarding point:";
	    gets(bp);
	    cout<<"Destination point:";
	    gets(dest);
	    cout<<"Enter the class f-first class s-second class:";
	    cin>>clas;
            cout<<"enter no of seats:";
            cin>>nos;
            cout<<"Date of travel:";
            cin>>d>>m>>y;
        }
        void display_details()
        {
            cout<<endl<<endl<<endl;
            cout<<"Train no: "<<t_no<<"\n";
            cout<<"Train name: "<<t_name<<"\n";
            cout<<"boarding point: "<<bp<<"\n";
            cout<<"destination point: "<<dest<<"\n";
            cout<<"class: "<<clas<<"\n";
            cout<<"no of seats: "<<nos<<"\n";
            cout<<"Date of travel:"<<d<<"-"<<m<<"-"<<y<<"\t"<<endl;
        }
        int get_ticket()
        {
            return id;
        }

 };

 void railway()
 {
     char pass[5];
     char password[5]="train";
     int ch;
     char ans;
     cout<<"Enter password: ";
     gets(pass);
     if(strcmp(pass,"train")!=0)
     {
         cout<<"You are not permitted here";
         return;
     }
     else
     {
         do
         {
              cout<<"1)Enter database\n";
              cout<<"2)Modify details\n";
              cout<<"3)Add details\n";
              cout<<"4)display details\n";
              cout<<"5)exit\n";
              cin>>ch;
              cout<<endl<<endl;
              switch(ch)
              {

                  case 1:create_database();
                         break;
		          case 2:modify_database();
                         break;
		          case 3:append_database();
                         break;
		          case 4:read_database();
                         break;
		          case 5:exit(0);

	          }
              cout<<endl<<"Do you want to continue as admin ?\n";
              cin>>ans;
         }
	     while(ans=='y');
     }
 }
 void user()
 {
     int ch;
     char ans;
     do
     {
	 cout<<"1)Reserve tickets\n";
	 cout<<"2)Check reservation\n";
	 cout<<"3)Cancel reservation\n";
	 cout<<"4)exit(0)\n";
	 cin>>ch;
	 cout<<endl<<endl;
	 switch(ch)
	 {
	     case 1:create_user();
		    break;
	     case 2:search_user();
		    break;
	     case 3:delete_user();
		    break;
	     case 4:exit(0);

	 }
	 cout<<endl<<"Do you want to continue as user ?\n";
	 cin>>ans;
     }
     while(ans=='y');
 }

 void create_database()
 {
     fstream f;
     admin ob;
     f.open("database.dat",ios::out|ios::binary);
     if(!f)
     {
	 cout<<"error opening file";
	 return;
     }
     char ch='y';
     while(ch=='y')
     {
	 ob.get_data();
	 f.write((char*)&ob,sizeof(ob));
	 cout<<endl<<"Want to enter more data ?\n";
	 cin>>ch;
     }
     f.close();
 }

 void read_database()
 {
     fstream f;
     admin ob;
     f.open("database.dat",ios::in|ios::binary);
     if(!f)
     {
         cout<<"error opening file";
         return;
     }
     while(f.read((char*)&ob,sizeof(ob)))
     {
         ob.display_data();
     }
     f.close();
 }

 void append_database()
 {
     int flag=0;
     fstream f,f1;
     admin ob,ob1;
     ob1.get_data();
     f.open("database.dat",ios::in|ios::binary);
     f1.open("temp.dat",ios::out|ios::binary);
     if(!f)
     {
	 cout<<"error opening file";
	 return;
     }
     while(f.read((char*)&ob,sizeof(ob)))
     {
	 if(ob.get_train()>ob1.get_train()&&flag==0)

	 {
	     f1.write((char*)&ob1,sizeof(ob1));
	     flag=1;
	 }
	 f1.write((char*)&ob,sizeof(ob));
     }
     if(flag==0)
     {
	 f1.write((char*)&ob,sizeof(ob));
     }
     f1.close();
     f.close();
     remove("database.dat");
     rename("temp.dat","database.dat");
 }

 void modify_database()
 {

     fstream f,f1;
     admin ob;
     int flag=0;
     int tno;
     cout<<"Enter the train no to be modified\n";
     cin>>tno;
     f.open("database.dat",ios::in|ios::binary);
     f1.open("temp.dat",ios::out|ios::binary);
     if(!f||!f1)
     {
         cout<<"error opening file";
         return;
     }
     while(f.read((char*)&ob,sizeof(ob)))
     {
         if(tno==ob.get_train())
         {
             ob.get_data();
             flag=1;
         }
	 f1.write((char*)&ob,sizeof(ob));
     }
     f.close();
     f1.close();
     remove("database.dat");
     rename("temp.dat","database.dat");
     if(flag)
     {
         cout<<"Train modified\n";
     }
     else
     {
         cout<<"No train was found\n";
     }
 }

 void create_user()
 {
     fstream f,f1;
     admin ob;
     reserve ob1;
     f.open("database.dat",ios::in|ios::binary);
     f1.open("user.dat",ios::app|ios::binary);
     if(!f||!f1)
     {
         cout<<"error opening file";
	 return;
     }
     cout<<"The available trains and their details are as follows:\n";
     while(f.read((char*)&ob,sizeof(ob)))
     {
        ob.display_data();
     }
     char ch='y';
     while(ch=='y')
     {
         cout<<endl<<endl;
         ob1.get_details();
         f1.write((char*)&ob1,sizeof(ob1));
	 cout<<"Want to reserve more tickets of a different train ?\n";
	 cin>>ch;
     }
     f.close();
     f1.close();
     cout<<"Your ticket is reserved\n";
 }

 void search_user()
 {
   fstream f;
   reserve ob;
   int id;
   int flag=0;
   f.open("user.dat",ios::in|ios::binary);
   if(!f)
   {
       cout<<"error opening file";
       return;
   }
   cout<<"Enter your user id\n";
   cin>>id;
   while(f.read((char*)&ob,sizeof(ob)))
    {
        if(id==ob.get_ticket())
         {
	     ob.display_details();
	     flag=1;
         }
    }
    f.close();
    if(flag==0)
    {
	cout<<"Id not matched\n";
    }
 }

 void delete_user()
 {
     int id;
     int flag=0;
     cout<<"Enter your user id";
     cin>>id;
     fstream f,f1;
     reserve ob;
     f.open("user.dat",ios::in|ios::binary);
     f1.open("temp.dat",ios::out|ios::binary);
     if(!f||!f1)
     {
         cout<<"error opening file";
         return;
     }
     while(f.read((char*)&ob,sizeof(ob)))
     {
         if(ob.get_ticket()!=id)
         {
	     f1.write((char*)&ob,sizeof(ob));

         }
         else
         {
            flag=1;
         }
     }
     f.close();
     f1.close();
     remove("user.dat");
     rename("temp.dat","user.dat");
     if(flag)
     {
         cout<<"Your ticket is cancelled\n";
     }
     else
     {
         cout<<"Id not matched\n";
     }

 }
 void main()
 {
     clrscr();
     cout<<"**************************************************************\n";
     cout<<"*              MADE BY-                                      *\n";
     cout<<"*                       SUKANYA KAPOOR AND PRAKHAR BINDAL    *\n";
     cout<<"*                                                            *\n";
     cout<<"*                        XII-A                               *\n";
     cout<<"*                                                            *\n";
     cout<<"*               RAILWAY RESERVATION SYSTEM                   *\n";
     cout<<"**************************************************************\n";
     int ch;
     char ans;
     do
     {
         cout<<" 1)Administrator\n";
         cout<<" 2)User\n";
         cout<<" 3)exit\n";
         cin>>ch;
         cout<<endl<<endl;
         switch(ch)
         {

             case 1:railway();
                     break;
             case 2:user();
                     break;
             case 3:exit(0);

         }
        cout<<"\n"<<"want to continue ?\n";
        cin>>ans;
     }
     while(ans=='y');
     getch();
 }
