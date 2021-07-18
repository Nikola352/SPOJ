#include <bits/stdc++.h>
using namespace std;
    
int zoo(string str) {
    int open = 0, count=0;
    for (char ch : str) {
        if (ch == '{')
            open++;
        else if (ch == '}') {
            if (open == 0) {
                count++;
                open++;
            } else
                open--;
        }
    }
    count += open / 2;
    return count;
}
    
int main() {
    string str;
    cin >> str;
    
    for (int i = 1; str[0]!='-'; i++) {
        cout << i << ". " << zoo(str) << endl;
        cin >> str;
    }
    
    return 0;
} 