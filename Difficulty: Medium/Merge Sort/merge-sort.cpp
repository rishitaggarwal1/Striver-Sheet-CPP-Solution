class Solution {
  public:
    void merge(vector<int> &arr, int l, int mid, int r)
    {
        int temp[r-l+1]={0};
        int i=l,j=mid+1,k=0;
        while(i<=mid && j<=r)
        {
            if(arr[i]<arr[j])
                temp[k++]=arr[i++];
            else
                temp[k++]=arr[j++];
        }
        while(i<=mid)
            temp[k++]=arr[i++];
        while(j<=r)
            temp[k++]=arr[j++];
        for(int i=l,k=0;i<=r;)
            arr[i++]=temp[k++];
        
        return;
    }
    void mergeSort(vector<int>& arr, int l, int r) {
        // code here
        if(l>=r)
            return;
        int mid=l+(r-l)/2;
        mergeSort(arr,l,mid);
        mergeSort(arr,mid+1,r);
        merge(arr,l,mid,r);
    }
};