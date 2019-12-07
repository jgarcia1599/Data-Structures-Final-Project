#include<iostream>
#include<fstream>
#include<cmath>
#include<list>
#include<sstream>
#include<vector>
#include <iostream>
#include <algorithm>//Library used for sorting 
#include <iterator>
#include <string>


using namespace std; 



class HashNode
{
	public:
		string key;
	  	string hotelname;
		string cityname;
		string value;
	public:
		HashNode(string,string,string,string);
		string getKey();
		string getValue();
};

class HashMap
{
    private:
		list<HashNode> *buckets;		// Array of Pointers to Hash Nodes
		int size;					//Current Size of HashMap
		int capacity;				// Total Capacity of HashMap

    public: 
		HashMap(int capacity);
		int hashCode(const string);
		void insert(const string, const string,const string,const string);
		void search(const string key);
		void remove(const string,const string,const string);
		int getSize();
		list<HashNode> getBucket();
		vector <string> sortNodes();
		~HashMap();

};

bool mycomp(string, string);	
vector<string> Sort(vector<string>);
void dump (vector<string>);


