#include "functions.h"

HashMap::HashMap(int capacity)
{
	buckets = new list<HashNode>[capacity];
	this->capacity = capacity;
	this->size = 0;
}

int HashMap::hashCode(const string key)
{
	unsigned long sum=0;//made tho data type unsinged long as some of the hashcodes produced where yielding a negative answer
	for(int i=0; i<key.length(); i++)
		sum += key[i]*pow(i,10); 		//Add ascci code of each letter times i power 10

	return (sum)%this->capacity;	
}
//================================================
void HashMap::insert(const string hotel, const string city,const string key,const string value)
{
		if (city==key)//CityHash case
		{
			string data= hotel+','+value;
			int index= hashCode(key);
			HashNode temp=HashNode(key,data,hotel,city);
			list<HashNode>:: iterator it;
			for (it=buckets[index].begin();it!=buckets[index].end();it++)
			{
				if((*it).hotelname==hotel)
				{
					(*it).value=data;
					return;
				}
			}
			buckets[index].push_back(temp);
			this->size+=1;

		}
		else
		{
			int index= hashCode(key);
			list<HashNode>:: iterator it;
			for (it=buckets[index].begin();it!=buckets[index].end();it++)
			{
				if((*it).key==key)
				{
					(*it).value=value;
					return;
				}
			}
			HashNode temp=HashNode(key,value,hotel,city);
			buckets[index].push_back(temp);
			this->size+=1;
		}
		

}
//===================================================
void HashMap::search(const string key)
{
	int index= hashCode(key);
	int counter=0;
	list<HashNode>:: iterator it;
	bool found=false;
	for (it=buckets[index].begin();it!=buckets[index].end();it++)
	{
		counter++;
		if((*it).key==key&& (*it).cityname!=key)//HotelHash
		{
			found=true;
			cout<<"\nThe Hotel Info has been found: "<<(*it).value<<endl;
			cout<<"Number of comparisons: "<<counter<<endl;
			cout<<endl;
			//return (*it).value;
			break;
		}
		else//CityHash case
		{
			if((*it).cityname==key)
			{
				cout<<(*it).value<<endl;
				cout<<endl;
				found=true;
			}
		}
		
	}
	if (found==false)
		{
			cout<<"Hotel not found...."<<endl;
		}
	
	//TODO
}
//=====================================================
void HashMap::remove(const string key,const string hotel, const string city)
{
	bool found=false;
	if (key==city)//CityHashCase
	{
		int index= hashCode(key);
		list<HashNode>:: iterator it;
		for (it=buckets[index].begin();it!=buckets[index].end();it++)
		{
			if((*it).cityname==city)
			{
				break;
			}
		}
		if(it!=buckets[index].end())
		{
			found=true;
			buckets[index].erase(it);
			this->size-=1;
		}
	}
	else
	{
		int index= hashCode(key);
		list<HashNode>:: iterator it;
		for (it=buckets[index].begin();it!=buckets[index].end();it++)
		{
			if((*it).key==key)
			{
				break;
			}
		}
		if(it!=buckets[index].end())
		{
			found=true;
			cout<<endl;
			cout<<"Hotel "<<(*it).hotelname<<" has been removed!"<<endl;
			cout<<endl;
			buckets[index].erase(it);
			this->size-=1;
		}
	}
	if (found==false)
	{
		cout<<endl;
		cout<<"Hotel not found...."<<endl;
		cout<<endl;
	}

	//TODO
}
//===================================================

int HashMap::getSize()
{
	return this->size;
}
list<HashNode> HashMap::getBucket()
{
	return (*this->buckets);
}

vector<string> HashMap::sortNodes()//Returns a vector with all nodes in sorted order based on hotel name
{
	vector <HashNode> nodevector;
	vector<string> sorted_string,aftersorting;
	for (int i=0;i<this->capacity;i++)
	{
		list<HashNode>:: iterator it;
		for (it=buckets[i].begin();it!=buckets[i].end();it++)
		{
			sorted_string.push_back((*it).key+','+(*it).value);
		}
	}
	aftersorting=Sort(sorted_string);//Sort string of hotelnames
	return aftersorting;
}



HashMap::~HashMap()
{
	delete[] this->buckets;
}

bool mycomp(string a, string b)
{
	string c,d;
	for (int i=0;i<a.size();i++)
	{
		c+=tolower(a[i]);//Lowercase the string to avoid case-sensitive comparison

	}
	for (int j=0;j<b.size();j++)
	{
		d+=tolower(b[j]);
	}
	return c<d;
}

vector<string> Sort(vector<string> a)
{
	int n=a.size();
	sort(a.begin(),a.end(),mycomp);//Sorting occurs here
	return a;
}

void dump (vector<string> sortednodes)
{
	ofstream file;
	file.open("sorted_data.csv");
	file<<"hotelName,cityName,stars,price,countryName,address"<<endl;
	for (int i=0;i<sortednodes.size();i++)
	{
		file<<sortednodes[i]<<endl;
	}
	cout<<"Data has been organized alphabetically and dumped succesfully in file 'sorted_data.csv'. "<<endl;
}



HashNode::HashNode(string key,string value,string hotel,string city)
	{
		this->key=key;
		this->value=value;
		this->hotelname=hotel;
		this->cityname=city;
	}
string HashNode::getKey()
	{
		return this->key;
	}
string HashNode::getValue()
	{
		return this->value;
	}










