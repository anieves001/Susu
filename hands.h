
#ifndef NIEVES_SUSU_H
#define NIEVES_SUSU_H
#include<string>
using std::string;
namespace nieves_hands{

			class participant{
				
				public:
					//CONSTRUCTORS
					participant();
					participant(int n,string Pname);
					//MODIFICATION MEMBER FUNCTIONS
					void gotHand(){receivedHand=true;}
					void setName(string Pname){name=Pname;}
					void setNum(int n){num=n;}
					//CONSTANT MEMBER FUNCTIONS
					string getName() const{return name;}
					int getNum() const{return num;}
					bool handStatus() const{return receivedHand;}


				private:
					int num;
					string name;
					bool receivedHand;

			};
}
#endif

