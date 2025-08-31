#ifndef STACK_H
#define STACK_H



#include "Linked__List.hpp"
#include "Vector.hpp"
#include "Queue.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <algorithm>
#include <map>

using namespace std;

template<class t>
class StackArr{
    private:
        t*data{};
        int size{0};
        int topindx{0};
    public:
        StackArr():StackArr(10){}
        StackArr(int x):size(x){
            data=new t[size];
        }
        ~StackArr(){
            delete []data;
            data=nullptr;
        }
        void push(t x){
            if(isav())
                data[topindx++]=x;
            else    throw overflow_error("Stack is full !");

        }
        t pop(){
            if(not isemt()){
                return data[--topindx];

            }
             else    throw underflow_error("Stack is empty !");
        }
        t peek() const {
            if (!isemt())
                return data[topindx - 1];
            else
                throw underflow_error("Stack is empty!");
}
        bool isemt() const {
             return topindx == 0;
    }

         bool isav() const {
            return topindx < size;
    }
        bool isfull()const{
            return topindx>=size;
        }
        int getcap()const{
            return size;
        }
        void pushback(t x){
            if(isav()){
                t*data2=new t[size++];
                data2[0]=x;
                for(int i=1;i<=topindx;i++){
                    data2[i]=data[i-1];
                }
            swap(data,data2);
            delete []data2;
            data2=nullptr;
            topindx++;

            return;

            }
            throw overflow_error("Stack is full");


        }
        void reversest(){
            if(not this->isemt()){
            StackArr<t>tmp(size);
            while (not this->isemt())
            {
                tmp.push(this->pop());
            }
            while (not tmp.isemt())
            {
                this->push(tmp.pop());
                
            }
        }
        else
            throw underflow_error("stack is empty");
            
            
        }

//


};


template<class t>
class StackLI{
    private:
        DoubleLinkedList<t>data;
        int size{0};
        bool dynamic{false};
    public:
        StackLI():StackLI(10){}
        StackLI(int x,bool b= false): size(x) , dynamic(b){}
        void push(t x){
            if(dynamic || isav()){
                data.insert_end(x);
                if(dynamic && data.getlen()==this->size) size*=2;
            }
            else
                throw overflow_error("stack is full !");
        }
        t pop(){
            if(not isemt()){
                auto x =data.getfrb(0);
                data.edel();
                return x;
                }
            else
                throw underflow_error("stack is empty !");

            
        }
        t peek()const{

            if(not isemt())
                return data.getfrb(0);
            else
                throw underflow_error("stack is empty !");
        }
        bool isemt()const{
            return data.getlen()==0;
                }
        bool isav()const{
                return dynamic || data.getlen()<this->size;
        }
        bool isfull()const{
            return !dynamic&&data.getlen()>=this->size;
        }
        int getNoelem()const{
            return data.getlen();
        }
        int getcap()const{
            return size;
        }
        void setDynami(bool b){
            dynamic=b;
        }
        bool IsDynamic()const{
            return dynamic;
        }
        void addfront(t x){
            if(isav()){
                data.finsert(x);
                if(dynamic && data.getlen() == size)
                    size *= 2;
            }
            else{
                throw overflow_error("Stack is full and not dynamic");
            }
        }
        void reversest(){
            if(not this->isemt()){
            StackLI<t>tmp(size,true);
            while (not this->isemt())
            {
                tmp.push(this->pop());
            }
            while (not tmp.isemt())
            {
                this->push(tmp.pop());
                
            }
        }
        else
            throw underflow_error("stack is empty");
            
            
        }

};


string reversestr(string & s){
    StackLI<char>st(s.size(),true);
    for(const char &c :s)st.push(c); 
    string ans="";
    while(not st.isemt())
    ans+=st.pop();
    return ans;
}

void f1(string & s){
    string ans="";
    int x=0;
    for (int i = 0; i <= s.size(); ++i) {       
    if (i == s.size() || s[i] == ' ') {       
        string word = s.substr(x, i - x);    
        ans += reversestr(word);
        if (i != s.size()) ans += ' ';        
        x = i + 1;                             
    }
}
    s=ans;


}

int reversenum(int x){
    string s=to_string(x);
    s=reversestr(s);
    return stoi(s);
}

bool isvalid(const string& s) {
    StackArr<char> st(s.size());

    for (char c : s) {
      
        if (c == '(' || c == '[' || c == '{') {
            st.push(c);
        } else if(c == ')'||c == ']'||c == '}') {
            if (st.isemt()) return false;
            char top = st.pop();
            if ((c == ')' && top != '(') ||
                (c == ']' && top != '[') ||
                (c == '}' && top != '{'))
                return false;
        }
    }

    return st.isemt();
}


StackLI<int> nxtgret(const vector<int>&v){
    StackLI<int>st(v.size(),true);
    for(int i=0;i<v.size();i++){
        bool notf=true;
    for(int j=i;j<v.size();j++){
        if(v[j]>v[i]){
            notf=false;
            st.addfront(v[j]);
            break;
        }
        

    }   
    if(notf){
        st.addfront(-1);
    } 

    }  
    return st;  
}

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

string infx2pfx(const string& s) {
    string result = "";
    StackLI<char> st(s.size(), true);

    for (char c : s) {
        if (isdigit(c)) {
            result += c;
        } else { 
            while (!st.isemt() && precedence(c) <= precedence(st.peek())) {
                result += st.pop();
            }
            st.push(c);
        }
    }

    
    while (!st.isemt()) {
        result += st.pop();
    }

    return result;
}

#endif