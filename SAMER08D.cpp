#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
 
int max(int a, int b) {
    return (a > b ? a : b);
}
 
int lcs(string& str1, string& str2, int k) {
    int l1 = str1.length(), l2 = str2.length();
    vector<vector<int>> dp(l1+1, vector<int>(l2+1, 0));
    vector<vector<int>> seg(l1+1, vector<int>(l2+1, 0));
    for (int i = 1; i <= l1; i++) {
        for (int j = 1; j <= l2; j++) {
			dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            if (str1[i-1] == str2[j-1])
                seg[i][j] = seg[i-1][j-1] + 1;
            if (seg[i][j] >= k) {
                for (int z = k; z <= seg[i][j]; z++) 
                    dp[i][j] = max(dp[i][j], dp[i-z][j-z] + z);
            }
        }
    }
    return dp[l1][l2];
}
 
int main() {
    int k;
    cin >> k;
    while (k) {
        string str1, str2;
        cin >> str1 >> str2;
        cout << lcs(str1, str2, k) << endl;
        cin >> k;
    }
}