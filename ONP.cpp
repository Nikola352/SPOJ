#include <bits/stdc++.h>
using namespace std;
 
int prec(char x){
    // precedence
    switch(x){
    case '^':
        return 3;
    case '*':
    case '/':
        return 2;
    case '+':
    case '-':
        return 1;
    default:
        return -1;
    }
}
 
void zoo(){
    string exp, out;
    cin >> exp;
 
    stack<char> st;
 
    for(char c : exp){
        if(c>='a' && c<='z'){
            // operand
            out += c;
        } else if(c=='('){
            st.push(c);
        } else if(c==')'){
            while(st.top()!='('){
                out += st.top();
                st.pop();
            }
            st.pop();
        } else{
            // operator
            if(st.empty() || prec(c) > prec(st.top()))
                st.push(c);
            else{
                while(!st.empty() && prec(c) <= prec(st.top())){
                    out += st.top();
                    st.pop();
                }
                st.push(c);
            }
        }
    }
 
    // remaining elements
    while(!st.empty()){
        out += st.top();
        st.pop();
    }
 
    cout << out << endl;
 
}
 
int main(){
    int T;
    cin >> T;
 
    while(T--)
        zoo();
 
    return 0;
}