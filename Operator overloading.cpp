#include<iostream>
using namespace std;
class Complex{
public:
int real;
int img;
Complex(){
    real=0;
    img=0;
}
Complex(int real,int img){
    this->real=real;
    this->img=img;
}
friend Complex operator+(Complex x,Complex y);
friend ostream & operator<<(ostream &out,Complex c);
friend  Complex & operator++(Complex &y);
friend Complex operator++(Complex &c,int );

};
Complex operator+(Complex x,Complex y){
    Complex temp;
    temp.real=x.real+ y.real;
    temp.img=x.img+y.img;
    return temp;
}
ostream & operator<<(ostream &out,Complex c){
    out<<c.real<<"+i"<<c.img;
    return out;

}
  Complex & operator++(Complex &y){//pre increment
    ++y.real;
    ++y.img;
    return y;   
  }  
   Complex operator++(Complex &c,int){//post increment
    Complex temp=c;
   
    c.real++;
    c.img++;
    return temp;
  } 
  
int main(){
    Complex c1={10,30},c2(5,24),c3,c4;
    c3=c1+c2;
    cout<<c3<<endl;
    ++c3;
     cout<<c3<<endl;
     c4=c3++;
     cout<<c4<<endl<<c3;
    
    return 0;
}







    