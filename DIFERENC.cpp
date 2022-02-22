#include <iostream>
#include <vector>
#include <stack>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pii;
typedef stack<pii> stii;

bool cmp(int a, int b, bool t){
    return ((a < b) == t);
}

bool cmpe(int a, int b, bool t){
    return ((a <= b) == t);
}

ll getSum(const vi& arr, int n, bool t){
    vi left(n), right(n);
    stii st;

    st.push(pii(arr[0], 0));
    left[0] = 1;
    for(int i=1; i<n; i++){
        while(!st.empty() && cmp(arr[i], st.top().first, t))
            st.pop();
        if(st.empty())
            left[i] = i+1;
        else 
            left[i] = i - st.top().second;
        st.push(pii(arr[i], i));
    }
    while(!st.empty()) st.pop();

    st.push(pii(arr[n-1], n-1));
    right[n-1] = 1;
    for(int i=n-2; i>=0; i--){
        while(!st.empty() && cmpe(arr[i], st.top().first, t))
            st.pop();
        if(st.empty())
            right[i] = n-i;
        else 
            right[i] = st.top().second - i;
        st.push(pii(arr[i], i));
    }
    
    ll res = 0;
    for(int i=0; i<n; i++)
        res += (ll)arr[i] * (ll)left[i] * (ll)right[i];
    return res;
}

int main()
{
    int n;
    cin >> n;
    vi arr(n);
    for(int i=0; i<n; i++)
        cin >> arr[i];

    cout << (getSum(arr, n, 0) - getSum(arr, n, 1)) << '\n';

    return 0;
}