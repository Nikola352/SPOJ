#include <bits/stdc++.h>
using namespace std;
 
struct Card{
    int col, val;
};
 
struct Seq{
    Card last;
    int length;
    Seq(Card card, int length): last(card), length(length){}
};
 
bool compCards(Card c1, Card c2, int perm[]){
    int i1=-1, i2=-1;
    for(int i=0; i1==-1 || i2==-1; i++){
        if(c1.col == perm[i])
            i1 = i;
        if(c2.col == perm[i])
            i2 = i;
    }
    if(i1 == i2)
        return (c1.val < c2.val);
    return (i1 < i2);
}
 
int LIS(int c, int n, int perm[], Card arr[]){
    vector<Seq> lis;
    Seq firstSeq(arr[0], 1);
    lis.push_back(firstSeq);
    for(int i=1; i<c*n; i++){
        int maxLength = 0;
        for(int j=0; j<lis.size(); j++){
            if(compCards(lis[j].last, arr[i], perm) // lis[j] < arr[i]
            && lis[j].length > maxLength){
                maxLength = lis[j].length;
            }
        }
        if(maxLength == 0){
            Seq newSeq(arr[i], 1);
            lis.push_back(newSeq);
        } else{
            Seq newSeq(arr[i], maxLength+1);
            lis.push_back(newSeq);
        }
    }
 
    int max = lis[0].length;
    for(int i=1; i<lis.size(); i++){
        if(lis[i].length > max)
            max = lis[i].length;
    }
    return max;
}
 
int minMoves(int c, int n, Card arr[]){
    int perm[c];
    for(int i=0; i<c; i++)
        perm[i] = i+1;
 
    int min = INT_MAX;
    do{
        int p = c*n - LIS(c, n, perm, arr);
        if(p<min) min = p;
    } while(next_permutation(perm, perm+c));
    return min;
}
 
int main() {
    int c, n;
    cin >> c >> n;
 
    Card arr[c*n];
    for(int i=0; i<c*n; i++)
        cin >> arr[i].col >> arr[i].val;
 
    cout << minMoves(c, n, arr);
 
    return 0;
}