#ifndef VECTOR_H
#define VECTOR_H

#include<iostream>
#include<string>
#include<vector>
#include <thread>
#include<algorithm>

using namespace std;

template<class t>
class Vector{

    private:
    t*ptr=nullptr;
    int size{0};
    int capacity;
    void expand( void ){
        size*=2;
        t*ptr2=new t[size];
        for(int i=0;i<size/2;i++){
            ptr2[i]=ptr[i];
        }
        swap(ptr,ptr2);
        delete[]ptr2;
    }
    public:
    Vector(): Vector(10){}
    Vector(int x):size(x){
        capacity=size*10;
        ptr=new t[capacity];
    }
    Vector(const Vector<t>& x){
        this->ptr=new t[x.getsize()*10];
        this->size=x.getsize();
        this->capacity=x.getsize()*10;
        for(int i=0;i<x.getsize();i++){
            this->ptr[i]=x.get(i);

        }

    }
   Vector(initializer_list<t> x) {
    this->size = 0;
    this->capacity = 100;
    this->ptr = new t[capacity];
    for (const auto& c : x) this->append(c);
}

    ~Vector() {
		delete[] ptr;
		ptr = nullptr;
	}
    int getsize() const{
        return this->size;
    }
    auto get(int indx)const {
        if(indx>=0&&indx<size) return ptr[indx];
        else{
            throw out_of_range("Index out of range"); 
        } 
    }
    void set(int indx,t x){
    if(indx>=0&&indx<size) {
        if (typeid(x) == typeid(t)) ptr[indx] = x;
        else 
        throw new_handler("Mismatch datatype");
    }
    else 
    throw out_of_range("Index out of range");} 
    void print() const {
		for (int i = 0; i < size; ++i)
			cout << ptr[i] << " ";
		cout << "\n";
	}

	int find(t value) const  {
		for (int i = 0; i < size; ++i)
			if (ptr[i] == value)
				return i;
		return -1; // -1 for NOT found
	}
    void append(t x){
        if(size==capacity)
            this->expand();
        ptr[size++]=x;

        

    }
    void insert(int index,t x){
        if(index >= this->size)
    throw out_of_range("Index out of range");
    if(this->size==this->capacity) this->expand();

        for(int i=size++;i>=index;i--){
            ptr[i]=ptr[i-1];
            
        }
        ptr[index]=x;
    

    }
    const std::type_info& getid() const {
    return typeid(get(0));
}
    auto operator [](int index)const {
        if(index>=0&&index<size) return &ptr[index];
        else{
            throw out_of_range("Index out of range"); 
        } 
    }
    auto operator =(const Vector<t>&x)=delete;
    void rrotate(int n=1){
        if(n>0){
        auto x=this->get((this->size)-1);
        for(int i=this->getsize()-1;i>0;i--){
            this->ptr[i]=this->ptr[i-1];
        }
         ptr[0]=x;
         return rrotate(--n);
    }
    else return;

    }
    void lrotate(int n=1){
        if(n>0){
        auto x=this->get(0);
        for(int i=0;i<this->getsize();i++){
            this->ptr[i]=this->ptr[i+1];
        }
        this->set(this->getsize()-1,x);
         return lrotate(--n);}
         else return;
         
    }
    auto pop(int indx ){
        if(indx>=size||indx<0) 
        throw out_of_range("Index out of range"); 
        auto x=ptr[indx];
        for(int i=indx;i<size;i++){
            ptr[i]=ptr[i+1];
        }
        ptr[size-1]=t();
        size--;
        return x;

    }
    void Sorted(){
        vector<t>v(this->size);
        for(int i=0;i<v.size();i++){
            v[i]=this->ptr[i];
        }
        sort(v.begin(),v.end());
        for(int i=0;i<v.size();i++){
            this->ptr[i]=v[i];
        }

    }

    
};
#endif
