//41043257 惲子威 
#include <cstdio>
#include <iostream>
using namespace std;
 
// str : 儲存字串 
// index : 回傳目前的subset, curr
// curr : 儲存目前的subset
void powerset(string str, int index = -1, string curr = "")
{
    int n = str.length();//計算長度 
    
    if (index == n)
        return;
 
    cout << curr << "\n";//印出目前的subset 
 
    // Try appending remaining characters to current subset
    for (int i = index + 1; i < n; i++) {
 
        curr += str[i];
        powerset(str, i, curr); 
 
        
        curr.erase(curr.size() - 1);//將最後一個集合刪除 
    }
    return;
}
 
int main()
{
	string str = "abcd";
    powerset(str);
    return 0;
}
