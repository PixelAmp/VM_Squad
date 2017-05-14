/***************VMmain.cpp*******************/
//CS 433 Final Project
//Created by: Raul, Andrew, Aaron
//Last Updated: 2017/05/13
//Written in Vim and Codeblocks
//Compiled with g++
/********************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
using namespace std;

//Global Variables
int pageFaultcount = 0;
int tlbHitcount = 0;
int addressCount = 0;
int tlbIndex=0;
int pageTableIndex=0;


class VM {
private:
	static const int TLBsize = 16;
	static const int PageTableSize = 256;
	static const int frameSize = 256;

	int TLBtable[16][2];
	int PageTable[256];
	int frameTable[256];	//physical memory

	int input, page, offset;

public:
	VM(); //constructor
	~VM(); //destructor
	int toInt(string);
	string toBinary(int);

	int central(string); //heart of the function. This is where the mega loop is

    	int tlbSearch(int); //Andrew's thing
    	int updateTLBVM(int, int, int);//

protected:
	//nothing?
};

VM::VM() //constructor
{


}

VM::~VM() //destructor
{



}

//converts a string of binary to decimal
int VM::toInt(string bin) //turns passed string into a number
{
    int spot = 0, num = 0;
    for(int i = (bin.size()-1); i >= 0; i--){
            if(bin[i]== '1'){
                num += pow(2,spot);
            }
            spot++;
        }
    return num;
}

//converts a string of decimal to binary
string VM::toBinary(int n) //turns passed integer into a 32 bit binary string
{
    string r;
    while(n!=0) {r=(n%2==0 ?"0":"1")+r; n/=2;}
    while(r.size() != 32) {r = '0' + r;}

    return r;
}

//reads in from file and calls relevent functions
int VM::central(string fileName)
{
	string binary;	
	ifstream address;
	ofstream Out;
	string found;
    	address.open(fileName.data()); //opens file
	Out.open("VMresults.txt");

	Out << "Logical address" << "\t\t" << "Physical Address" << "\t" << "searchResult" << "\n";

   	if (address == NULL){ //checks to make sure file exists
     	   cout << "file does not exist" << endl;
     	   return 1;
	}
	
	while(!address.eof())	//while there are addresses to read
	{
  	      	address >> input; //reads in a number from the file; reuse since we're throwing away this value anyway		
		addressCount++;

		binary = toBinary(input); //makes input a 32 bit number

		page = toInt(binary.substr(16,8)); //makes 15-8 to an int for the page
		offset = toInt(binary.substr(24,8)); // makes 7-0 to an int for the offset

		//check TLB for page number
		//tlbSearch(int& tlbArray[][],int& pageTable[][],int toFind)
		int searchResult = tlbSearch(page);

		if(searchResult == 1)	//found in TLB, hit
		{
			tlbHitcount++;
			found = "found";
		}
		else //page fault or TLB miss
		{
			updateTLBVM(page, offset, searchResult);
			found = "not found";
		}
		
		Out << input << "\t\t\t" << offset << "\t\t\t" << found << "\n";
	}
	double PFrate = ((double)pageFaultcount / addressCount) * 100;
	double TLBrate = ((double)tlbHitcount / addressCount) * 100;

	cout << "pageFaultcount: " << pageFaultcount << "\ntlbHitcount: " << tlbHitcount << "\naddressCount: " << addressCount << "\n\n";

	cout << "Page Fault Rate: " << PFrate << "%" << endl
	     << "TLB Hit Rate: " << TLBrate << "%" << endl; 
	
	//closes stream files
	Out.close();
	address.close();
}

//seaches TLB table and page table for a virtual address
int VM::tlbSearch(int toFind)//int& tlbArray[][],int& pageTable[][],int toFind)
{
	int found= -1;
	for(int i=0;i<(TLBsize-1);i++)
	{
		if(TLBtable[i][0]==toFind) //search through TLB
		{
			found=1;
		}
	}
	if(found==-1)	//TLB miss
	{
		for(int j=0;j<(PageTableSize-1);j++)
		{
			if(PageTable[j]==toFind) //search through page table
			{
				found=0;
			}
		}
	}
	if(found==-1)	//page fault occured
	{
		pageFaultcount++;
	}
	return found;
}

//updates the TLB table and page table
int VM::updateTLBVM(int page, int frame, int status)//int& tlbArray[][],int& pageTable[][],int page,int frame,int status)
{	
	if(tlbIndex == TLBsize)	//reset FIFO order
	{
		tlbIndex=0;
	}

	if(status==-1)	//page fault
	{
		PageTable[page]=frame;
		TLBtable[tlbIndex][0]=page;
		TLBtable[tlbIndex][1]=frame;
		tlbIndex++;
	}
	else if(status==0)	//TLB miss
	{
		TLBtable[tlbIndex][0]=page;
		TLBtable[tlbIndex][1]=frame;
		tlbIndex++;
		return PageTable[page];
	}	
	else	//TLB hit
	{
		printf("\nTLB HIT NO UPDATE\n");
		return TLBtable[page][1];
	}

	return -1;
}
