//
//  main.cpp
//  DS_2020_HW5_Sorting
//
//  Created by 顏浩昀 on 2021/1/1.
//

#include <iostream>

int Kth_largest(int [], int, int, int);
int P(int [], int, int);
void swap(int*, int*);
int QQ_merge(int [], int [], int, int);
int merge(int [], int [], int, int, int);



int main() {
    int n, op;
    int arr[1000001];
    while (std::cin>>n) {
        std::cin>>op;
        for(int i = 0; i < n; i++){
            std::cin>>arr[i];
        }
        if(op == 0){
            int tmp[n];
            int ans = QQ_merge(arr, tmp, 0, n-1);
            std::cout<<ans<<"\n";
        }else{
            int ans = Kth_largest(arr, 0, n-1, op);
            std::cout<<ans<<"\n";
        }
    }
    return 0;
}

int Kth_largest(int arr[], int l, int r, int k){
    //std::cout<<k<<" ";
    if(k > 0 && k <= r-l+1){
        int pos = P(arr, l, r);
        //std::cout<<pos<<"\n";
        if(pos-l == k-1)    return arr[pos];
        if (pos-l > k-1)    return Kth_largest(arr, l, pos-1, k);
        return Kth_largest(arr, pos+1, r, k-pos+l-1);
    }
    return -1;
}

int P(int arr[], int l, int r){
    int pivot = arr[r];
    int a = l;
    for(int i = l; i < r; i++){
        if(arr[i] > pivot){
            swap(&arr[a], &arr[i]);
            a++;
        }
    }
    swap(&arr[a], &arr[r]);
    return a;
}

void swap(int *a, int *b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int QQ_merge(int arr[], int tmp[], int l, int r){
    int mid = 0, pair = 0;
    if(r > l){
        mid = (l+r)/2;
        pair += QQ_merge(arr, tmp, l, mid);
        pair += QQ_merge(arr, tmp, mid+1, r);
        pair += merge(arr, tmp, l, mid+1, r);
    }
    return pair;
}

int merge(int arr[], int tmp[], int l, int mid, int r){
    int pair = 0;
    int i = l;
    int j = mid;
    int k = l;
    int a = l; // same as i
    int b = mid; // same as j
    while ((i < mid) && (j <= r)) {
        if(arr[i] > 2*arr[j]){
            pair = pair + (mid-i);
            j++;
        }else{
            i++;
        }
    }
    while ((a < mid) && (b <= r)) {
        if(arr[a] > arr[b]){
            tmp[k++] = arr[b++];
        }else{
            tmp[k++] = arr[a++];
        }
    }
    while (a<mid) {
        tmp[k++] = arr[a++];
    }
    while (b<=r) {
        tmp[k++] = arr[b++];
    }
    for(int c = l; c <= r; c++){
        arr[c] = tmp[c];
    }
    return pair;
}
