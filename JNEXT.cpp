#include <bits/stdc++.h>
using namespace std;
 
int closestGreater(int x, vector<int>& arr, int l, int r){
    // O(log(r-l))
    while(l<=r){
        int m = l + (r-l)/2;
        if(arr[m] <= x)
            r = m-1;
        else
            l = m+1;
    }
    return l-1;
}
 
void swap(int& x, int& y){
    int temp = x;
    x = y;
    y = temp;
}
 
bool nextPermutation(vector<int>& arr){
    int n = arr.size();
    bool is_greatest = true;
    for(int i=n-2; i>=0; i--){
        if(arr[i]<arr[i+1]){
            // there is a lexicographically greater variation
            is_greatest = false;
            // swap arr[i] with the next greater elem form right
            swap(arr[i], arr[closestGreater(arr[i], arr, i+1, n-1)]);
            // sort the remainder of the array (just reverse it)
            for(int j=0; j<(n-i)/2; j++)
                swap(arr[i+1+j], arr[n-1-j]);
            // exit the for loop
            break;
        }
    }
 
    if(is_greatest) return false;
    else return true;
}
 
void zoo(){
    int n;
    cin >> n;
    vector<int> digits(n);
    for(int i=0; i<n; i++) cin >> digits[i];
 
    if(nextPermutation(digits)){
        for(int i=0; i<n; i++)
            cout << digits[i];
    } else cout << -1;
 
    cout << endl;
}
 
int main(){
    int T;
    cin >> T;
 
    while(T--)
        zoo();
 
    return 0;
}