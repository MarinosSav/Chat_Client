#include <iostream>
#include <stdlib.h>
#include <string>
#include <sstream>

using namespace std;

int main(){

    int link_num, msg_num, temp;
    string port, frame, dst, temp_str;
    stringstream ss;
    bool found;

    cin >> link_num >> msg_num;

    string arr[msg_num][2], out[msg_num];

    for (int i = 0; i < msg_num; i++){
        cin >> port >> frame;
        found = false;
        arr[i][0] = port;
        arr[i][1] = frame.substr(4 , 4);
        for (int j = 0; j < i; j++){
            if (frame.substr(0 , 4) == arr[j][1]){
                temp = j;
                found = true;
                break;
            }
        }
        if (found){
            if (port != arr[temp][0])
                out[i] = frame + " " + arr[temp][0];
            else
                out[i] = frame;
        }
        else {
            out[i] = frame;
            for (int j = 0; j < link_num; j++){
                if (j != (int)strtol(port.c_str(), NULL, 10)){
                    ss << " " << j;
                }
            }
            out[i] = out[i] + ss.str();
            ss.str("");
        }
    }

    cout << endl;
    for (int i = 0; i < msg_num; i++){
        cout << out[i] << endl;
    }

    system("PAUSE");
    return 0;
}
