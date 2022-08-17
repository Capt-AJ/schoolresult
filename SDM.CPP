#include <graphics.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <conio.h>
#include <fstream.h>
#include <dos.h>

#define poscur(y) gotoxy(3,y)

class Student
{
private:
	int enroll, std;
	long int ph;
	char name[20], address[50], stream[20];
	int eng, mat, phy, che, csc, bio, tot;
	float avg;
public:
	int accept(int);
	void displaym(int);
	void displayd(int);
	void copy(Student);
	void changem(int p);
	void readstream(int p);
	int checkfail();
	Student()
	{
		csc = bio = 0;
	}
	int returnenroll()
	{
		return enroll;
	}
	char* returnname()
	{
		return name;
	}
	int returnstd()
	{
		return std;
	}
	float returnavg()
	{
		return avg;
	}
	void changeenroll(int e)
	{
		enroll = e;
	}
	void changestd() 
	{
		std+=1;
	}
};

int login();
void clear(int x, int y, int x1, int y1);
void display();
void displaydetail();
void displayml();
void displaytopper();
void displayfailure();
int admission();
void modify();
char* returnfilename(int std);
void yearupgrade();
void stdupgrade(char fname[]);
void sort(int std);
void studleft();
void changemarks();
void inputstream();

void main()
{

	/* request auto detection */
	int gdriver = DETECT, gmode, errorcode;
	int style, userpat;
	int ch;

	/* initialize graphics and local variables */
	initgraph(&gdriver, &gmode, "\\tc\\bin");

	userpat = 1;

	style = SOLID_LINE;
	initgraph(&gdriver, &gmode, "\\tc\\bin");

	/* select the line style */
	setlinestyle(style, userpat, 3);

	/* draw a rectangle */
	rectangle(10, 10, getmaxx() - 10, getmaxy() - 10);
	int poly[8] = { 200,130,getmaxx() - 200,130,getmaxx() - 200,getmaxy() - 130,200,getmaxy() - 130 };
	do
	{
		clear(3,3,75,22);
		setfillstyle(1, 1);
		fillpoly(4, poly);
		//rectangle(200, 130, getmaxx() - 200, getmaxy() - 130);
		gotoxy(38, 12);
		cout << " Menu ";
		gotoxy(38, 13);
		cout << " ---- ";
		gotoxy(34, 14);
		cout << " 1.Display   ";
		gotoxy(34, 15);
		cout << " 2.Admission ";
		gotoxy(34, 16);
		cout << " 3.Modify    ";
		gotoxy(34, 17);
		cout << " 4.Exit      ";
		gotoxy(32, 19);
		cout << " Enter choice:   ";
		gotoxy(47,19);
		cin >> ch;
		textbackground(0);
		switch (ch)
		{
		case 1:
			display();
			break;
		case 2:
			admission();
			break;
		case 3:
			modify();
			break;
		}
	}while (ch != 4);
	closegraph();
}

int admission()
{
   char ch, sch;
   int  s;
   char stylestr[40];
   Student stud, s1;
   fstream file;


   int x=login();
   if(x==-1)
   {
      closegraph();
      cout<<"Password incorrect";
      cout<<"\nPress any key to exit";
      system("pause");
      exit(0);
   }
   setlinestyle(0, 0, 3);
   rectangle(10, 10, getmaxx() - 10, getmaxy() - 10);
   rectangle(200, 130, getmaxx() - 200, getmaxy() - 130);

   do
   {
      clear(3,3,70,24);
      poscur(3);
      cout<<"Enter standard for admission: ";
      poscur(4);
      cin>>s;
	  char tempstd[20];
	  switch (s)
	  {
	  case 1:
		  strcpy(tempstd, "Stud1.dat");
		  break;
	  case 2:
		  strcpy(tempstd, "Stud2.dat");
		  break;
	  case 3:
		  strcpy(tempstd, "Stud3.dat");
		  break;
	  case 4:
		  strcpy(tempstd, "Stud4.dat");
		  break;
	  case 5:
		  strcpy(tempstd, "Stud5.dat");
		  break;
	  case 6:
		  strcpy(tempstd, "Stud6.dat");
		  break;
	  case 7:
		  strcpy(tempstd, "Stud7.dat");
		  break;
	  case 8:
		  strcpy(tempstd, "Stud8.dat");
		  break;
	  case 9:
		  strcpy(tempstd, "Stud9.dat");
		  break;
	  case 11:
		  strcpy(tempstd, "Stud11.dat");
		  break;
	  default:
		  return -1;
	  }
	  if (s == 1)
	  {
		  file.open(tempstd, ios::out | ios::binary);
		  while (1)
		  {
			  int x = stud.accept(s);
			  if (x == -1)
			  {
				  break;
			  }
			  poscur(16);
			  file.write((char*)&stud, sizeof(stud));
			  cout << "Any more records? ";
			  cin >> ch;
			  if (ch == 'n' || ch == 'N')
				  break;
		  }
		  file.close();
		  sort(1);
	  }
	  else
	  {
		  file.open(tempstd, ios::out | ios::binary | ios::in);
		  int x = s1.accept(s);
		  if (x == -1)
		  {
			  break;
		  }
		  fstream tempfile("temp.dat", ios::out | ios::binary);
		  int f = 0;
		  while (file.read((char*)&stud, sizeof(stud)))
		  {
			  if (stud.returnenroll() < s1.returnenroll())
				  tempfile.write((char*)&stud, sizeof(stud));
			  else if (stud.returnenroll() == s1.returnenroll())
			  {
				  f++;
				  tempfile.write((char*)&s1, sizeof(s1));
				  stud.changeenroll(stud.returnenroll() + 1);
				  tempfile.write((char*)&stud, sizeof(stud));
			  }
			  else
			  {
				  stud.changeenroll(stud.returnenroll() + 1);
				  tempfile.write((char*)&stud, sizeof(stud));
			  }
		  }
		  poscur(16);
		  if (f == 0 && s1.returnenroll() > 0)
		  {
			  tempfile.write((char*)&s1, sizeof(s1));
		  }
		  file.close();
		  tempfile.close();
		  remove(tempstd);
		  rename("temp.dat", tempstd);
		  cout << "Successfully inserted!";
	  }
      poscur(17);
      cout<<"Would you like to do admission for another class?";
      poscur(18);
      cin>>sch;
      file.close();
   }while(sch=='y'||sch=='Y');

   /* wait for a key */
   poscur(15);
   system("pause");

   return 0;
}

void display()
{
	int ch;
	clear(3, 3, 70, 23);
	rectangle(10, 10, getmaxx() - 10, getmaxy() - 10);
	rectangle(200, 130, getmaxx() - 200, getmaxy() - 130);
	gotoxy(39, 12);
	cout << "Menu";
	gotoxy(39, 13);
	cout << "----";
	gotoxy(35, 14);
	cout << "1.Details";
	gotoxy(35, 15);
	cout << "2.Mark list";
	gotoxy(35, 16);
	cout << "3.Toppers";
	gotoxy(35, 17);
	cout << "4.Failures";
	gotoxy(32, 19);
	cout << "Enter choice: ";
	cin >> ch;
	switch (ch)
	{
	case 1:
		displaydetail();
		break;
	case 2:
		displayml();
		break;
	case 3:
		displaytopper();
		break;
	case 4:
		displayfailure();
		break;
	}
}

void displayml()
{
	Student s;
	clear(3, 3, 70, 23);
	int st;
	fstream file;
	poscur(3);
	cout << "Enter class to be displayed: ";
	cin >> st;
	char tempstd[20];
	switch (st)
	{
	case 1:
		strcpy(tempstd, "Stud1.dat");
		break;
	case 2:
		strcpy(tempstd, "Stud2.dat");
		break;
	case 3:
		strcpy(tempstd, "Stud3.dat");
		break;
	case 4:
		strcpy(tempstd, "Stud4.dat");
		break;
	case 5:
		strcpy(tempstd, "Stud5.dat");
		break;
	case 6:
		strcpy(tempstd, "Stud6.dat");
		break;
	case 7:
		strcpy(tempstd, "Stud7.dat");
		break;
	case 8:
		strcpy(tempstd, "Stud8.dat");
		break;
	case 9:
		strcpy(tempstd, "Stud9.dat");
		break;
	case 10:
		strcpy(tempstd, "Stud10.dat");
		break;
	case 11:
		strcpy(tempstd, "Stud11.dat");
		break;
	case 12:
		strcpy(tempstd, "Stud12.dat");
		break;
	default:
		return;
	}
	file.open(tempstd, ios::in | ios::binary);
	poscur(3);
	cout << "Enroll\tEnglish\tMaths\tPhysics\tChemistry\tAverage";
	int l = 4;
	while (file.read((char*)&s, sizeof(s)))
	{
		if (s.returnenroll() <= 0)
		{
			break;
		}
		s.displaym(l++);
	}
	getch();
}

void displaydetail()
{
	fstream file;
	Student stud;
	char std[5], tempstd[20] = "Stud";
	clear(3, 2, 70, 23);
	poscur(2);
	cout << "Enter class to be displayed ";
	cin >> std;
	strcat(tempstd, std);
	strcat(tempstd, ".dat");
	file.open(tempstd, ios::in | ios::binary);
	clear(3, 2, 70, 20);
	int temploc = 5;
	poscur(3);
	cout << "Enroll\tName\tStandard\tStream\t\tPhone number";
	while (file.read((char*)&stud, sizeof(stud)))
	{
		if (stud.returnenroll() == 0)
			break;
		stud.displayd(temploc++);
	}
	poscur(temploc + 1);
	system("pause");
}

void displaytopper()
{
	fstream file;
	Student stud;
	char fname[20] = "Stud", tempstd[5];
	clear(3, 2, 70, 23);
	int i, pos, cursor = 5;
	float max;
	poscur(3);
	cout << "Enroll\tName\tStandard\tStream\t\tPhone number";
	for (i = 1; i <= 12; i++)
	{
		max = 0.0;
		strcpy(fname, NULL);
		strcpy(fname, "Stud");
		itoa(i, tempstd, 10);
		strcat(fname, tempstd);
		strcat(fname, ".dat");
		file.open(fname, ios::in | ios::binary);
		pos = 0;
		file.read((char*)&stud, sizeof(stud));
		if (stud.returnenroll() <= 0)
			break;
		max = stud.returnavg();
		pos = stud.returnenroll();
		while (file.read((char*)&stud, sizeof(stud)))
		{
			if (stud.returnavg() > max)
			{
				max = stud.returnavg();
				pos = stud.returnenroll();
			}
		}
		file.close();
		file.open(fname, ios::in | ios::binary);
		while (file.read((char*)&stud, sizeof(stud)))
		{
			if (stud.returnenroll() == pos)
			{
				stud.displayd(cursor++);
			}
		}
		file.close();
	}
	getch();
}

void displayfailure()
{
	fstream file;
	Student stud;
	char std[5], tempstd[20] = "Stud";
	clear(3, 2, 70, 23);
	poscur(2);
	cout << "Enter class to be displayed ";
	cin >> std;
	strcat(tempstd, std);
	strcat(tempstd, ".dat");
	file.open(tempstd, ios::in | ios::binary);
	clear(3, 2, 70, 20);
	int temploc = 5;
	poscur(3);
	cout << "Enroll\tName\tStandard\tStream\t\tPhone number";
	while (file.read((char*)&stud, sizeof(stud)))
	{
		if (stud.checkfail() == 1)
			stud.displayd(temploc++);
	}
	poscur(temploc + 1);
	system("pause");
}

void modify()
{
	int ch;
	int x = login();
	if (x == -1)
	{
		closegraph();
		cout << "Password incorrect";
		cout << "\nPress any key to exit";
		system("pause");
		exit(0);
	}
	setlinestyle(0, 0, 3);
	rectangle(10, 10, getmaxx() - 10, getmaxy() - 10);
	rectangle(200, 130, getmaxx() - 200, getmaxy() - 130);
	gotoxy(39, 12);
	cout << "Menu";
	gotoxy(39, 13);
	cout << "----";
	gotoxy(34, 14);
	cout << "1.End of Year";
	gotoxy(34, 15);
	cout << "2.Student left";
	gotoxy(34, 16);
	cout << "3.Change marks";
	gotoxy(33, 18);
	cout << "Enter choice: ";
	cin >> ch;
	switch (ch)
	{
	case 1:
		yearupgrade();
		break;
	case 2:
		studleft();
		break;
	case 3:
		changemarks();
		break;
	}

}

int Student::accept(int s)
{
   clear(3,5,60,20);
   strcpy(stream,"Nil");
   if(s==10||s>=12||s<=0)
      {
		poscur(5);
		cout<<"Admission not available for the selected class";
		return -1;
      }
   else if(s==11)
      {
		poscur(5);
		cout<<"Enter stream(science/bio-technology): ";
		gets(stream);
		if(strcmpi(stream,"science")!=0&&strcmpi(stream,"bio-technology")!=0)
		{
		   poscur(6);
		   cout<<"Invalid stream";
		   return -1;
		}
      }
   std=s;
   poscur(6);
   cout<<"Enter enrollment number: ";
   cin>>enroll;
   poscur(7);
   cout<<"Enter name: ";
   gets(name);
   poscur(8);
   cout<<"Enter address\n";
   poscur(9);
   gets(address);
   poscur(10);
   cout<<"Enter phone number: ";
   cin>>ph;
   poscur(11);
   cout << "Enter marks in English: ";
   cin >> eng;
   poscur(12);
   cout << "Enter marks in Maths: ";
   cin >> mat;
   poscur(13);
   cout << "Enter marks in Physics: ";
   cin >> phy;
   poscur(14);
   cout << "Enter marks in Chemistry: ";
   cin >> che;
   poscur(15);
   if (strcmpi(stream, "science") == 0)
   {
	   cout << "Enter marks in Computer Science: ";
	   cin >> csc;
   }
   else if (strcmpi(stream, "bio-technology") == 0)
   {
	   cout << "Enter marks in Bio-technology: ";
	   cin >> bio;
   }
   tot = eng + mat + phy + che + bio + csc;
   if (std == 11 || std == 12)
	   avg = tot / 5.0;
   else
	   avg = tot / 4.0;
   return 0;
}

void Student::displayd(int y)
{
   poscur(y);
   cout << enroll << "\t\t" << name << '\t' << std << "\t\t" << stream << "\t\t" << ph;
}

void Student::displaym(int y)
{
	poscur(y);
	cout << enroll << "\t\t" << eng << '\t' << mat << "\t" << phy << "\t" << che << "\t";
	/*if (strcmpi(stream, "science") == 0)
		cout << csc;
	else if (strcmpi(stream, "bio-technology") == 0)
		cout << bio;*/
	cout << "\t" << avg;
}

int Student::checkfail()
{
	if (eng <= 40 || mat <= 40 || phy <= 40 || che <= 40)
		return 1;
	if (std >= 11)
	{
		if (csc <= 40 && bio <= 40)
			return 1;
	}
	return 0;
}

void Student::copy(Student s)
{
	enroll = s.enroll;
	strcpy(name, s.name);
	std = s.std;
	ph = s.ph;
	strcpy(address, s.address);
	strcpy(stream, s.stream);
	eng = s.eng;
	mat = s.mat;
	che = s.che;
	phy = s.phy;
	bio = s.bio;
	csc = s.csc;
	tot = s.tot;
	avg = s.avg;
}

int login()
{

   /* request auto detection */
   int gdriver = DETECT, gmode, errorcode;

   int style;
   char stylestr[40];

   /* initialize graphics and local variables */
   initgraph(&gdriver, &gmode, "\\tc\\bin");


   int userpat = 1;
   static int check = 0;
   if (check == 1)
	   return 0;


   /* select the line style */
   setlinestyle(0, userpat, 3);

   /* draw a rectangle */
   rectangle(10, 10, getmaxx()-10, getmaxy()-10);
   rectangle(200, 150, getmaxx()-200, getmaxy()-150);
   char pass[20];
   gotoxy(28,12);
   cout<<"Enter password\n";
   gotoxy(28,14);
   gets(pass);
   if(strcmp(pass,"Admin123")==0)
   {
      gotoxy(28,16);
      cout<<"Password correct";
	  clear(0, 0, 80, 24);
      cout<<"Decrypting\n";
      delay(1000);
      for(int i=0;i<10;i++)
      {
      for(int j=0;j<80;j++)
      {
		cout<<(rand()%2);
		delay(1);
      }
	  }
	  cout<<"Successful\n";
	  system("pause");
	  check = 1;
	  clear(0, 0, 80, 24);
	  rectangle(10, 10, getmaxx() - 10, getmaxy() - 10);
	  return 0;
   }
   return -1;
}

void clear(int x, int y, int x1, int y1)
{
   int i,j;
   for(i=y ;i<=y1 ;i++)
   {
      gotoxy(x,i);
      for(j=x;j<=x1;j++)
      {
	 cout<<" ";
      }
      cout<<endl;
   }

}

void yearupgrade()
{
	remove("STUD12.dat");
	rename("STUD11.dat", "STUD12.dat");
	stdupgrade("Stud12.dat");
	remove("Stud11.dat");
	rename("Stud10.dat", "Stud11.dat");
	stdupgrade("Stud11.dat");
	inputstream();
	remove("Stud10.dat");
	rename("Stud9.dat", "Stud10.dat");
	stdupgrade("Stud10.dat");
	remove("Stud9.dat");
	rename("Stud8.dat", "Stud9.dat");
	stdupgrade("Stud9.dat");
	remove("Stud8.dat");
	rename("Stud7.dat", "Stud8.dat");
	stdupgrade("Stud8.dat");
	remove("Stud7.dat");
	rename("Stud6.dat", "Stud7.dat");
	stdupgrade("Stud7.dat");
	remove("Stud6.dat");
	rename("Stud5.dat", "Stud6.dat");
	stdupgrade("Stud6.dat");
	remove("Stud5.dat");
	rename("Stud4.dat", "Stud5.dat");
	stdupgrade("Stud5.dat");
	remove("Stud4.dat");
	rename("Stud3.dat", "Stud4.dat");
	stdupgrade("Stud4.dat");
	remove("Stud3.dat");
	rename("Stud2.dat", "Stud3.dat");
	stdupgrade("Stud3.dat");
	remove("Stud2.dat");
	rename("Stud1.dat", "Stud2.dat");
	stdupgrade("Stud2.dat");
	remove("Stud1.dat");
}

void stdupgrade(char fname[])
{
	fstream file(fname, ios::in | ios::out | ios::binary);
	fstream temp("temp.dat", ios::out | ios::binary);
	Student Stud;
	while (file.read((char*)&Stud, sizeof(Stud)))
	{
		if (Stud.returnenroll() == 0)
			break;
		Stud.changestd();
		temp.write((char*)&Stud, sizeof(Stud));
	}
	file.close();
	temp.close();
	remove(fname);
	rename("temp.dat", fname);
}

void sort(int std)
{
	char t[20], fname[20] = "Stud";
	itoa(std, t, 10);
	strcat(fname, t);
	strcat(fname, ".dat");
	fstream file;
	file.open(fname, ios::in | ios::binary);
	Student stud[30], temp;
	int i, j,  n = 0;
	while (!file.eof())
	{
		file.read((char*)&stud[n], sizeof(stud[n]));
		if (stud[n].returnenroll() <= 0|| stud[n].returnenroll() >=13000)
		{
			break;
		}
		n += 1;
	}
	getch();
	for (i = 0; i < n - 1; i++)
		for (j = 0; j < n - i - 1; j++)
			if (stud[j].returnenroll() > stud[j + 1].returnenroll())
			{
				temp.copy(stud[j]);
				stud[j].copy(stud[j + 1]);
				stud[j + 1].copy(temp);
			}
	file.close();
	fstream temp1;
	temp1.open("temp1.dat", ios::out | ios::binary);
	for (i = 0; i < n; i++)
	{
		temp1.write((char*)&stud[i], sizeof(stud[i]));
	}
	getch();
	temp1.close();
	remove(fname);
	rename("temp1.dat", fname);
}

void studleft()
{
	Student s;
	clear(3, 3, 70, 23);
	int st;
	fstream file;
	poscur(3);
	cout << "Enter standard: ";
	cin >> st;
	char tempstd[20];
	switch (st)
	{
	case 1:
		strcpy(tempstd, "Stud1.dat");
		break;
	case 2:
		strcpy(tempstd, "Stud2.dat");
		break;
	case 3:
		strcpy(tempstd, "Stud3.dat");
		break;
	case 4:
		strcpy(tempstd, "Stud4.dat");
		break;
	case 5:
		strcpy(tempstd, "Stud5.dat");
		break;
	case 6:
		strcpy(tempstd, "Stud6.dat");
		break;
	case 7:
		strcpy(tempstd, "Stud7.dat");
		break;
	case 8:
		strcpy(tempstd, "Stud8.dat");
		break;
	case 9:
		strcpy(tempstd, "Stud9.dat");
		break;
	case 10:
		strcpy(tempstd, "Stud10.dat");
		break;
	case 11:
		strcpy(tempstd, "Stud11.dat");
		break;
	case 12:
		strcpy(tempstd, "Stud12.dat");
		break;
	default:
		return;
	}
	file.open(tempstd, ios::in | ios::binary);
	fstream t;
	t.open("temp.dat", ios::out | ios::binary);
	poscur(4);
	cout << "Enter enroll:";
	int f = 0, e;
	cin >> e;
	while (file.read((char*)&s, sizeof(s)))
	{
		if (s.returnenroll() == e)
		{
			f = 1;
			continue;
		}
		else if (f == 1)
		{
			s.changeenroll(s.returnenroll() - 1);
		}
		t.write((char*)&s, sizeof(s));
	}
	file.close();
	t.close();
	remove(tempstd);
	rename("temp.dat", tempstd);
}

void Student::changem(int p)
{
	clear(3, 4, 70, 22);
	poscur(p++);
	cout << "Enter new marks for enroll. no: " << enroll;
	poscur(p++);
	cout << "Enter marks in english: ";
	cin >> eng;
	poscur(p++);
	cout << "Enter marks in Mathematics: ";
	cin>>mat;
	poscur(p++);
	cout << "Enter marks in physics: ";
	cin >> phy;
	poscur(p++);
	cout << "Enter marks in chemistry: ";
	cin >> che;
	tot = eng + mat + phy + che;
	avg = tot / 4;
	if (strcmpi(stream, "Science") == 0)
	{
		poscur(p++);
		cout << "Enter marks in computer science: ";
		cin>>csc;
		tot += csc;
		avg = tot / 5;
	}
	else if (strcmpi(stream, "bio-technology") == 0)
	{
		poscur(p++);
		cout << "Enter marks in biology: ";
		cin >> bio;
		tot += bio;
		avg = tot / 5;
	}
}

void changemarks()
{
	clear(3, 3, 74, 22);
	Student stud;
	fstream file, temp;
	int s;
	char tempstd[20];
	poscur(3);
	cout << "Enter standard";
	cin >> s;
	switch (s)
	{
	case 1:
		strcpy(tempstd, "Stud1.dat");
		break;
	case 2:
		strcpy(tempstd, "Stud2.dat");
		break;
	case 3:
		strcpy(tempstd, "Stud3.dat");
		break;
	case 4:
		strcpy(tempstd, "Stud4.dat");
		break;
	case 5:
		strcpy(tempstd, "Stud5.dat");
		break;
	case 6:
		strcpy(tempstd, "Stud6.dat");
		break;
	case 7:
		strcpy(tempstd, "Stud7.dat");
		break;
	case 8:
		strcpy(tempstd, "Stud8.dat");
		break;
	case 9:
		strcpy(tempstd, "Stud9.dat");
		break;
	case 10:
		strcpy(tempstd, "Stud10.dat");
		break;
	case 11:
		strcpy(tempstd, "Stud11.dat");
		break;
	case 12:
		strcpy(tempstd, "Stud12.dat");
		break;
	default:
		return;
	}
	file.open(tempstd, ios::in | ios::out | ios::binary);
	temp.open("temp.dat", ios::out | ios::binary);
	while (file.read((char*)&stud, sizeof(stud)))
	{
		if (stud.returnenroll() <= 0)
		{
			break;
		}
		stud.changem(5);
		temp.write((char*)&stud, sizeof(stud));
	}
	file.close();
	temp.close();
	remove(tempstd);
	rename("temp.dat", tempstd);
}

void Student::readstream(int p)
{
	top:
	clear(3, 4, 70, 22);
	getch();
	poscur(p++);
	cout << "Enter stream for enroll. no: " << enroll << " ";
	cin >> stream;
	if (strcmpi(stream, "Science") != 0 && strcmpi(stream, "bio-technolody") != 0)
	{
		poscur(p--);
		cout << "Invalid stream";
		poscur(p + 2);
		system("PAUSE");
		goto top;
	}
}

void inputstream()
{
	fstream file, temp;
	Student stud;
	file.open("Stud11.dat", ios::in | ios::binary);
	temp.open("temp.dat", ios::out | ios::binary);
	while (file.read((char*)&stud, sizeof(stud)))
	{
		if (stud.returnenroll() <= 0)
			break;
		stud.readstream(4);
		temp.write((char*)&stud, sizeof(stud));
	}
	file.close();
	temp.close();
	remove("Stud11.dat");
	rename("temp.dat", "Stud11.dat");
}