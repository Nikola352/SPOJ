// gives WA
// I have no idea why or how this clould fail
// works for every test case that I can imagine

#include <bits/stdc++.h>
using namespace std;
    
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    int n;
    cin >> n;
    
    while(n > 0){
        unordered_set<string> ins(n);
        for(int i=0; i<n; i++){
            string str;
            cin >> str;
            ins.insert(str);
        }
        cin.ignore();
    
        string line;
        getline(cin, line);
        while(line != "LAST CASE"){
            int sp = line.find(' ');
            string abrv = line.substr(0, sp);
    
            istringstream iss(line.substr(sp+1));
            vector<string> words;
            string word;
            while(iss >> word){
                if(ins.find(word) == ins.end())
                    words.push_back(word);
            }
    
            word = "";
            int n1 = abrv.length(), n2 = 0;
            vector<int> lastword;
            for(string& w : words){
                for(char& c : w){
                    c += 'A' - 'a';
                    lastword.push_back(n2-1);
                }
                word += w;
                n2 += w.length();
            }
    
            vector<vector<int>> dp(n1, vector<int>(n2, 0));
            dp[0][0] = (abrv[0] == word[0]);
            for(int j=1; lastword[j]==-1; j++){
                dp[0][j] = dp[0][j-1];
                if(abrv[0] == word[j])
                    dp[0][j]++;
            }
    
            for(int i=1; i<n1; i++){
                for(int j=i; j<n2; j++){
                    if(lastword[j] != j-1)
                        dp[i][j] = dp[i][j-1];
                    if(abrv[i] == word[j]){
                        dp[i][j] += dp[i-1][j-1];
                        if(dp[i-1][j-1] == 0)
                            dp[i][j] += dp[i-1][lastword[j]];
                    }
                }
            }
    
            if(dp[n1-1][n2-1] == 0)
                cout << abrv << " is not a valid abbreviation\n";
            else 
                cout << abrv << " can be formed in " << dp[n1-1][n2-1] << " ways\n";
    
            getline(cin, line);
        }
    
        cin >> n;
    }
    
    return 0;
} 