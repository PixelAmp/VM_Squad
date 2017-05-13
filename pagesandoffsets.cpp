#include <iostream>
#include <fstream>
#include <math.h>
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

int main()
{
    ifstream address;
    int page, offset, data;
    string binary;
    address.open("address.txt"); //opens file

	while(!address.eof())	//while there are addresses to read
	{

        address >> data; //reads in a number from the file; reuse since we're throwing away this value anyway

		binary = toBinary(data); //makes input a 32 bit number

		page = toInt(binary.substr(16,8)); //makes 15-8 to an int for the page
		offset = toInt(binary.substr(24,8)); // makes 7-0 to an int for the offset

        cout << data << "\t" << page << "\t" << offset << endl;
	}

    return 0;
}
