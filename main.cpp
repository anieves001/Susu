#include<iostream>
#include<unistd.h>
#include<string>
#include "hands.h"
#include<sys/types.h>
#include<sys/wait.h>

using namespace std;
using namespace nieves_hands;

void clear_screen();
void display_greeting();
void printParticipants(participant* i_ptr,int n);
participant* add_participant(participant* i_ptr,int& n);
participant* delete_participant(participant* i_ptr,int& n);
void hands_Order(participant* i_ptr,int n);
string displaymoney(double money);

int main(){
	int hands;
	double amount;
	string name,session;
	clear_screen();
	display_greeting();
	cout<<"*****************************/WELCOME TO SUSU/******************************\n"<<"Is this a new session y/n? ";
	cin>>session;
	clear_screen();
	if((session.compare("y")==0)||(session.compare("Y")==0)){
		cout<<"Please enter the amount of hands for this session and press Enter\n"<<"number of hands: ";
		cin>>hands;
		participant* ptr;
		ptr = new participant[hands];
		cout<<"Enter the amount per hand and press Enter\n"<<"U.S. dollars: $ ";
		cin>>amount;
		double total = amount*(double(hands));
		string dollars=displaymoney(total);
		cout<<"total amount = $ "<<dollars<<"\n";
		cout<<"Please enter participant name in order of hand and press Enter\n";
		for(int i = 0;i<hands;i++){
			cout<<"Hand "<<i+1<<": ";
			cin>>ws;	//clear input buffer
			getline(cin,name);
			ptr[i].setName(name);
			ptr[i].setNum(i+1);
		}
		clear_screen();
		printParticipants(ptr,hands);
		cout<<"Is this order correct y/n? ";
		cin>>session;
		while((session.compare("n")==0)||(session.compare("N")==0)){
			hands_Order(ptr,hands);
			printParticipants(ptr,hands);
			cout<<"Is this order correct y/n? ";
			cin>>session;
		}
		cout<<"Would you like to Add, Delete or Reorder a Participant? y/n: ";
		cin>>session;
		while((session.compare("y")==0)||(session.compare("Y")==0)){

			cout<<"Choose from the available options below\n";
			cout<<"a: add participant\n";
			cout<<"d: delete participant\n";
			cout<<"c: change order\n";
			char a;
			cin>>a;

			switch(a){			
			
				case 'a':ptr=add_participant(ptr,hands);
					break;
				case 'd':ptr=delete_participant(ptr,hands);
					break;
				case 'c':hands_Order(ptr,hands);
				       break;

			}
			printParticipants(ptr,hands);
			cout<<"Would you like to Add, Delete or Reorder a Participant? y/n: ";
			cin>>session;
			
		}
	}
	else{
		//upload previous session;
	}
	return 0;
}

void clear_screen(){

	int status;
	char* argv[1];
	argv[0] = NULL;
	int child = fork();
	if(child==0)
		execvp("clear",&argv[0]);
	else{
		waitpid(child,&status,0);
	}
}

void display_greeting(){
  cout<<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n";
	cout<<"$$                                                                        $$\n";
	cout<<"$$ ****  *  ****  *******  ***    *****     *****       *   *      ****** $$\n";
  cout<<"$$  *** *** ***   ***      ***   *** ****  *******     *** ***     ***    $$\n";
  cout<<"$$   *********    *******  ***  ***       **** ****   *********    ****** $$\n";
  cout<<"$$    *** ***     ***      ***   *** ****  *******   *** *** ***   ***    $$\n";
  cout<<"$$     *   *      *******  ***    *****     *****   ****  *  ****  ****** $$\n";
  cout<<"$$                                                                        $$\n";
  cout<<"$$                                                                        $$\n";
  cout<<"$$                          *******   *****                               $$\n";
  cout<<"$$                          *******  *******                              $$\n";
  cout<<"$$                            ***   **** ****                             $$\n";
  cout<<"$$                            ***    *******                              $$\n";
  cout<<"$$                            ***     *****                               $$\n";
  cout<<"$$                                                                        $$\n";
  cout<<"$$                       **                **                             $$\n";
  cout<<"$$                     *****   ** **     *****   ** **                    $$\n";
  cout<<"$$                    *** ***  ** **    *** ***  ** **                    $$\n";
  cout<<"$$                     ***     ** **     ***     ** **                    $$\n";
  cout<<"$$                  *** ***    *****  *** ***    *****                    $$\n";
  cout<<"$$                   ******    *****   ******    *****                    $$\n";
  cout<<"$$                     **                **                               $$\n";
  cout<<"$$                                                                        $$\n";
	cout<<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n";

}

void printParticipants(participant* i_ptr,int n){
	cout<<"----Name-----------Hand-----------Collected----\n";
	int spaces;
	for(int i = 0;i<n;i++){
		cout<<i_ptr[i].getName();
		string temp=i_ptr[i].getName();
		if(temp.size()<19)
			spaces=19-temp.size();
		while(spaces>0){
			cout<<" ";
			spaces--;
		}
		cout<<i_ptr[i].getNum()<<"               ";
		if(i_ptr[i].handStatus()==1)
			cout<<"Yes\n";
		else
			cout<<"No\n";
	}
}

participant* add_participant(participant* i_ptr,int& n){
	string name;
	cout<<"Enter name: ";
	cin>>ws;
	getline(cin,name);
	participant* p1,*p2,*p3;
	p1=i_ptr;
	i_ptr=new participant[n+1];//create larger array for new participant
	for(int i=0;i<n;i++){ //migrate participants with new participant
		p2=&i_ptr[i];
		p3=&p1[i];
		*p2=*p3;
	}
	n++;
	i_ptr[n-1].setName(name);
	i_ptr[n-1].setNum(n);
	delete[] p1;
	return i_ptr;
}

participant* delete_participant(participant* i_ptr,int& n){
	int d,j=0;
	participant* p1,*p2,*p3;
	cout<<"Enter the number of the participant to be deleted: ";
	cin>>d;
	if((d<=n)&&(d>0)){
		p1=i_ptr;
		i_ptr=new participant[n-1];
		for(int i=0;i<n;i++){
			p3=&p1[i];
			p2=&i_ptr[j];
			if(p1[i].getNum()!=d){
				*p2=*p3;
				j++;
				(*p2).setNum(j);
			}
		}
		n--;
		delete[] p1;

	}
	else{
		cout<<"Please enter a valid number.\n";
	}
	return i_ptr;
}

void hands_Order(participant* ptr,int n){
	int num1,num2;
	participant* p1,*p2,*p3;
	cout<<"Which hand would you like to change? ";
	cin>>num1;
	cout<<"What number would you like to change it to? ";
	cin>>num2;
	p1=new participant(ptr[num1-1]);	//save participant object to change order
	(*p1).setNum(num2);	//set the participants new hand number
	if((num1<num2)&&(num1>0)&&(num2<=n)){		//condition in which participant is being set to a later hand
		p2=&ptr[num1-1];	
		for(int i = num1;i<num2;i++){		//shifts all participants one space left until we reached the desired place
			p3=&ptr[i];
			(*p3).setNum(i);	//updates each participants new hand number before being shifted one space.
			*p2=*p3;
			p2=p2+1;
		}
		*p2=*p1;	//sets selected participant to new hand.
	}
	else if((num1>num2)&&(num2>0)&&(num1<=n)){	//condition participant is being set to an earlier hand
		p2=&ptr[num1-1];
		for(int i = num1-1;i>num2-1;i--){	//shifts all participants one space right until the desired place is reached
			p3=&ptr[i-1];
			(*p3).setNum(i+1);
			*p2=*p3;
			p2=p2-1;
		}
		*p2=*p1;
	}
	else{
		if(num1!=num2)
			cout<<"Please enter a valid number between and including 1 and "<<n<<"\n";
	}
	delete p1;
		
}
string displaymoney(double money){

	string dollars=to_string(money);
	string accum;
	char test;
	int j=0;

	for(int i=0;i<dollars.size()-4;i++){
		accum+=dollars[i];
		test=dollars[i+1];

		if(((dollars.size()%11)%3==0)&&!(test=='.')&&(i<dollars.size()-7)){
			if(i==0||j==3){
				accum+=",";
				j=0;
			}
			j++;
		}
		else if(((dollars.size()%12)%3==0)&&!(test=='.')&&(i<dollars.size()-7)){
			if(i==1||j==3){
				accum+=",";
				j=0;
			}
			j++;
		}
		else if(((dollars.size()%13)%3==0)&&!(test=='.')&&(i<dollars.size()-7)){
			if(i==2||j==3){
				accum+=",";
				j=0;
			}
			j++;
		}

	}
	return accum;
}

