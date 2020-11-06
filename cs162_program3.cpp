//Shang Chun Lin ; CS162 program#3
//the purpose of this assignment is to practice how to use an array of
//the structs holding the data and storing them as a file by writing them
//out to an external data file

#include <iostream>
#include <cstring>
#include <cctype>
#include <fstream>
using namespace std;

//constant
const int LIST = 5;		//how many kinds of activities
const int NAME = 16;		//the name of the activity
const int PLACE = 11;		//location
const int TIME = 16;		//time
const int DESCRIP = 131;	//description
const int THOUGHT = 201;	//your thought
const int NEED = 31;		//supplies needed
const int CERTAIN = 16;		//only available for certain dates

const char file_name[] = "favorite.txt";

//structure definition
struct activity
{
	char name[NAME];
	char place[PLACE];
	char time[TIME];
	char descrip[DESCRIP];
	char thought[THOUGHT];
	char need[NEED];
	char certain[CERTAIN];
};

//prototypes
void read_in_info(int & counter,activity list[]);
void display(int & counter,activity list[]);
void save_to_file(int & counter,activity list[]);
int read_from_file(activity list[]);
void search(activity list[]);

//main

int main()
{
	activity list[LIST];
	int counter = 0;			//to count how many activities are in the array now
	int num = read_from_file(list);		//to know how many activities have been read
	int answer = 0;

	cout<<"What do you want to do? Type 1 to load from file, 2 to add new item to the list, 3 to search a certain activity and display it,"
        <<" 4 to display all activities, and 5 to quit."<<endl;
        cin>>answer;
        cin.ignore(100,'\n');

	while(answer != 5)
	{
		if(answer == 1)
		{
			read_from_file(list);
			display(counter,list);
		}
	
		if(answer == 2)
		{
			read_in_info(counter,list);
			display(counter,list);
			save_to_file(counter,list);
		}

		if(answer == 3)
		{
			search(list);
		}
		
		if(answer == 4)
		{
			display(counter,list);
		}

		cout<<"Do you want to continue on using this program? If no, enter 5."<<endl;
		cout<<"Otherwise, Type 1 to load from file, 2 to add new item to the list, 3 to search a certain activity and display it,"
                <<" and 4 to display all activities."<<endl;
		cin>>answer;
                cin.ignore(100,'\n');
	}

	return 0;
}


//implementation of functions

void read_in_info(int & counter,activity list[])
{
	char answer = 'n';
	while(counter<LIST && toupper(answer)!= 'Y')
	{
		cout<<"Please enter the name#place#time#description#thought"<<endl
		<<"#supplies needed#only available for certain dates"<<endl
		<<" in order with the # sign. Then press enter to complete"<<endl
		<<" the process of typing. You can enter at most 5 activities in the program."<<endl;

		cin.get(list[counter].name,NAME,'#');
		cin.ignore(100,'#');
		cin.get(list[counter].place,PLACE,'#');
                cin.ignore(100,'#');
		cin.get(list[counter].time,TIME,'#');
                cin.ignore(100,'#');
		cin.get(list[counter].descrip,DESCRIP,'#');
                cin.ignore(130,'#');
		cin.get(list[counter].thought,THOUGHT,'#');
                cin.ignore(200,'#');
		cin.get(list[counter].need,NEED,'#');
                cin.ignore(100,'#');
		cin.get(list[counter].certain,CERTAIN,'\n');
                cin.ignore(100,'\n');

		++counter;

		cout<<"Do you want to stop entering more activities? Y for yes,N for no."<<endl;
		cin>>answer;
	}

	return;
}

void display(int & counter,activity list[])
{
	int i = 0;
	int j = i + 1;
	cout<<"Now the program will show you what activities are in the array."<<endl;

	for(i=0;i<counter;++i)
	{
		cout<<"The informations of the number "<<j<<" activity :"<<endl;
		cout<<"Name :"<<list[i].name<<endl;
		cout<<"Place :"<<list[i].place<<endl;
		cout<<"Time :"<<list[i].time<<endl;
		cout<<"Description :"<<list[i].descrip<<endl;
		cout<<"Thought :"<<list[i].thought<<endl;
		cout<<"Supplies needed :"<<list[i].need<<endl;
		cout<<"Only available dates :"<<list[i].certain<<endl;
	}
	return;
}

void save_to_file(int & counter,activity list[])
{
	ofstream file_out;
	file_out.open(file_name,ios::app);

	if(file_out)
	{
		for(int i=0;i<counter;++i)
		{
			file_out<<list[i].name<<'#'<<list[i].place<<'#'<<list[i].time<<'#'<<list[i].descrip<<'#'<<list[i].thought<<'#'<<list[i].need<<'#'<<list[i].certain<<endl;
		}

		file_out.close();
		file_out.clear();
	}

	return;
}

int read_from_file(activity list[])
{
	ifstream file_in;
	int i = 0;
	int j = i + 1;
	file_in.open(file_name);

	if(file_in)
	{
		file_in.get(list[i].name,NAME,'#');
		file_in.ignore(100,'#');
		while(!file_in.eof() && i<LIST)
		{
			file_in.get(list[i].place,PLACE,'#');
		        file_in.ignore(100,'#');
			file_in.get(list[i].time,TIME,'#');
		        file_in.ignore(100,'#');
			file_in.get(list[i].descrip,DESCRIP,'#');
		        file_in.ignore(100,'#');
			file_in.get(list[i].thought,THOUGHT,'#');
		        file_in.ignore(100,'#');
			file_in.get(list[i].need,NEED,'#');
		        file_in.ignore(100,'#');
			file_in.get(list[i].certain,CERTAIN,'\n');
	                file_in.ignore(100,'\n');
			cout<<"You have read in the information of the number "<<j<<" activity :"<<endl;
			cout<<"Name :"<<list[i].name<<endl;;	
			cout<<"Place :"<<list[i].place<<endl;
			cout<<"Time :"<<list[i].time<<endl;
			cout<<"Description :"<<list[i].descrip<<endl;
			cout<<"Thought :"<<list[i].thought<<endl;
			cout<<"Supplies needed :"<<list[i].need<<endl;
			cout<<"Only available dates :"<<list[i].certain<<endl;

			if(!file_in.eof() && i+1<LIST)
			{
				file_in.get(list[i+1].name,NAME,'#');
				file_in.ignore(100,'#');
			}
			++i;
		}
		file_in.close();
		file_in.clear();
	}
	return i;
}

void search(activity list[])
{
	char search_name[NAME];
	cout<<"Please enter a name of an activity to search the informations stored in the program."<<endl;
	cin.get(search_name,NAME,'\n');
	for(int i=0;i<LIST;++i)
	{
		if(strcmp(list[i].name,search_name) == 0)
		{
			cout<<"This is the information of the number "<<i<<" activity :"<<endl;
			cout<<"Name :"<<list[i].name<<endl;	
			cout<<"Place :"<<list[i].place<<endl;
			cout<<"Time :"<<list[i].time<<endl;
			cout<<"Description :"<<list[i].descrip<<endl;
			cout<<"Thought :"<<list[i].thought<<endl;
			cout<<"Supplies needed :"<<list[i].need<<endl;
			cout<<"Only available dates :"<<list[i].certain<<endl;
		}
	}	
	return;
}
