#include <iostream>
#include <ifstream>
using namespace std;

//Global Variables
const int TLBsize = 16;
const int PageTableSize = 256;
const int frameSize = 256;

int main()
{
	int TLBtable[TLBsize];
	int PageTable[PageTableSize];
	int frameTable[frameSize];		//physical memory
	
	while(address.open("address.txt"))	//while addresses still exist
	{
		//convert to binary
		string result = decToBin(/*input from address.txt*/);
		
		//split resulting binary string into two 8 bit strings
		
		//convert string to page number and offset
		
		//check TLB for page number
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
					//update TLB
					//generate physical address
			}
			else	//page number is not in page table
			{
				//read page from disk
				
				//activate I/O hardware
				
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