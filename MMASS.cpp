#include <bits/stdc++.h>
using namespace std;
 
int mmass(string f){
    int n = f.length(),
        res = 0;
 
    map<char, int> mass;
    mass.insert(pair<char, int>('H', 1));
    mass.insert(pair<char, int>('C', 12));
    mass.insert(pair<char, int>('O', 16));
 
    stack<int> st;
 
    for(int i=0; i<n; i++){
        if(f[i]=='H' || f[i]=='C' || f[i]=='O'){
            st.push(mass[f[i]]);
        } else if(f[i]>='2' && f[i]<='9'){
            int val = st.top() * (int)(f[i]-'0');
            st.pop();
            st.push(val);
        } else if(f[i]=='('){
            st.push(-1);
        } else if(f[i]==')'){
            int val = 0;
            while(st.top() != -1){
                val += st.top();
                st.pop();
            }
            st.pop(); // '('
            st.push(val);
        }
    }
 
    while(!st.empty()){
        res += st.top();
        st.pop();
    }
 
    return res;
}
 
int main(){
    string formula;
    cin >> formula;
 
    cout << mmass(formula);
 
    return 0;
}