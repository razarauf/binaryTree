//  Raza Rauf
//  main.cpp
//  Binary Tree project
//
//  The program implements the binary tree data structure.

#include "TreeType.h"

int main()
{
    //Creating objects of type TreeType
    TreeType<int> t1;
    TreeType<int> t2;
    int inp;
    
    //Inserting nodes into one of the TreeType objects
    cout << "How many nodes?";
    int n;
    cin >> n;
    cout << "Insert: " << endl;
    for (int i=0; i<n; i++)
    {
        cin >> inp;
        t1.InsertItem(inp);
    }
    
    //Printing the structure of the TreeType object
    t1.showStructure();
    cout << endl;
    
    cout << "How many nodes?";
    cin >> n;
    cout << "Insert: " << endl;
    for (int i=0; i<n; i++)
    {
        cin >> inp;
        t2.InsertItem(inp);
    }
    t2.showStructure();
    cout << endl;
    
    //This member function is used to compare the structure of two TreeType objects
    if(t1.SimilarTreesHelp(t2))
        cout << "\nBoth trees have the same structure." << endl;
    else
        cout << "\nBoth trees does not have the same structure." << endl;
    
    //Print out the middle node of the first TreeType object
    int mid=t1.midNode();
    cout << "Midpoint for tree #1 is: " << mid << endl;
    
    cin.get();
    
    return 0;

}