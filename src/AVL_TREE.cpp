//
// Created by kacyw on 9/30/2023.
//

#include <vector>
#include "AVL_TREE.h"

//insert function
Node *AVL::insert_helper(Node *root, int number, string name){
    if(root == nullptr){
        return new Node(number, name);
    }
    if(number < root -> ID_Number){
        root -> left = insert_helper(root -> left, number, name);
    }
    else
        root -> right = insert_helper(root -> right, number, name);

    root -> height = find_height(root);

    int unbalance = find_unbalance(root);
    if(unbalance < -1) {
        if (find_height(root -> right -> left) > find_height(root -> right -> right)) {
            root -> right = shift_right(root -> right);
            root = shift_left(root);

            root -> height = find_height(root);

        } else {
            root = shift_left(root);
            root -> height = find_height(root);
        }
    }
    else if(unbalance > 1){
        if (find_height(root -> left -> left) < find_height(root -> left -> right)) {
            root -> left = shift_left(root -> left);
            root = shift_right(root);
            root -> height = find_height(root);

        }
        else {
            root = shift_right(root);
            root -> height = find_height(root);
        }
    }


    return root;
}
bool AVL::insert(int number, string name){

    if(if_exists(Root, number)){
        cout << "unsuccessful" << endl;
        return false;
    }

    Root = insert_helper(Root, number, name); //sends to helper so it can access the private root
    cout << "successful" << endl;
    return true;
}
bool AVL::if_exists(Node *root, int ID) {
    if(root == nullptr)
        return false; //can't search an empty tree
    else{
        if(root -> ID_Number == ID) { //checks if the ID and the search ID are the same
            return true;
        }
        else if(root -> ID_Number > ID)
            if_exists(root -> left, ID);
        else
            if_exists(root -> right, ID);
    }
}

void AVL::display(string kind) {
    // i felt like this was easier than having the several different things
    vector<string> printing;
    if(kind == "in")
        inOrder(Root, printing);
    else if(kind == "pre")
        PreOrder(Root, printing);
    else if(kind == "post")
        PostOrder(Root, printing);

    for(int i = 0; i < printing.size(); i++){
        cout << printing[i];
        if(i != printing.size() - 1){
            cout << ", ";
        }
    }
    cout << endl;

}
void AVL::inOrder(Node *root, vector<string>& printing) {

    if(root != nullptr){
        inOrder(root -> left, printing);
        printing.push_back(root -> student_name);
        inOrder(root -> right, printing);
    }
}
void AVL::PreOrder(Node *root, vector<string>& printing) {

    if(root != nullptr){
        printing.push_back(root -> student_name);
        PreOrder(root -> left, printing);
        PreOrder(root -> right, printing);
    }

}
void AVL::PostOrder(Node *root,vector<string>& printing) {
    if(root != nullptr)
    {
        PostOrder(root -> left, printing);
        PostOrder(root -> right, printing);
        printing.push_back(root -> student_name);
    }
}

void AVL::search_ID(int ID) {
    if(!search_ID_Help(Root, ID))
        cout << "unsuccessful" << endl;
}
bool AVL::search_ID_Help(Node *root, int ID) {
    if(root == nullptr)
        return false; //can't search an empty tree
    else{
        if(root -> ID_Number == ID) { //checks if the ID and the search ID are the same
            cout << root -> student_name << endl;
            return true;
        }
        else if(root -> ID_Number > ID)
            search_ID_Help(root -> left, ID);
        else
            search_ID_Help(root -> right, ID);
    }
}

void AVL::search_name(string name) {
    vector<int> IDs;
    search_name_help(Root, name, IDs);
    if(IDs.empty())
        cout << "unsuccessful" << endl;
    else {
        for(auto a: IDs)
            cout << a << endl;
    }
}
void AVL::search_name_help(Node *root, string name, vector<int>& IDs) {
    if(root != nullptr) {
        if (root -> student_name == name){
            IDs.push_back(root->ID_Number);}
        search_name_help(root->left, name, IDs);
        search_name_help(root->right, name, IDs);

    }
}

void AVL::remove(int ID) {
    if(if_exists(Root, ID)) {
        remove_helper(Root, ID);
        cout << "successful" << endl;
    }
    else
        cout << "unsuccessful" << endl;
}

Node* AVL::remove_helper(Node *root, int ID) {
    if(root == nullptr)
        return nullptr;
    else if(root -> ID_Number == ID ){
        // find parent
        Node *parent = find_parent(Root, root);

        Node *temp = root;


        if(root -> left == nullptr && root -> right == nullptr){

            //specialty case where there's only the root
            if(root == Root)
                Root = nullptr;

                // set parent left||right to nullptr, removing the node;
            else if(parent -> left == root)
                parent -> left = nullptr;
            else
                parent -> right = nullptr;

            delete temp;
        }

            //one child

        else if(root -> left == nullptr){

            if(root == Root)
                Root = root -> right;
            else if(parent -> left == root)
                parent -> left = root -> right;
            else
                parent -> right = root -> right;

            delete temp;
        }
        else if(root -> right == nullptr){

            if(root == Root)
                Root = root -> left;
            else if(parent -> left == root)
                parent -> left = root -> left;
            else
                parent -> right = root -> left;

            delete temp;
        }

            //two children removal

        else{

            Node* successor = find_successor(root);
            root -> ID_Number = successor -> ID_Number;
            root -> student_name = successor -> student_name;
            remove_helper(successor, successor -> ID_Number);


        }

    }
    else{
        if(root -> ID_Number > ID)
            remove_helper(root -> left, ID);
        else
            remove_helper(root -> right, ID);
    }
    return nullptr;
}

Node *AVL::find_parent(Node *root, Node *child) {
    if(root == nullptr)
        return nullptr;
    else{
        if(root -> left == child || root -> right == child){
            return root;
        }
        else if(root -> ID_Number > child -> ID_Number)
            find_parent(root -> left, child);
        else
            find_parent(root -> right, child);

    }
}
Node *AVL::find_successor(Node *root) {
    root = root -> right;
    while(root -> left != nullptr)
        root = root -> left;
    return root;
}

int AVL::find_height(Node *root) {

    int lHeight = 0;
    int rHeight = 0;
    if (root == nullptr || (root -> left == nullptr && root -> right == nullptr))
        return 0;

    else {

        lHeight = 1 + find_height(root->left);
        rHeight = 1 + find_height(root->right);

        if (lHeight > rHeight)
            return (lHeight);
        else
            return (rHeight);

    }
}
int AVL::find_unbalance(Node *root) {
    if(root == nullptr || root -> left == nullptr && root -> right == nullptr){
        return 0;
    }
    else if(root -> left == nullptr){
        return ((root -> height) * -1);
    }
    else if(root -> right == nullptr){
        return root -> height;
    }
    else
        return( (root -> left -> height) - (root -> right -> height));

}

Node* AVL::shift_left(Node *root) {

    Node* gchild = root -> right -> left;
    Node* new_root = root -> right;
    new_root -> left = root;
    root -> right = gchild;
    return new_root;
}
Node* AVL::shift_right(Node *root) {

    Node* gchild = root -> left -> right;
    Node* new_root = root -> left;
    new_root -> right = root;
    root -> left = gchild;
    return new_root;
}


void AVL::print_Root() {
    cout << endl << "this is the root: " << Root -> student_name << endl;
    if(Root -> left != nullptr)
        cout << "this is the left: " << Root -> left -> student_name << endl;
    if(Root -> right != nullptr)
        cout << "this is the right: " << Root -> right -> student_name << endl;
}

void AVL::remove_nth_node(int n) {
    vector<int> in_order;
    remove_nth_node_help(Root,in_order);
    if(n > in_order.size() - 1){
        cout << "unsuccessful" << endl;
    }
    else{
        remove(in_order[n]);
    }
}


void AVL::remove_nth_node_help(Node *root, vector<int>& order) {

    if (root != nullptr) {
        remove_nth_node_help(root->left, order);
        order.push_back(root->ID_Number);
        remove_nth_node_help(root->right, order);
    }
}

void AVL::print_level_count() {
    cout << (find_height(Root) + 1) << endl;
}

