#include "functions.h"

using namespace std;


int main(int argc,char *argv[])
{
	string filename;
	int number=0;

	for(int i =0;i<argc;i++){
		if(strcmp(argv[i],"-i")==0){
			filename = argv[i+1];
		}
		else if (strcmp(argv[i], "-o")==0 && i+1 <argc){
			string outputfilename = argv[i+1];
		}
	}

	ifstream fin;
	fin.open(filename);
	if(!fin)
	{
		cout<<"Can not open the file "<<filename;
		exit(-1);
	}

	string line;
	HashMap myHashMap(105943);// Prime number bigger than > 19880*1.333;
	HashMap myCityMap(105943);
	getline(fin,line);  //skip first line
	while(!fin.eof())
	{
		string hotel,value,city;
		getline(fin,hotel,',');
		getline(fin,city,',');
		getline(fin,value);
		string citykey=city;
		string hotelkey=hotel+','+city;
		myHashMap.insert(hotel,city,hotelkey,value);
		myCityMap.insert(hotel,city,citykey,value);
	}
	fin.close();
	cout<<"Number of hotels in the file:  "<<myHashMap.getSize()<<endl;
	bool terminate=true;
	cout<<"Welcome to the hotelfinder application! What would you like to do (type in the appropiate number): "<<endl;
	while(terminate)
	{
		cout<<"\n 1.Find Hotel \n 2.Add Hotel \n 3.Delete Hotel \n 4.Dump F \n 5.All Hotels in a city \n 6.Terminate Program "<<endl;
		string input1;
		getline(cin,input1);
		int choice;
		istringstream iss (input1);
		iss>>choice;
		string input,hotel,city,value,citykey,hotelkey;
		vector <string> sortednodes;
		clock_t t; 
		double time_taken;
		switch(choice)
		{
			case 1:
				cout<<"Find a hotel by typing the query in the following format: (hotelname,cityname)"<<endl;
				getline(cin,input);
				t=clock();
				myHashMap.search(input);
				t=clock()-t;
				time_taken=((double)t)/CLOCKS_PER_SEC;
				cout<<"Time to perform search in seconds: "<<time_taken<<endl;
				break;

			case 2:

				cout<<"Add a hotel by typing the query in the following format: (hotelname,cityname,stars,price,countryname,address)"<<endl;
				getline(cin,hotel,',');
				getline(cin,city,',');
				getline(cin,value);
				citykey=city;
				hotelkey=hotel+','+city;
				myHashMap.insert(hotel,city,hotelkey,value);
				myCityMap.insert(hotel,city,citykey,value);
				cout<<"Hotel: "<<hotel<<" has been added succesfully!"<<endl;
				break;

			case 3: 

				cout<<"Delete a hotel by typing the query in the following format: (hotelname,cityname)"<<endl;
				getline(cin,hotel,',');
				getline(cin,city);
				myHashMap.remove((hotel+','+city),hotel,city);
				myCityMap.remove(city,hotel,city);
				break;

			case 4:
				sortednodes=myHashMap.sortNodes();
				dump(sortednodes);
				break;

			case 5: 

				cout<<"Type in the city name to find all the hotels in the city"<<endl;
				getline(cin,input);
				cout<<endl;
				cout<<"The following are the hotels located in city "<<input<<": "<<endl;
				myCityMap.search(input);
				break;

			case 6: 
				cout<<"Program terminated succesfully!"<<endl;
				terminate=false;
				break;

			default:
				cout<<"Invalid option! Try again"<<endl;
				break;
		}
	}
	exit(0);
}