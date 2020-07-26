#include<iostream.h>
#include<conio.h>
#include<fstream.h>
#include<string.h>
#include<process.h>
#include<stdio.h>
#include<ctype.h>
#include<iomanip.h>
void intro();
void reportMenu();
void editStation();
int leapOrNot();
class date
{
public:
int dd,mm,yy;
int leapOrNot()
{	 int lp;
 (yy%100==0 && yy%400==0)?lp=1:(yy%4==0)?lp=1:lp=0;
 return lp;	}
int valid()
{	  int days[]={0,31,29,31,30,31,30,31,31,30,31,30,31};
  if((yy<1900||mm<1||mm>12||dd<1||dd>days[mm])||(leapOrNot()==0 && mm==2 && dd>28))
  return 0;
  else
  return 1;
}	}dt;
class station
{
	private:
		char stcode[10],name[20];
		float doc,addDoc,ndoc,naddDoc;
	public:
		void enter();
		void display();
		void displaylist();
		void modify();
		int foundcode(char[]);
		float amount(char[],float,char);
		void addstation();
		void liststation();
		void search();
		void modifystation();
		void delstation();
}s;

class user
{
	private:
		int lastcustcode();
		int custcode;
		char name[20],address[35],phone[10], stcode[10], cname[20], caddress[30], cphone[10],type;
		float weight, amount;
	public:
		void adduser();
		void showuser();
		void booking();
		void searchuser();
		void listuser();
		void dailylist();
		void monthlylist();

}c;

void station::enter()
{
cout<<"enter station name:\t";
gets(name);
cout<<"enter charges for document(upto 500g):\t";
cin>>doc;
cout<<"enter charges for document(above 500g):\t";
cin>>addDoc;
cout<<"enter charges for non document(upto 500g):\t";
cin>>ndoc;
cout<<"enter charges for non document(above 500g):\t";
cin>>naddDoc;
}
void station::display()
{
cout<<"station code:\t"<<stcode<<endl;
cout<<"station name:\t"<<name<<endl;
cout<<"charges for document(upto 500g):Rs\t"<<doc<<endl;
cout<<"charges for document(above 500g):Rs\t"<<addDoc<<endl;
cout<<"charges for document(upto 500g):Rs\t"<<ndoc<<endl;
cout<<"charges for document(above 500g):Rs\t"<<naddDoc<<endl;
}
void station::displaylist()
{
cout<<setw(2)<<stcode<<setw(20)<<name<<setw(10)<<doc<<setw(10)<<addDoc<<setw(10)<<ndoc<<setw(10)<<naddDoc<<endl;
}
void station::modify()
{
char nm[20];
float d,ad,nd,nad;
display();
cout<<"enter new station name or press . to retain:\t";
gets(nm);
cout<<"enter new charges for document(upto 500g) or press -1 to retain:\t";
cin>>d;
cout<<"enter charges for document(above 500g) or press -1 to retain:\t";
cin>>ad;
cout<<"enter charges for document(upto 500g) or press -1 to retain:\t";
cin>>nd;
cout<<"enter charges for document(above 500g) or press -1 to retain:\t";
cin>>nad;
if(strcmpi(nm,".")!=0)
strcpy(name,nm);
if(d!=-1)
doc=d;
if(ad!=-1)
addDoc=ad;
if(nd!=-1)
ndoc=nd;
if(nad!=-1)
naddDoc=nad;
}
int station::foundcode(char tcode[10])
{
int found=0;
fstream f;
f.open("station.dat",ios::in|ios::binary);
 while(f.read((char *)&s,sizeof(s)))
  {
	if(strcmpi(tcode,stcode)==0)
	{
		found=1;
		break;
	}
  }
f.close();
return found;
}
float station::amount(char tcode[10],float weight, char type)
{
float tweight,amount=0.0;
fstream f;
f.open("station.dat",ios::in|ios::binary);
while(f.read((char *)&s,sizeof(s)))
{
	if(strcmpi(tcode,stcode)==0)
	{
		tweight=weight;
		if(type=='D')
		{
			amount=doc;
			tweight-=500;
			while(tweight>0)
			{
				amount+=addDoc;
				tweight-=500;
			}
		}
		else
		{
			amount=ndoc;
			tweight-=500;
			while(tweight>0)
			{
				amount+=naddDoc;
				tweight-=500;
			}
		}
		break;
	}
}
f.close();
return amount;
}
void station::addstation()		//to add station in file
{
char tcode[10],ch;
clrscr();
cout<<"enter station code:\t";
gets(tcode);
if(s.foundcode(tcode)==1)
{
	cout<<"\n\n station code already exists";
	getch();
	return;
}
s.enter();
do
{
	cout<<"\n do you want to save?(y/n)";
	ch=getche();
	ch=toupper(ch);
}while(ch!='Y'&&ch!='N');
if(ch=='Y')
{
strcpy(stcode,strupr(tcode));
fstream f;
f.open("station.dat",ios::app|ios::binary);
f.write((char *)&s,sizeof(s));
f.close();
cout<<"\n\n *********************record saved*************************\n\n";
getch();
}
}
void station::delstation()		//to delete station from file
{
   char tcode[10],ch;
   clrscr();
   cout<<"enter station code:\t";
   gets(tcode);
   int found=0;
   fstream f,fl;
   f.open("station.dat",ios::in|ios::binary);
   char confirm='n';
   fl.open("temp.dat",ios::out|ios::binary);
   while(f.read((char *)&s,sizeof(s)))
   {
      if(strcmpi(tcode,stcode)==0)
      {
	s.display();
	found=1;
	cout<<"are you sure u want to delete this record? (y/n)\n";
	cin>>confirm;
	if(confirm=='n')
	  fl.write((char*)&s,sizeof(s));
	cout<<"\n\n\t\tRECORD DELETED\n\n";
      }
      else
	fl.write((char*)&s,sizeof(s));
   }
   if(found=='f')
   cout<<"\n\t\trecord not found\n\n";
   cout<<"press any key to continue\n";
   fl.close();
   f.close();
   remove("station.dat");
   rename("temp.dat","station.dat");
   getch();
   clrscr();
}
void station::modifystation()		//to modify record from file
{  char tcode[10],ch;
   clrscr();
   cout<<"enter station code:\t";
   gets(tcode);
   int found=0;
   fstream f;
   f.open("station.dat",ios::in|ios::out|ios::binary);
   while(!f.eof())
   {  int pos=f.tellg();
      f.read((char*)&s,sizeof(s));
      if(strcmpi(tcode,stcode)==0)
      {
	s.modify();
	f.seekg(pos);
	f.write((char*)&s,sizeof(s));
	found=1;
	cout<<"**************record modified*************";
	break;
      }

   }
   if(found==0)
   cout<<"\n\n\t\trecord not found\n";
   cout<<"\t\tpress enter to continue\n";
   f.close();
   getch();
   clrscr();
}
void station::search()			//to search a particular station
{
 char tcode[10];
 int found=0;
clrscr();
cout<<"search station record\n\n\n";
cout<<"enter station code:\t";
gets(tcode);
fstream f;
f.open("station.dat",ios::in|ios::binary);
while(f.read((char *)&s,sizeof(s)))
{
	if(strcmpi(tcode,stcode)==0)
	{
		found=1;
		s.display();
		break;
	}
}

f.close();
if(!found)
cout<<"\n\n station code does not exists!!!\n\n";
getch();
}
void station::liststation()		//to display list of available station
{
clrscr();
fstream f;
f.open("station.dat",ios::in|ios::binary);
int row=5, found=0;
gotoxy(28,1);
cout<<"station information";
gotoxy(28,2);
cout<<"~~~~~~~~~~~~~~~~~~~~~~";
gotoxy(1,3);
cout<<"code     name          charges: doc   addition    non-doc   additional";
gotoxy(1,4);
cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
while(f.read((char *)&s,sizeof(s)))
{
found=1;
gotoxy(1,row);
s.displaylist();
if(row==23)
{
row=5;
gotoxy(1,25);
cout<<"press any key to continue......";
getche();
clrscr();
gotoxy(28,1);
cout<<"station information";
gotoxy(28,2);
cout<<"~~~~~~~~~~~~~~~~~~~~~~";
gotoxy(1,3);
cout<<"code     name          charges: doc   addition    non-doc   additional";
gotoxy(1,4);
cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
}
else
row++;
}
if(!found)
{
gotoxy(5,10);
cout<<"records not found!!!";
}
gotoxy(1,25);
cout<<"press any key to continue.....";
getche();
f.close();
}

void user::showuser()
{
cout<<"\n CONSIGNOR INFORMATION \n";
cout<<"consignor name:\t"<<name<<endl;
cout<<"address of consignor:\t"<<address<<endl;
cout<<"enter phone no of consignor:\t"<<phone<<endl;
cout<<"\n CONSIGNEE INFORMATION \n";
cout<<"enter consignee name:\t"<<cname<<endl;
cout<<"enter address of consignee:\t"<<caddress<<endl;
cout<<"enter phone no of consignee:\t"<<cphone<<endl;
cout<<"date of booking"<<dt.dd<<dt.mm<<dt.yy<<endl;
if(type=='D')
cout<<"\n type of courier document\n";
else
cout<<"\n type of courier non document\n";
cout<<"\n weight (in gms)\t"<<weight<<endl;
cout<<"\n amount: Rs"<<amount;
}
void user::listuser()
{
cout<<setw(2)<<custcode<<setw(15)<<name<<setw(15)<<cname<<setw(4)<<stcode
<<setw(2)<<(type=='D')?cout<<"doc":cout<<"non-doc"<<setw(3)<<weight<<setw(5)<<amount<<endl;
}
void user::booking()
{
char tstcode[10],ch;
int tcustcode,datevalid;
clrscr();
cout<<"\t\tBooking Courier\t\n";
cout<<"enter station code(destination):\t";
gets(tstcode);
if(s.foundcode(tstcode)==0)
{
	cout<<"\n\n station code does not exists";
	getch();
	return;
}
tcustcode=lastcustcode()+1;
cout<<"\n INPUT CONSIGNOR INFORMATION \n";
cout<<"enter consignor name:\t";
gets(name);
cout<<"enter address of consignor:\t";
gets(address);
cout<<"enter phone no of consignor:\t";
gets(phone);
cout<<"\n INPUT CONSIGNEE INFORMATION \n";
cout<<"enter consignee name:\t";
gets(cname);
cout<<"enter address of consignee:\t";
gets(caddress);
cout<<"enter phone no of consignee:\t";
gets(cphone);
do
{
cout<<"\n enter type of courier (D=document, N= non document)\t";
type=getche();
type=toupper(type);
}while(type!='D' && type!='N');
cout<<"\n enter weight (in gms)\t";
cin>>weight;

while(1)
{
	cout<<"enter date of booking (dd mm yyyy):\t";
	cin>>dt.dd>>dt.mm>>dt.yy;
	datevalid=dt.valid();
	if(datevalid==1)
		break;
	else
		cout<<"invalid date!!!\n";
}
amount=s.amount(tstcode,weight,type);
do
{
	cout<<"\n do you want to save?(y/n)";
	ch=getche();
	ch=toupper(ch);
}while(ch!='Y'&&ch!='N');
if(ch=='Y')
{
strcpy(stcode,strupr(tstcode));
custcode=tcustcode;
fstream f;
f.open("customer.dat",ios::app|ios::binary);
f.write((char *)&c,sizeof(c));
f.close();
cout<<"\n\n *********************record saved*************************\n\n";
getch();
}
}
void user::searchuser()
{
int tcode;
 int found=0;
clrscr();
cout<<"search customer record\n\n\n";
cout<<"enter customer code:\t";
cin>>tcode;
fstream f;
f.open("customer.dat",ios::in|ios::binary);
while(f.read((char *)&c,sizeof(c)))
{
	if(tcode==custcode)
	{
		found=1;
		c.showuser();
		break;
	}
}

f.close();
if(!found)
cout<<"\n\n customer code does not exists!!!\n\n";
getch();
}

void user::dailylist()
{
clrscr();
date tdate;
int datevalid;
while(1)
{
	cout<<"enter date of booking (dd mm yyyy):\t";
	cin>>tdate.dd>>tdate.mm>>tdate.yy;
	datevalid=dt.valid();
	if(datevalid==1)
		break;
	else
		cout<<"invalid date!!!\n";
}
fstream f;
f.open("customer.dat",ios::in|ios::binary);
int row=10, found=0;
gotoxy(23,4);
cout<<"daily booking status("<<tdate.dd<<'/'<<tdate.mm<<'/'<<tdate.yy<<")";
gotoxy(23,5);
cout<<"~~~~~~~~~~~~~~~~~~~~~~";
gotoxy(1,6);
cout<<"code    consignor     consignee   station_code    type   weight   amount";
gotoxy(1,7);
cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
while(f.read((char *)&c,sizeof(c)))
{
if(tdate.dd==dt.dd && tdate.mm==dt.mm && tdate.yy==dt.yy)
{
found=1;
gotoxy(1,row);
c.listuser();
if(row==23)
{
row=5;
gotoxy(1,25);
cout<<"press any key to continue......";
getche();
clrscr();
gotoxy(23,1);
cout<<"daily booking status("<<tdate.dd<<'/'<<tdate.mm<<'/'<<tdate.yy<<")";
gotoxy(23,2);
cout<<"~~~~~~~~~~~~~~~~~~~~~~";
gotoxy(1,3);
cout<<"code    consignor     consignee   station code    type   weight   amount";
gotoxy(1,4);
cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
}
else
row++;
}
}
if(!found)
{
gotoxy(5,10);
cout<<"records not found!!!";
}
gotoxy(1,25);
cout<<"press any key to continue.....";
getche();
f.close();

}
void user::monthlylist()
{
clrscr();
date tdate;
int datevalid;
while(1)
{
	cout<<"enter date of booking (dd mm yyyy):\t";
	cin>>tdate.dd>>tdate.mm>>tdate.yy;
	datevalid=dt.valid();
	if(datevalid==1)
		break;
	else
		cout<<"invalid date!!!\n";
}
fstream f;
f.open("customer.dat",ios::in|ios::binary);
int row=10, found=0;
gotoxy(23,4);
cout<<"Monthly booking status("<<tdate.dd<<'/'<<tdate.mm<<'/'<<tdate.yy<<")";
gotoxy(23,5);
cout<<"~~~~~~~~~~~~~~~~~~~~~~";
gotoxy(1,6);
cout<<"code    consignor     consignee   station_code    type   weight   amount";
gotoxy(1,7);
cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
while(f.read((char *)&c,sizeof(c)))
{
if( tdate.mm==dt.mm && tdate.yy==dt.yy)
{
found=1;
gotoxy(1,row);
c.listuser();
if(row==23)
{
row=5;
gotoxy(1,25);
cout<<"press any key to continue......";
getche();
clrscr();
gotoxy(23,1);
cout<<"Monthly booking status("<<tdate.dd<<'/'<<tdate.mm<<'/'<<tdate.yy<<")";
gotoxy(23,2);
cout<<"~~~~~~~~~~~~~~~~~~~~~~";
gotoxy(1,3);
cout<<"code    consignor     consignee   station code    type   weight   amount";
gotoxy(1,4);
cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
}
else
row++;
}
}
if(!found)
{
gotoxy(5,10);
cout<<"records not found!!!";
}
gotoxy(1,25);
cout<<"press any key to continue.....";
getche();
f.close();
}
int user::lastcustcode()
{
	int tcode=0;
	fstream f;
	f.open("customer.dat",ios::in|ios::binary);
	while(f.read((char *)&c,sizeof(c)))
		tcode=custcode;
	f.close();
	return tcode;
}

void main()
{
clrscr();
textcolor(50);
textbackground(65);
gotoxy(20,5);
cout<<"star"<<endl;
gotoxy(2,10);
cout<<"courier services"<<endl;
gotoxy(40,14);
cout<<"name: shruti anand"<<endl;
gotoxy(40,15);
cout<<"roll no: 1"<<endl;
gotoxy(40,16);
cout<<"class: 12 B"<<endl;
gotoxy(40,17);
cout<<"school name: shivalik academy"<<endl;
getch();
clrscr();
intro();
getch();
}

void intro()
{
int op;
do
{
clrscr();
gotoxy(20,5);
cout<<"      COURIER SERVICES"<<endl;
gotoxy(20,6);
cout<<"vvvvvvvvvvvvvvvvvvvvvvvvvvvvv"<<endl;
gotoxy(20,7);
cout<<"|| 1.  STATION INFORMATION ||"<<endl;
gotoxy(20,8);
cout<<"|| 2.  BOOKING             ||"<<endl;
gotoxy(20,9);
cout<<"|| 3.  SEARCH STATION      ||"<<endl;
gotoxy(20,10);
cout<<"|| 4.  CUSTOMER RECORDS    ||"<<endl;
gotoxy(20,11);
cout<<"|| 5.  REPORTS             ||"<<endl;
gotoxy(20,12);
cout<<"|| 6.  EDIT STATION        ||"<<endl;
gotoxy(20,13);
cout<<"|| 0.  TO QUIT            ||"<<endl;
gotoxy(20,14);
cout<<"VVVvvvvvvvvvvvvvvvvvvvvvvvVVV"<<endl;
gotoxy(20,16);
cout<<"ENTER YOUR CHOICE"<<endl;
gotoxy(20,17);
cin>>op;
switch(op)
{
case 1:s.liststation();
break;
case 2:c.booking();
break;
case 3:s.search();
break;
case 4:c.searchuser();
break;
case 5:reportMenu();
break;
case 6:editStation();
break;
case 0:exit(0);
break;
default:
cout<<"enter wrong choice plz enter again!!"<<endl;
}
}while(op!=0);
}
void reportMenu()
{
int op;
do
{
clrscr();
gotoxy(20,5);
cout<<"          REPORTS"<<endl;
gotoxy(20,6);
cout<<"vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv"<<endl;
gotoxy(20,7);
cout<<"|| 1.  DAILY BOOKING REPORT   ||"<<endl;
gotoxy(20,8);
cout<<"|| 2.  MONTHLY BOOKING REPORT ||"<<endl;
gotoxy(20,9);
cout<<"|| 0.  TO GO BACK             ||"<<endl;
gotoxy(20,10);
cout<<"VVVvvvvvvvvvvvvvvvvvvvvvvvvvvVVV"<<endl;
gotoxy(20,11);
cout<<"ENTER YOUR CHOICE"<<endl;
gotoxy(20,13);
cin>>op;
switch(op)
{
case 1:c.dailylist();
break;
case 2:c.monthlylist();
break;
case 0:intro();
break;
default:
cout<<"enter wrong choice plz enter again!!"<<endl;
}
}while(op!=0);
}
void editStation()
{
int op;
do
{
clrscr();
gotoxy(20,5);
cout<<"      STATION EDITING"<<endl;
gotoxy(20,6);
cout<<"vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv"<<endl;
gotoxy(20,7);
cout<<"|| 1.  ADD NEW STATION         ||"<<endl;
gotoxy(20,8);
cout<<"|| 2.  DELETE EXISTING STATION ||"<<endl;
gotoxy(20,9);
cout<<"|| 3.  MODIFY STATION          ||"<<endl;
gotoxy(20,10);
cout<<"|| 0.  TO GO BACK              ||"<<endl;
gotoxy(20,11);
cout<<"VVVvvvvvvvvvvvvvvvvvvvvvvvvvvvVVV"<<endl;
gotoxy(20,12);
cout<<"ENTER YOUR CHOICE"<<endl;
gotoxy(20,14);
cin>>op;
switch(op)
{
case 1:s.addstation();
break;
case 2:s.delstation();
break;
case 3:s.modifystation();
break;
case 0:intro();
break;
default:
cout<<"enter wrong choice plz enter again!!"<<endl;
}
}while(op!=0);
}
