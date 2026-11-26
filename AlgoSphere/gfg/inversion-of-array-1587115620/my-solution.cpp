// Count Inversions (GeeksforGeeks, Medium)
// https://www.geeksforgeeks.org/problems/inversion-of-array-1587115620/1
// My accepted solution · 2026-11-26 · runtime 0.34 s

class Solution {
  public:
    int cnt=0;
    void merge(vector<int> &arr, int l, int r, int mid)
    {
        int i=l,j=mid+1;
        vector<int> v(r-l+1);
        int k=0;
        while(i<=mid && j<=r)
        {
            if(arr[i]<=arr[j])
            {
                v[k++]=arr[i++];
            }
            else
            {
                cnt+=(mid-i+1);
                v[k++]=arr[j++];
            }
        }
        while(i<=mid)
            v[k++]=arr[i++];
        while(j<=r)
            v[k++]=arr[j++];
        for(int i=l,k=0;i<=r;i++,k++)
        {
            arr[i]=v[k];
        }
        return;
    }
    void mergeSort(vector<int> &arr, int l, int r)
    {
        if(l>=r)    return;
        int mid = l + (r-l)/2;
        mergeSort(arr,l,mid);
        mergeSort(arr,mid+1,r);
        merge(arr,l,r,mid);
    }
    int inversionCount(vector<int> &arr) {
        // code here
        int n = arr.size();
        mergeSort(arr,0,n-1);
        return cnt;
    }
};
