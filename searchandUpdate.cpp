#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int tlbIndex=0;
int pageTableIndex=0;

int tlbSearch(int& tlbArray[][],int& pageTable[][],int toFind)
{
	int found=-1;
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

int updateTLBVM(int& tlbArray[][],int& pageTable[],int page,int frame,int status)
{
	if(status==-1)
	{
		pageTable[page]=frame;
		tlbArray[tlbIndex][0]=page;
		tlbArray[tlbIndex][1]=frame;
		tlbArrayIndex++;
	}
	else if(status==0)
	{
		tlbArray[tlbIndex][0]=page;
		tlbArray[tlbIndex][1]=frame;
		tlbIndex++;
		return pageTable[page];
	}
	else
	{
		printf("\nTLB HIT NO UPDATE\n");
		return tlbArray[page][1];
	}
	if(tlbIndex==sizeof(tlbArray)-1)
	{
		tlbIndex=0;
	}
	
	//needs a return
}
