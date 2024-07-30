#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>

using namespace std;

string HexToTxt(string hex){

	string txt;

	for(int i = 0; i < hex.length(); i += 2)
	{
		string temp = hex.substr(i,2);
		char chr = (char) (int)strtol(temp.c_str(), NULL, 16);
		txt.push_back(chr);
	}

	return txt;
}

long CheckSum(string hex){

    long sum = 0;

    for(int i = 0; i < hex.length(); i += 2)
	{
		string temp = hex.substr(i,2);
		sum += (int)strtol(temp.c_str(), NULL, 16);
	}

	return sum % 128;
}

int main(){

    string address, comp_address, src, frame_length, payload, in_str, check_sum;
    int frame_count = 0, frame_len, icheck_sum;

    cin >> comp_address >> in_str;

    while (in_str.size() != 0){
        frame_count++;
        address = in_str.substr(0, 4);
        src = in_str.substr(4, 4);
        frame_length = in_str.substr(8, 8);
        frame_len = (int)strtol(frame_length.c_str(), NULL, 16);
        payload = in_str.substr(16, (2 * frame_len) - 18);
        check_sum = in_str.substr((2 * frame_len) - 2, 2);

        if ((int)strtol(check_sum.c_str(), NULL, 16) != CheckSum(in_str.substr(0, (2 * frame_len) - 2)))
            cout << "ERROR" << endl;
        else if (address != comp_address)
            cout << "ADDRESS MISMATCH" << endl;
        else
            cout << address << " " << src << " " << frame_len << " " << HexToTxt(payload) << endl;

        in_str = in_str.erase(0, 2 * frame_len);

    }
    system("PAUSE");
    return 0;
}


