#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<conio.h>
/*#include<time.h>*/
using namespace std;
class medicine
{
public:
    string id;
    char name[50],exd[5];
    int price;
public:
    void accept()
    {
        fflush(stdin);
        cout<<"Enter medicine name : ";
        gets(name);
        cout<<"Enter medicine id : ";
        cin>>id;
        cout<<"Enter medicine price : ";
        cin>>price;
        cout<<"Enter exp date mm/yy : ";
        cin>>exd;
    }
    void display()
    {
        cout<<"Medicine ID     : "<<id<<endl;
        cout<<"Medicine Name   : "<<name<<endl;
        cout<<"Medicine Price  : "<<price<<endl;
        cout<<"Expiry date  : " << exd << endl;
    }
};
medicine med;
void addmedicine()
{
    fstream wr;
    wr.open("C:\\Users\\HP\\OneDrive\\Desktop\\C++ Project\\medicine.txt",ios::app);
    if(!wr)
    {
        cout<<"Error opening file "<<endl;
    }
    else
    {
        med.accept();
        wr.write((char*)&med,sizeof(med));
        wr.close();
        cout<<"medicine Added "<<endl;
    }
}
void showallmedicines()
{
    fstream rd;
    rd.open("C:\\Users\\HP\\OneDrive\\Desktop\\C++ Project\\medicine.txt",ios::in);
    if(!rd)
    {
        cout<<"Error opening file"<<endl;
    }
    else
    {
        int n;
        rd.seekg(0,ios::end);
        n = rd.tellg()/sizeof(med);
        rd.seekg(0,ios::beg);
        for(int i=1; i<=n; i++)
        {
            rd.read((char*)&med,sizeof(med));
            med.display();
            cout<<"--------------------------"<<endl;
        }
        rd.close();
    }
}
void searchmedicine()
{
    fstream rd;
    rd.open("C:\\Users\\HP\\OneDrive\\Desktop\\C++ Project\\medicine.txt",ios::in);
    if(!rd)
    {
        cout<<"Error opening file"<<endl;
    }
    else
    {
        string id; //id to search
        cout<<"Enter medicine id to search : ";
        cin>>id;
        int flag=0;

        int n;
        rd.seekg(0,ios::end);
        n = rd.tellg()/sizeof(med);
        rd.seekg(0,ios::beg);
        for(int i=1; i<=n; i++)
        {
            rd.read((char*)&med,sizeof(med));
            if(med.id == id)
            {
                cout<<"medicine Information "<<endl;
                med.display();
                cout<<"--------------------------"<<endl;
                flag = 1;
                break;
            }
        }
        if(flag==0)
        {
            cout<<"medicine not found "<<endl;
        }
        rd.close();
    }
}
int login(){
   string pass ="";
   char ch;
   cout<<"\t\t\t\t\t\t\t\t\t CUSTOMER INFORMATION \n\n";
   cout<<"\t\t\t\t\t\t\t\t-----------------------------------";
   cout<<"\n\t\t\t\t\t\t\t\t\t     LOGIN \n";
   cout<<"\t\t\t\t\t\t\t\t-----------------------------------\n\n";
   cout << "\t\t\t\t\t\t\t\tEnter Password: ";
   ch = _getch();
   while(ch != 13){//character 13 is enter
      pass.push_back(ch);
      cout << '*';
      ch = _getch();
   }
   if(pass == "group8" || pass=="Group8"){
      cout << "\n\n\t\t\t\t\t\t\t\tAccess Granted! \n";

   }else{
      cout << "\n\n\t\t\t\t\t\t\t\tAccess Aborted...\n\t\t\t\t\t\t\t\tPlease Try Again\n\n";

      login();

   }
   return 0;
}

class head
{
	char Iname[50][50];

public:
	int totalitems;
	float Qty[3];
	float price[3];
	int vatprice[3];
	int tprice[3];
	void input();
	void output();
};
class vat:public head
{
	float vats;
public:
	void vatcal();
	void outputs();
	void sum();
};

//******************************************************************
//	    INPUT FUNCTION
//******************************************************************

void head::input()
{
	system("CLS");
	cout<<"\nEnter number of items= ";
	cin>>totalitems;

	for(int i=0; i<totalitems; i++)
	{
		cout<<"\nEnter name of item "<<i+1<<": ";
		cin>>Iname[i];
		cout<<"Enter quantity: ";
		cin>>Qty[i];
		cout<<"Enter price of item "<<i+1<<": ";
		cin>>price[i];
		tprice[i]=Qty[i]*price[i];
	}
}

//******************************************************************
//	   OUTPUT FUNCTION
//******************************************************************



void head::output()
{
	int a;

	ifstream infile("COUNT.TXT");
	infile>>a;

	ofstream outfile("COUNT.TXT");
	a+=1;
	outfile<<a;
	outfile.close();

	{ofstream outfile("HIS.TXT", ios::app);
	outfile<<endl<<"Bill No.: "<<a<<endl;
	outfile<<"------------------------------------------------------------------------"<<endl;
cout<<"\n";
	cout<<"Name of Item\tQuantity   Price  Total Price\n";
	for(int i=0;i<totalitems;i++)
	{
		outfile<<"Name: "<<Iname[i]<<" Qty: "<<Qty[i]<<" Price: "<<tprice[i]<<endl;
		cout<<Iname[i]<<"\t\t"<<Qty[i]<<"\t   "<<price[i]<<"\t   "<<tprice[i]<<'\n';
	}

	outfile<<"------------------------------------------------------------------------"<<endl;
	outfile.close();
	}
}


//******************************************************************
//	   VAT CALCULATION
//******************************************************************

void vat::vatcal()
{
	input();
	for(int i=0;i<totalitems;i++)
	{
		if(price[i]<=100.00)
		{
			vatprice[i]=tprice[i]+(0.03*tprice[i]);
		}
		else
		{
			vatprice[i]=tprice[i]+(0.1*tprice[i]);
		}
	}
}
//******************************************************************
//	    VAT OUTPUTS
//******************************************************************

void vat::outputs()
{
	output();

	float cash=0,sum=0,qty=0,sumt=0;

	for(int i=0;i<totalitems;i++)
	{
	       sumt+=tprice[i];
		   sum+=vatprice[i];
		   qty+=Qty[i];
	}
	cout<<"\nTotal:";
	cout<<"\n------------------------------------------------------------------------------";
	cout<<"\n\tQuantity= "<<qty<<"\t\t Sum= "<<sumt<<"\tWith Vat:"<<sum;
	cout<<"\n------------------------------------------------------------------------------";

pay:

	cout<<"\n\n\t\t\t**PAYMENT SUMMARY**\n";
	cout<<"\n\t\t\tTotal cash given: ";
	cin>>cash;

	if(cash>=sum)
		cout<<"\n\t\t\tTotal cash repaid: "<<cash-sum<<'\n';

	else
	{	cout<<"\n\t\t\tCash given is less than total amount!!!";

	goto pay;
	}
}


//******************************************************************
//	    PROTECTION PASSWORD
//******************************************************************

int passwords()
{

    string s,t;
    s = "Group8";
	cout<<"\n\n\n\n\n\n\t\t\tENTER THE PASSWORD: ";
    cin >> t;
	if(s == t)
		return 1;
	else
		return 0;
}
// END of Password.
class supplier
{
public:
    int id;
    char name[50],date[5];
    char medicine_name[50];
    int quantity_supplied;
    int price;
public:
    void accept()
    {
        fflush(stdin);
        cout<<"Enter supplier name : ";
        gets(name);
        cout<<"Enter supplier id : ";
        cin>>id;
        cout<<"Enter the medicine supplied : ";
        cin >> medicine_name;
        cout<<"Enter the quantity supplied : ";
        cin>>quantity_supplied;
        cout<<"Enter supplier price : ";
        cin>>price;
        cout<<"Enter date mm/yy : ";
        cin>>date;
    }
    void display()
    {
        cout<<"Supplier ID     : "<<id<<endl;
        cout<<"Supplier Name   : "<<name<<endl;
        cout<<"Medicine supplied : "<<medicine_name<<endl;
        cout<<"Quantity : "<<quantity_supplied<<endl;
        cout<<"Supplier Price  : "<<price<<endl;
        cout<<"date  : " << date << endl;
    }
};
supplier sup;
void addsupplier()
{
    fstream wr;
    wr.open("Suppliermodule.txt",ios::app);
    if(!wr)
    {
        cout<<"Error opening file "<<endl;
    }
    else
    {
        sup.accept();
        wr.write((char*)&sup,sizeof(sup));
        wr.close();
        cout<<"Supplier Added "<<endl;
    }
}
void viewsupplier()
{
    fstream rd;
    rd.open("Suppliermodule.txt",ios::in);
    if(!rd)
    {
        cout<<"Error opening file"<<endl;
    }
    else
    {
        int n;
        rd.seekg(0,ios::end);
        n = rd.tellg()/sizeof(sup);
        rd.seekg(0,ios::beg);
        for(int i=1; i<=n; i++)
        {
            rd.read((char*)&sup,sizeof(sup));
            sup.display();
            cout<<"--------------------------"<<endl;
        }
        rd.close();
    }
}
void searchsupplier()
{
    fstream rd;
    rd.open("Suppliermodule.txt",ios::in);
    if(!rd)
    {
        cout<<"Error opening file"<<endl;
    }
    else
    {
        int id; //id to search
        cout<<"Enter supplier id to search : ";
        cin>>id;
        int flag=0;

        int n;
        rd.seekg(0,ios::end);
        n = rd.tellg()/sizeof(sup);
        rd.seekg(0,ios::beg);
        for(int i=1; i<=n; i++)
        {
            rd.read((char*)&sup,sizeof(sup));
            if(sup.id == id)
            {
                cout<<"Supplier Information "<<endl;
                sup.display();
                cout<<"--------------------------"<<endl;
                flag = 1;
                break;
            }
        }
        if(flag==0)
        {
            cout<<"Supplier not found "<<endl;
        }
        rd.close();
    }
}



int main()
{

while(true)
{
cout<<"***************************************************************************************************";
cout<<"\n\n\t\t\t\t\t\t\t\t  S.R.M MEDICAL STORE MANAGEMENT SYSTEM \n\n";
cout<<"\n\n\t\t\t\t\t\tPlease,  Choose from the following Options: \n\n";
cout<<"\t\t\t\t\t\t _________________________________________________________________ \n";
cout<<"\t\t\t\t\t\t|                                           	                  |\n";
cout<<"\t\t\t\t\t\t|             1  >> Medicine Stock Record                         |\n";
cout<<"\t\t\t\t\t\t|             2  >> Customer Management                           |\n";
cout<<"\t\t\t\t\t\t|             3  >> Bill                                          |\n";
cout<<"\t\t\t\t\t\t|             4  >> Supplier                                      |\n";
cout<<"\t\t\t\t\t\t|             5  >> Exit                                          |\n";
cout<<"\t\t\t\t\t\t|_________________________________________________________________|\n\n";
int choice;
cout<<"\t\t\t\t\t\tEnter your choice: ";
cin>>choice;
cout<<"***************************************************************************************************\n\n";

if(choice == 1)
{
    int key;
    while(1)
    {
        cout<<"1.Add medicine\n";
        cout<<"2.View All medicines\n";
        cout<<"3.Search medicine\n";
        cout<<"4.Exit\n";
        cout<<"Enter your key : ";
        cin>>key;
        switch(key)
        {
        case 1:
            addmedicine();
            break;
        case 2:
            showallmedicines();
            break;
        case 3:
            searchmedicine();
            break;
        case 4:
            exit(0);
        default:
            cout<<"Invalid key "<<endl;
        }
    }
}
if (choice==2)
{
    char fname[20];

int i;
int login();
login();//passcode for entering into program
b:

cout<<"\n\n\t\t\t\t\t\tPlease,  Choose from the following Options: \n\n";
cout<<"\t\t\t\t\t\t _________________________________________________________________ \n";
cout<<"\t\t\t\t\t\t|                                           	                  |\n";
cout<<"\t\t\t\t\t\t|             1  >> Add New Student Record                        |\n";
cout<<"\t\t\t\t\t\t|             2  >> Exisiting Student                             |\n";
cout<<"\t\t\t\t\t\t|             3  >> Full History of the Student                   |\n";
cout<<"\t\t\t\t\t\t|             4  >> Exit the Program                              |\n";
cout<<"\t\t\t\t\t\t|                                                                 |\n";
cout<<"\t\t\t\t\t\t|_________________________________________________________________|\n\n";
a:cout<<"\t\t\t\t\t\tEnter your choice: ";
cin>>i;
if(i>4||i<1)
{
cout<<"\n\n\t\t\t\t\t\tInvalid Choice\n";
cout<<"\t\t\t\t\t\tTry again...........\n\n";
goto a;} //if inputed choice is other than given choice
//system("cls");
// If user Gives the option as 1--------------------
if(i==1)
{

  ofstream pat_file;//to input data into file ---ifstream:-to read the file
  char fname[20];
  cout<<"\n\n\n\nEnter the Student's Admission Number : ";
  cin.ignore();
  gets(fname);
  pat_file.open(fname);
  		if(!fname)
		{
		cout<<"\nError while opening the file\n";
       goto b;
		}
		else
		{
                        struct patient_info
                        {
                            char name[20];
                            char sec_year[10];
                            char contact[10];
                            char age[5];
                            char sex[8];
                            char id[15];
                            char doc[5];
                            char cause[30];
                            char medicine[50];

                        };

            patient_info ak;//ak= structure variable
            cout<<"\n*******************************************************************\n";pat_file<<"\n*******************************************************************\n\n";
            cout<<"\n Student Name : ";pat_file<<"Name : ";gets(ak.name);pat_file<<ak.name<<"\n"; // to insert data into file
            cout<<"\nSec And Year : ";pat_file<<"Sec_year : ";gets(ak.sec_year);pat_file<<ak.sec_year<<"\n";
            cout<<"\nContact Number : ";pat_file<<"Contact Number : ";gets(ak.contact);pat_file<<ak.contact<<"\n";
            cout<<"\nAge : ";pat_file<<"Age : ";gets(ak.age);pat_file<<ak.age<<"\n";
            cout<<"\nSex : ";pat_file<<"Sex : ";gets(ak.sex);pat_file<<ak.sex<<"\n";
            cout<<"\nPatient ID : ";pat_file<<"Patient ID : ";gets(ak.id);pat_file<<ak.id<<"\n";
            cout<<"\nAppointed Docter :Y/N : ";pat_file<<"Appointed Doc? : ";gets(ak.doc);pat_file<<ak.doc<<"\n";
            cout<<"\nSuffering From :";pat_file<<"Suffering From : ";gets(ak.cause);pat_file<<ak.cause<<"\n";
            cout<<"\nTaken Medicine: ";pat_file<<"Medicine : ";gets(ak.medicine);pat_file<<ak.medicine<<"\n";
            cout<<"\n*******************************************************************\n";pat_file<<"\n*******************************************************************\n\n";
            cout<<"\nInformation Saved Successfully\n";
            }
  //system("pause");
  //system("cls");
  goto b;

}
// if option is 2-------------------
if(i==2)
{
    fstream pat_file;//headerfile to read and write data
    cout<<"\n\nEnter the Student's Admission Number  to be opened : ";
    cin.ignore();
    gets(fname);
    //system("cls");
	pat_file.open(fname, ios::in);//to enter the name into the file ios-input output stream
		if(!pat_file)
		{
		cout<<"\nError while opening the file\n";goto b;
		}
		else
		{
		    cout<<"\n\n\n\n\t\t\t\t........................................ Information about  the Student "<<fname<<" ........................................\n\n\n\n";
		    string info;
			while(pat_file.good())
			{
			getline(pat_file,info);
			cout<<info<<"\n";
			}
			cout<<"\n";
			pat_file.close();
			pat_file.open(fname, ios::out | ios::app);//to read or write data append
            cout<<"\n";
			cout<<"Adding more information in Student's file ";
			          struct patient_info
                        {

                            char doc[5];
                            char cause[30];
                            char medicine[50];
                        };


            patient_info add;
            cout<<"\nAppointed Docter :Y/N ";pat_file<<" Appointed Doc ? : ";gets(add.doc);pat_file<<add.doc<<"\n";
            cout<<"\nSuffering From: ";pat_file<<"Suffering From : ";gets(add.cause);pat_file<<add.doc<<"\n";
            cout<<"\nTaken Medicine: ";pat_file<<"Medicine : ";gets(add.medicine);pat_file<<add.medicine<<"\n";
            cout<<"\n\n"<<" Updated the Record Successfully\n";
            cout<<"\n*************************************************************************\n";
			pat_file.close();
			cout<<"\n\n";
			system("pause");
            system("cls");
			goto b;
		}

}
//For displaying the full medical history of patient in that hospital............option 3
if(i==3)
{
    fstream pat_file;
    cout<<"\n\nEnter the Student's Admission number to be opened : ";
    cin.ignore();
    gets(fname);
    system("cls");
	pat_file.open(fname, ios::in);
		if(!pat_file)
		{
		cout<<"\nError while opening the file\n";goto b;
		}
		else
		{
		    cout<<"\n\n\n\n\t\t\t\t........................................ Full Medical History of "<<fname<<" ........................................\n\n\n\n";
		    string info;
			while(pat_file.good())
			{
			getline(pat_file,info);
			cout<<info<<"\n";
			}
			cout<<"\n";
        }
        system("pause");
        system("cls");
        goto b;
}
//Exiting Through the system with a Thank You note........................option 4
if(i==4)
{
exit(0);
}
}
if (choice==3)
{

vat obj;
	char opt, ch;
	ifstream fin;

	int a = passwords();
	if(!a)
	{
		for(int i=0;i<2;i++)
		{
			cout<<"\nWrong password try once more\n";
			if(passwords())
			{
				goto last;
			}
			else
			{
				cout<<"\n\n\t\t\t all attempts failed.....";
				exit(0);
			}

		}
		cout<<"\t\t\t sorry all attempts failed............. \n \t\t\tinactive";
			 }
	else{
last:;


	 do{
start:
	system("PAUSE");
	system("CLS");
	cout<<"\n\n\t\t\t------------------------------";
	cout<<"\n\t\t\tShop Billing Management System";
	cout<<"\n\t\t\t------------------------------";
	 cout<<"\n\n\t\t\tWhat you want to do?";
	 cout<<"\n\t\t\t1.\tTo enter new entry\n\t\t\t2.\tTo view previous entries\n\t\t\t3.\tExit\n";
	 cout<<"\n\nEnter your option: ";
	 cin>>opt;
	 switch(opt)
	 {
	 case'1':
		 obj.vatcal();

		 obj.outputs();
		 goto start;
	 case'2':

		 fin.open("HIS.TXT", ios::in);
		 while(fin.get(ch))
		 {
			 cout<<ch;
		 }
		 fin.close();

		 goto start;
	 case'3':
		 exit(0);
	 default:
		 cout<<"\a";
	 }

	 }while(opt!=3);
	}
	return 0;
}
if (choice==4)
{
    int choice;
    while(1)
    {
        cout<<"1.Add Supplier\n";
        cout<<"2.View All Suppliers\n";
        cout<<"3.Search Suppliers\n";
        cout<<"4.Exit\n";
        cout<<"Enter your choice : ";
        cin>>choice;
        switch(choice)
        {
        case 1:
            addsupplier();
            break;
        case 2:
            viewsupplier();
            break;
        case 3:
            searchsupplier();
            break;
        case 4:
            exit(0);
        default:
            cout<<"Invalid choice "<<endl;
        }


}
}

if(choice==5)
{
    {
system("cls");
cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n";
cout<<"\t\t\t\t\t@@ _______________________________________________________________________________________ @@\n";
cout<<"\t\t\t\t\t@@|                                           		                                  |@@\n";
cout<<"\t\t\t\t\t@@|                                           		                                  |@@\n";
cout<<"\t\t\t\t\t@@|                                           		                                  |@@\n";
cout<<"\t\t\t\t\t@@|                                           		                                  |@@\n";
cout<<"\t\t\t\t\t@@|                                           		                                  |@@\n";
cout<<"\t\t\t\t\t@@|                               THANK YOU FOR USING                                     |@@\n";
cout<<"\t\t\t\t\t@@|                                                                                       |@@\n";
cout<<"\t\t\t\t\t@@|                             S.R.M HOSPITAL MANAGEMENT SYSTEM                          |@@\n";
cout<<"\t\t\t\t\t@@|                                                                                       |@@\n";
cout<<"\t\t\t\t\t@@|                                                                                       |@@\n";
cout<<"\t\t\t\t\t@@|                                                                                       |@@\n";
cout<<"\t\t\t\t\t@@|                                                                                       |@@\n";
cout<<"\t\t\t\t\t@@|                                                                                       |@@\n";
cout<<"\t\t\t\t\t@@|                                                 -Brought To You by Group-8            |@@\n";
cout<<"\t\t\t\t\t@@|_______________________________________________________________________________________|@@\n";
cout<<"\t\t\t\t\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n\n\n\n\t\t\t\t\t";
}
    exit(0);
}
}
}
