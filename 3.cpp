#include <iostream>
#include <vector>
#include <cmath>
#include <time.h>
#include <omp.h>
#include <chrono>
class Sequances {

public:

std::vector<double> seq_1;
std::vector<double> seq_2;

Sequances(std::vector<double> first_seq, std::vector<double> second_seq) {
    seq_1=first_seq;
    seq_2=second_seq;
}
 
~Sequances() {};


std::vector<double> Trig_func(){
std::vector<double> res;
//#pragma omp parallel for
for (long long unsigned int i = 0; i < seq_1.size(); ++i )
res[i]=[](double x, double y) {return sin(x)+cos(y);}(seq_1[i],seq_2[i]);
return res;
}

virtual void Result_print(){}

};


class str_print: public Sequances
{
public:

str_print(std::vector<double> ara1, std::vector<double> ara2): Sequances(ara1,ara2){}
std::vector<double> A = Trig_func();
void Result_print() {

for (long long unsigned int i = 0; i < seq_1.size(); ++i )
    {
    
    std::cout<<A[i]<<" ";
    }
}
};


class col_print: public Sequances
{
public:

col_print(std::vector<double> ara1, std::vector<double> ara2): Sequances(ara1,ara2){}
std::vector<double> B = Trig_func();
void Result_print() {
for (long long unsigned int i = 0; i < seq_1.size(); ++i )
std::cout<<B[i]<<"\n";
}
};

int main(void)
{  
  FILE * in;
  int n, i; 

  in = fopen("3.txt", "r");
  if (in == NULL)
  {
    printf("File open error");
    return 1;
  }

  if (fscanf(in, "%d", &n) != 1)
  {
    printf("File size error");
    fclose(in);
    return 1;
  }
  std::vector<double> arr1(n);
  std::vector<double> arr2(n);
  #ifdef Random
  for ( i = 0; i < 3; i++ )
  {
  arr1[i]=rand();
  arr2[i]=rand();
  }
  
  #else
  for ( i = 0; i < n; i++ )
  {
    
    if (fscanf(in, "%lf", &arr1[i]) != 1)
    {
      
      std::cout<<("Input data error");
      fclose(in);
      return 1;
    }
  }
  for ( i = 0; i < n; ++i )
  {
    if (fscanf(in, "%lf", &arr2[i]) != 1)
    {
      printf ("Input data error");
      fclose(in);
      return 1;
    }
  }
  #endif

#ifdef Str 
str_print str(arr1,arr2); 
auto start = std::chrono::steady_clock::now(); 
str.Result_print();
auto end = std::chrono::steady_clock::now();
std::chrono::duration<double> elapsed_seconds = end-start;
std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";

#else
col_print col(arr1,arr2);
auto start = std::chrono::steady_clock::now();   
col.Result_print();
auto end = std::chrono::steady_clock::now();
std::chrono::duration<double> elapsed_seconds = end-start;
std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";



#endif

fclose(in);
return 0;
}