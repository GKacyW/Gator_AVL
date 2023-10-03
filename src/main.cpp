#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include "AVL_TREE.h"
using namespace std;


bool is_number(string a){ // used to determine if the string is composed only of numbers
    for(char b: a){
        if(!isdigit(b)){
            return false;
        }
    }
    return true;
}
bool is_name(string a){ // used to determine if the string comprises only letters and spaces

    for(char b: a){
        if(!isalpha(b) && b != ' '){
            return false;
        }
    }
    return true;

}

int main() {
    AVL tree = *new AVL; // creating a tree


    //getting how many instructions from users
    int instruction_count;
    int count = 0; // this is so it doesn't print unsuccessful even though nothing got put in yet
    cin >> instruction_count;

    while(count <= instruction_count){

        //I referenced this code from the Project 1 Breakdown Powerpoint, along with the rest of the getline stuff
        string line;
        getline(cin, line);

        istringstream in(line);

        string command;
        in >> command;

        if(command == "insert"){

            // i didn't know what to do with the blank, so it's staying here
            string blank;
            getline(in, blank, '"');

            // getting student name
            string student_name;
            getline(in, student_name, '"');

            string ID_Number;
            getline(in, ID_Number);
            ID_Number.erase(0,1);

            if(is_number(ID_Number) && is_name(student_name))

                tree.insert(stoi(ID_Number), student_name);

            else

                cout << "unsuccessful" << endl;



        }
        else if(command == "remove"){

            string ID_Number;
            getline(in, ID_Number);
            ID_Number.erase(0,1); // erasing the space in the beginning

            if(is_number(ID_Number) && ID_Number.length() == 8){ // if valid number and length, send to remove
                tree.remove(stoi(ID_Number));
            }
            else{
                cout << "unsuccessful" << endl;
            }
        }
        else if(command == "search"){
            string search;
            getline(in, search);
            search.erase(0,1);

            if(is_number(search) && search.length() == 8){
                tree.search_ID(stoi(search));
            }
            else {
                // if not a number, format the name correctly by removing ["]
                search.erase(0,1);
                search.erase(search.end() - 1, search.end());

                //checks if it's a valid name
                if (is_name(search)) {
                    tree.search_name(search);
                }
                else
                    cout << "unsuccessful: outside" << endl; //didn't write a correctly formatted name/number
            }
        }
        else if(command == "printInorder"){
            tree.display("in"); // send directly to display
        }
        else if(command == "printPreorder"){
            tree.display("pre");
        }
        else if(command == "printPostorder"){
            tree.display("post");
        }
        else if(command == "printLevelCount"){
            tree.print_level_count();
        }
        else if(command == "removeInorder"){

            string n;
            getline(in, n);

            n.erase(0,1); // remove space in beginning

            if(is_number(n)){
                tree.remove_nth_node(stoi(n));
            }
            else
                cout << "unsuccessful" << endl;

        }
        else if(count != 0)
            cout << "unsuccessful" << endl;

        count ++;
    }

}
