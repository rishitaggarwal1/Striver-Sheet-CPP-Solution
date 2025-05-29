class Solution {
  public:
    // Function to sort an array using quick sort algorithm.
    void quickSort(vector<int>& arr, int low, int high) {
        // code here
        if(low>=high)
            return;
        int pivot = partition(arr,low,high);
        quickSort(arr,low,pivot-1);
        quickSort(arr,pivot+1,high);
        return;
    }

  public:
    // Function that takes last element as pivot, places the pivot element at
    // its correct position in sorted array, and places all smaller elements
    // to left of pivot and all greater elements to right of pivot.
    int partition(vector<int>& arr, int low, int high) {
        int temp=arr[low];
        int i=low,j=high;
        while(i<=j)
        {
            while(arr[i]<=temp && i<=high)  i++;
            while(arr[j]>temp && j>=low)  j--;
            if(i>j) break;
            swap(arr[i],arr[j]);
        }
        swap(arr[j],arr[low]);
        return j;
    }
};