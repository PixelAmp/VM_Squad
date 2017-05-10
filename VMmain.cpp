#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
//#include "searchandUpdate.cpp"
using namespace std;


class VM {
private:
	static const int TLBsize = 16;
	static const int PageTableSize = 256;
	static const int frameSize = 256;
/*
	int TLBtable[TLBsize];
	int PageTable[PageTableSize];
	int frameTable[frameSize];	//physical memory
	*/
	int TLBtable[16];
	int PageTable[256];
	int frameTable[256];	//physical memory
	int pageFaultcount = 0;

	int tlbIndex=0;
    int pageTableIndex=0;

public:
	VM(); //constructor
	~VM(); //destructor
	int toInt(string);
	string toBinary(int);

	int central(string); //heart of the function. This is where the mega loop is

    int tlbSearch(int); //Andrew's thing
    void updateTLBVM(int, int, int);//

protected:
	//nothing?
};

VM::VM() //constructor
{


}

VM::~VM() //destructor
{



}

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

string VM::toBinary(int n) //turns passed integer into a 32 bit binary string
{
    string r;
    while(n!=0) {r=(n%2==0 ?"0":"1")+r; n/=2;}
    while(r.size() != 32) {r = '0' + r;}

    return r;
}

int VM::central(string fileName)
{
	int page = 0, offset = 0; //holds page number and offset
	string binary;
	ifstream address, data;

    address.open(fileName.data()); //opens file

   	 if (address == NULL){ //checks to make sure file exists
     	   cout << "file does not exist" << endl;
     	   return 1;}


	while(!data.eof())	//while there are addresses to read
	{
        address >> page; //reads in a number from the file; reuse since we're throwing away this value anyway

		binary = toBinary(page); //makes input a 32 bit number

		page = toInt(binary.substr(16,8)); //makes 15-8 to an int for the page
		offset = toInt(binary.substr(24,8)); // makes 7-0 to an int for the offset

		//check TLB for page number
		//tlbSearch(int& tlbArray[][],int& pageTable[][],int toFind)
		bool searchResult = tlbSearch(page);

		if(searchResult == true)	//hit
		{
			//generate physical address
		}
		else	//page does not exist in TLB miss
		{
		//check page table for page number
			bool pageSearchResult = tlbSearch(page);

			if(pageSearchResult == true)	//page number is in page table
			{
					//use FIFO function to update tlb

					//generate physical address
			}
			else	//page number is not in page table
			{
				pageFaultcount++;	//page fault occured

				//transfer page to memory from disk

				//check if page table is full
				if(/*page table is not full*/)
				{
					//store in page table
				}
				else	//page table is full
				{
						//perform page replacement, LRU algorithm
				}
			}
		}

	}

}



int VM::tlbSearch(int toFind)//int& tlbArray[][],int& pageTable[][],int toFind)
{
	int found= -1;
	for(int i=0;i<sizeof(tlbArray)-1;i++)
	{
		if(tlbArray[i][0]==toFind)
		{
			found=1;
		}
	}
	if(found==-1)
	{
		for(int i=0;i<sizeof(pageTable)-1;i++)
		{
			if(pageTable[i][0]==toFind)
			{
				found=0;
			}
		}
	}
	if(found==-1)
	{
		pageFaultCount++;
	}
	return found;
}

void VM::updateTLBVM(int page, int frame, int status)//int& tlbArray[][],int& pageTable[][],int page,int frame,int status)
{
	if(status==-1)
	{
		pageTable[pageTableIndex][0]=page;
		pageTable[pageTableIndex][1]=frame;
		pageTableIndex++;
		tlbArray[tlbIndex][0]=page;
		tlbArray[tlbIndex][1]=frame;
		tlbArrayIndex++;
	}
	else if(status==0)
	{
		tlbArray[tlbIndex][0]=page;
		tlbArray[tlbIndex][1]=frame;
		tlbIndex++;
	}
	else
	{
		printf("\nTLB HIT NO UPDATE\n");
	}
	if(tlbIndex==sizeof(tlbArray)-1)
	{
		tlbIndex=0;
	}
	if(pageTableIndex==sizeof(pageTable)-1)
	{
		pageTableIndex=0;
	}
}



