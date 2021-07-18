#include <cstdio>
#include <queue>
using namespace std;

int main()
{
    int t;
    scanf("%d", &t);

    while(t--){
        priority_queue<int> maxheap;
        priority_queue<int> minheap;

        int sz = 0;

        int n;
        scanf("%d", &n);

        while(n != 0){
            if(n == -1){
                printf("%d\n", maxheap.top());
                maxheap.pop();
                sz--;
                while(maxheap.size() < (sz+1)/2){
                    maxheap.push(-minheap.top());
                    minheap.pop();
                }
                while(maxheap.size() > (sz+1)/2){
                    minheap.push(-maxheap.top());
                    maxheap.pop();
                }
            } else{
                if(maxheap.empty() || n < maxheap.top())
                    maxheap.push(n);
                else
                    minheap.push(-n);
                sz++;
                while(maxheap.size() < (sz+1)/2){
                    maxheap.push(-minheap.top());
                    minheap.pop();
                }
                while(maxheap.size() > (sz+1)/2){
                    minheap.push(-maxheap.top());
                    maxheap.pop();
                }
            }

            scanf("%d", &n);
        }
    }

    return 0;
}