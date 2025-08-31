#ifndef HEAP_H
#define HEAP_H



#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <algorithm>

template<class t>
class Binaryheap{
    private:
        t*data{};
        int size{0};
        int capacity{0};
        bool Max{false};
        int leftidx(int pidx){
            int lc = 2*pidx+1;
            return (lc>= size ? -1 : lc);
        }
        int rightidx(int pidx){
            int rc = 2*pidx+2;
            return(rc>=size ? -1:rc);
        }
         int leftidx(int pidx,int sz){
            int lc = 2*pidx+1;
            return (lc>= sz ? -1 : lc);
        }
        int rightidx(int pidx,int sz){
            int rc = 2*pidx+2;
            return(rc>=sz ? -1:rc);
        }
        int parentidx(int idx){
            return (idx==0 ? -1:(idx-1)/2);
        }
        void heapify_up(int child){
            if(not Max){
                int parent = parentidx(child);
                if(child==0|| data[parent]<=data[child])
                return;
                swap(data[parent],data[child]);
                heapify_up(parent);
            }
            else{
                int parent = parentidx(child);
                if(child==0|| data[parent]>=data[child])
                return;
                swap(data[parent],data[child]);
                heapify_up(parent);

            }
        }
        void expand(){
            capacity*=3;
            t*data2=new t[capacity];
            for(int i=0;i<size;i++)
                data2[i]=data[i];
            swap(data,data2);
            delete [] data2;
        }
        void heapify_down(int parent){
            int child_=leftidx(parent);
            int right_=rightidx(parent);
            if(child_<0)
                return;
            if(!Max){
            if(right_!=-1&&data[right_]<data[child_])
                child_=right_;
            if(data[parent]>data[child_]){
                swap(data[parent],data[child_]);
                heapify_down(child_);
            }}
            else{
                if(right_!=-1&&data[right_]>data[child_])
                    child_=right_;
                 if(data[parent]<data[child_]){
                    swap(data[parent],data[child_]);
                    heapify_down(child_);

            }
        }
    }
         void heapify_down(int parent,t*arr,int sz,bool b ){
            int child_=leftidx(parent,sz);
            int right_=rightidx(parent,sz);
            if(child_<0)
                return;
            if(!b){
            if(right_!=-1&&arr[right_]<arr[child_])
                child_=right_;
            if(arr[parent]>arr[child_]){
                swap(arr[parent],arr[child_]);
                heapify_down(child_);
            }}
            else{
                if(right_!=-1&&arr[right_]>arr[child_])
                    child_=right_;
                 if(arr[parent]<arr[child_]){
                    swap(arr[parent],arr[child_]);
                    heapify_down(child_);

            }
        }
    }

    public :
        Binaryheap(int  len,bool maxx_ ):capacity(len*10),data(new t[capacity]),Max(maxx_){}
        Binaryheap(bool maxx_):Binaryheap(10,maxx_){}
        Binaryheap():Binaryheap(10,false){}
        Binaryheap(const initializer_list<t>& lst,bool b ):Max(b) {
            this->size = lst.size();
            this->capacity = max(10, (int)lst.size()*2);
            this->data = new t[capacity];
            auto it = lst.begin();
            for (int i = 0; i < this->size; i++, it++)
                data[i] = *it;
            this->heapify();
        }


        void heapify(){
            for(int i= size/2 -1;i>-1;i--)
                heapify_down(i);
        }
        void heapify(t*arr,int sz,bool b){
            for(int i= sz-1;i>=0;i--)
                heapify_down(i,arr,sz,b);
        }

        ~Binaryheap(){
            delete[] data;
            data=nullptr;
        }
        void insert(t x){
            if(size>=capacity)
                this->expand();
            int idx=size++;
            data[idx]=x;
            heapify_up(idx);
        }
        t pop() {
            if (isempty())
                throw runtime_error("Heap is empty");
            t root = data[0];
            data[0] = data[--size];
            heapify_down(0);
            return root;
}

        bool isempty()const{return size==0;}
        t top()const{return data[0];}
        t back()const{return data[size-1];}
        bool IsMax()const{return Max;}
        int len()const{return this->size;}
        void setMax(bool b){
            if(b!=this->Max)
                {Max=b;
                this->heapify();
            }
            return;
        }

        
        void heap_sort(t* arr, int sz, bool b) {
            // Step 1: Build heap
            heapify(arr, sz, b);

            // Step 2: Repeatedly extract max/min
            for (int i = sz - 1; i > 0; i--) {
                swap(arr[0], arr[i]);           
                heapify_down(0, arr, i, b);     
            }
        }
        t popBack(){
            return data[size--];
        }
        

        
};

#endif