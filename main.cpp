#include <iostream>
#include <fstream>
#include <string>
#include "searchandUpdate.cpp"
using namespace std;


int toInt(string bin) //turns passed string into a number
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

string toBinary(int n) //turns passed integer into a 32 bit binary string
{
    string r;
    while(n!=0) {r=(n%2==0 ?"0":"1")+r; n/=2;}
    while(r.size() != 32) {r = '0' + r;}

    return r;
}


//Global Variables
const int TLBsize = 16;
const int PageTableSize = 256;
const int frameSize = 256;
int pageFaultcount = 0;

int main()
{
	int TLBtable[TLBsize];
	int PageTable[PageTableSize];
	int frameTable[frameSize];		//physical memory
	int page = 0, offset = 0; //holds page number and offset
	string binary;
	ifstream address, data;
    	string fileName;
	
	
	if(argc != 2) { //checks to make sure there is the correct amount of arguments
            cout << "Incorrect Number of Arguments.\n" << endl;
            return 1; }

	fileName = argv[1]; //gets the file name

	address.open(fileName.data()); //opens file

   	 if (address == NULL){ //checks to make sure file exists
     	   cout << "file does not exist" << endl;
     	   return 1;}


	while(!data.eof())	//while there are addresses to read
	{
	    	address >> page; //reads in a number from the file; reuse since we're throwing away this value anyway

		binary = toBinary(input); //makes input a 32 bit number

		page = toInt(binary.substr(16,8)); //makes 15-8 to an int for the page
		offset = toInt(binary.substr(24,8)); // makes 7-0 to an int for the offset

		//check TLB for page number
		//tlbSearch(int& tlbArray[][],int& pageTable[][],int toFind)
		bool searchResult = searchFunc(/*page number*/);
		
		if(searchResult == true)	//hit
		{
			//generate physical address
		}
		else	//page does not exist in TLB miss
		{	
		//check page table for page number
			bool pageSearchResult = searchFunc(/*page number*/);
			
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
