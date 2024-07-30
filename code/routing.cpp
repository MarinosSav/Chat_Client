#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <stdlib.h>
using namespace std;

class route{
public:
    int delay;
    string next_node, final_node;
};

vector <route> routing_table;

route find_route(string destination){

    for (int i = 0; i < routing_table.size(); i++){
        if (routing_table[i].final_node == destination)
            return routing_table[i];
    }
}

int find_route_index(string destination){

    for (int i = 0; i < routing_table.size(); i++){
        if (routing_table[i].final_node == destination)
            return i;
    }
}

bool exists(string destination){

    for (int i = 0; i < routing_table.size(); i++){
        if (routing_table[i].final_node == destination)
            return true;
    }
    return false;

}

int main(){

    stringstream ss;
    string my_address;
    int line_num;
    char cmd;

    cin >> my_address >> line_num;

    string out[line_num];

   for (int i = 0; i < line_num; i++){
        cin >> cmd;
        if (cmd == 'D'){
            string str_temp;
            getline(cin, str_temp);
            string dst = str_temp.substr(6,4);
            if (exists(dst)){
                route temp = find_route(dst);
                ss << temp.next_node << " " << temp.delay;
                out[i] = ss.str();
                ss.str("");
            }
            else
                out[i] = "NO ROUTE";
        }
        else if (cmd == 'R'){
            out[i] = "THANK YOU";
            string table_source;
            int table_delay, entries;
            bool overwrite = false;
            cin >> table_source >> table_delay >> entries;
            if(exists(table_source) && find_route(table_source).next_node == table_source){
                routing_table[find_route_index(table_source)].delay = table_delay;
                overwrite = true;
            }
            else if(!exists(table_source)){
                route temp;
                temp.final_node = table_source;
                temp.next_node = table_source;
                temp.delay = table_delay;
                routing_table.push_back(temp);
            }
            for (int j = 0; j < entries; j++){
                string destination;
                int delay;
                cin >> destination >> delay;
                if (exists(destination) && (destination != my_address)){
                    route temp = find_route(destination);
                    if (overwrite && (temp.next_node == table_source))
                        temp.delay = delay + table_delay;
                    else if (delay + table_delay < temp.delay){
                        routing_table[find_route_index(destination)].delay = delay + table_delay;
                        routing_table[find_route_index(destination)].next_node = table_source;
                    }
                }
                else if (!exists(destination)){
                    route temp;
                    temp.final_node = destination;
                    temp.next_node = table_source;
                    temp.delay = delay + table_delay;
                    routing_table.push_back(temp);
                }
            }
        }
   }

    for (int i = 0; i < line_num; i++){
        cout << out[i] << endl;
    }

    return 0;}
