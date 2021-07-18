#include <bits/stdc++.h>
using namespace std;
 
bool canArrange(int arr[1000], int n){
    stack<int> st;
    int next = 1;
    int i=0;
    while(i<n){
        if(!st.empty() && st.top()==next){
            st.pop();
            next++;
        } else if(arr[i]==next){
            next++;
            i++;
        }
        else {
            st.push(arr[i]);
            i++;
        }
    }
 
    while(!st.empty() && st.top()==next){
        st.pop();
        next++;
    }
 
    if(next==n+1) return true;
    else return false;
}
 
int main(){
    int n;
    int arr[1000];
    cin >> n;
    while(n!=0){
        for(int i=0; i<n; i++) cin >> arr[i];
 
        if(canArrange(arr, n))
            cout << "yes" << endl;
        else
            cout << "no" << endl;
 
        cin >> n;
    }
 
    return 0;
}