//41043257 �@�l�� 
#include <cstdio>
#include <iostream>
using namespace std;
 
// str : �x�s�r�� 
// index : �^�ǥثe��subset, curr
// curr : �x�s�ثe��subset
void powerset(string str, int index = -1, string curr = "")
{
    int n = str.length();//�p����� 
    
    if (index == n)
        return;
 
    cout << curr << "\n";//�L�X�ثe��subset 
 
    // Try appending remaining characters to current subset
    for (int i = index + 1; i < n; i++) {
 
        curr += str[i];
        powerset(str, i, curr); 
 
        
        curr.erase(curr.size() - 1);//�N�̫�@�Ӷ��X�R�� 
    }
    return;
}
 
int main()
{
	string str = "abcd";
    powerset(str);
    return 0;
}
