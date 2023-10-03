//
// Created by kacyw on 9/30/2023.
//

#include <iostream>
#pragma once
using namespace std;
struct Node {
    int ID_Number;
    int height = 0;
    string student_name;
    Node* left = nullptr;
    Node* right = nullptr;
    Node(int x, string s) : ID_Number(x), student_name(s), left(nullptr), right(nullptr) {}
    ~Node(){}
};
class AVL {
    Node* Root = nullptr;

    Node* insert_helper(Node* root, int number, string name);
    bool if_exists(Node *root, int ID);
    Node* remove_helper(Node* root, int ID);

    void inOrder(Node* root, vector<string>& printing);
    void PreOrder(Node* root, vector<string>& printing);
    void PostOrder(Node* root, vector<string>& printing);

    bool search_ID_Help(Node* root, int ID);
    void search_name_help(Node* root, string name, vector<int>& IDs);
    Node* find_parent(Node* root, Node* child);
    Node* find_successor(Node* root);
    void remove_nth_node_help(Node *root, vector<int>& order);

    int find_height(Node* root);
    int find_unbalance(Node* root);
    Node* shift_left(Node* root);
    Node* shift_right(Node* root);


public:
    bool insert(int number, string name);
    void display(string kind);
    void search_ID(int ID);
    void search_name(string name);
    void remove(int ID);
    void print_Root();
    void remove_nth_node(int n);
    void print_level_count();
};

