#include "TreeType.h"

int main()
{
    TreeType<int> t1;
    TreeType<int> t2;
    int inp;
    cout << "How many nodes?";
    int n;
    cin >> n;
    cout << "Insert: " << endl;
    for (int i=0; i<n; i++)
    {
        cin >> inp;
        t1.InsertItem(inp);
    }
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
    
    //2a.Write the declaration of the function SimilarTrees as a TreeType member function.
    if(t1.SimilarTreesHelp(t2))
        cout << "\nBoth trees have the same structure." << endl;
    else
        cout << "\nBoth trees does not have the same structure." << endl;
    
    int mid=t1.midNode();
    cout << "Midpoint for tree #1 is: " << mid << endl;
    
    cin.get();
    
    return 0;

}