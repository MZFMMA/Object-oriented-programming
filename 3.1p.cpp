#include <string>
#include <iostream>
#include <cmath>

class CPVector {

    friend class AngleQuater;

/*private:

    double x;
    double y;
*/
public:

   double x;
   double y;    

    CPVector() {
        x = 42;
        y = 42;
    }

    CPVector(double xArg, double yArg) {
        x = xArg;
        y = yArg;
    }

    ~CPVector() {};

    CPVector operator+(const CPVector& other) const {
        return CPVector(x + other.x, y + other.y);
    }

    CPVector operator-(const CPVector& other) const {
        return CPVector(x - other.x, y - other.y);
    }

    CPVector operator*(double lambda) const {
        return CPVector(x * lambda, y * lambda);
    }


    double AngleDegr() const {
        return atan(y / x) * 180 / M_PI;
    }
    double AngleRad() const {
        return atan(y / x);
    }


    int Quater() const {
        if (x > 0 && y > 0) return 1;
        else if (x < 0 && y>0) return 2;
        else if (x < 0 && y < 0) return 3;
        else if (x > 0 && y < 0) return 4;
        else return 0;
    }


    double Length() const {
        return sqrt(x * x + y * y);
    }

    double X() const { return x; }

    double Y() const { return y; }

};



class AngleQuater
{

public:

    double Angle(CPVector& vec1, CPVector& vec2) const {
        return acos((vec1.x * vec2.x + vec1.y * vec2.y) / (vec1.Length() * vec2.Length())) * 180 / M_PI;
    }
    std::string SameQuater(CPVector& vec1, CPVector& vec2) const {
        if (vec1.Quater() == vec2.Quater()) return "Yes!";
        else return "No!";
    }
};



class Complex : public CPVector {
public:

    double a;
    double b;

    Complex(double xArg, double yArg) {
        a = xArg;
        b = yArg;
    }

    ~Complex() {};

    Complex operator+(const Complex& other) const {
        return Complex(a + other.a, b + other.b);
    }

    double Length() const {
        return sqrt(a * a + b * b);
    }

    double A() const { return a; }

    double B() const { return b; }
};


int main() {
    double a, b, c, d;
    int fl;
    int gpk=0, i=0;
    FILE* f;
    
    std::string line;
    for (int i=0; i<3; i++)
    line+=std::to_string(i)+" ";
    std::cout<<line<<std::endl;

    f = fopen("3.1.txt", "r");
    double* array = (double*)malloc(1 * 2 * sizeof(double));
    if (f == NULL)
    {
        printf("File open error\n");
        f = stdin;
        gpk = 1;
        
    }
    if (gpk == 1) std::cout << "Enter number of the operation: ['1': length, '2': quater, '3': angle, '4': +, '5': -, '6': *] " << std::endl;
    while (fscanf(f, "%d", &fl) == 1) {
        if (fl <= 3)
        {
            char s = 'n';
            if (gpk == 1) {

                std::cout << "Create a new vector or use existing? [n/e] " << std::endl;
                int flwt = fl;
                if (fscanf(f, "%s", &s) != 1) { std::cout << "Data input error"; free(array), fclose(f); return -1; };
                fl = flwt;
                
            }
            if (s == 'n') {
                if (gpk == 1)std::cout << "Enter coords of the vector: " << std::endl;
                if (fscanf(f, "%lf", &a) != 1)
                {
                    std::cout << "Data input error"; free(array); fclose(f); return -1;
                }
                if (fscanf(f, "%lf", &b) != 1)
                {
                    std::cout << "Data input error"; free(array); fclose(f); return -1;


                }
                
            }

            else if (s == 'e') {
                int q, numb=0;
                std::cout << "Enter number of the vector [1/2/3....] " << std::endl;
                for (int zbl = 1; zbl < i+1; zbl++){
                numb++;
                std::cout << "Vec # " << numb << ": "<< array[zbl*2-2]<<" "<< array[zbl*2-1]<< std::endl;}
                if (fscanf(f, "%d", &q) != 1)
                {
                    std::cout << "Data input error"; free(array); fclose(f); return -1;
                }
                if ((q>i) or (q<1)){
                    std::cout << "Data input error"; free(array); fclose(f); return -1;}
                a = array[q * 2 - 2];
                b = array[q * 2 - 1];

            }
            else { std::cout << "Data input error"; free(array), fclose(f); return -1; };
            CPVector vec(a, b);
            
            if (fl == 1)
            {
       
                std::cout << "Length of the vector is " << vec.Length() << std::endl;
            }
            else if (fl == 2)
                std::cout << "Vector is in the quater # " << vec.Quater() << std::endl;
            else if (fl == 3)
                std::cout << "Angle between vector and OX in degrees is " << vec.AngleDegr() << std::endl;
        }
        else if ((fl == 4) or (fl == 5) or (fl == 6)) {
            char s = 'n';
            if (gpk == 1) {
                std::cout << "Create a new vector or use existing? [n/e] " << std::endl;
                if (fscanf(f, "%s", &s) != 1) { std::cout << "Data input error"; free(array), fclose(f); return -1; };
            }
            if (s == 'n') {
                if (gpk == 1)std::cout << "Enter coords of the first vector: " << std::endl;
                if (fscanf(f, "%lf", &a) != 1)
                {
                    std::cout << "Data input error"; free(array); fclose(f); return -1;
                }
                if (fscanf(f, "%lf", &b) != 1)
                {
                    std::cout << "Data input error"; free(array); fclose(f); return -1;

            
                }
                }
                else if (s == 'e') {
                int q, numb=0;
                std::cout << "Enter number of the vector [1/2/3....] " << std::endl;
                for (int zbl = 1; zbl < i+1; zbl++){
                numb++;
                std::cout << "Vec # " << numb << ": "<< array[zbl*2-2]<<" "<< array[zbl*2-1]<< std::endl;}
                if (fscanf(f, "%d", &q) != 1)
                {
                    std::cout << "Data input error"; free(array); fclose(f); return -1;
                }
                if ((q>i) or (q<1)){
                    std::cout << "Data input error"; free(array); fclose(f); return -1;}
                a = array[q * 2 - 2];
                b = array[q * 2 - 1];
                }
            else { std::cout << "Data input error"; free(array), fclose(f); return -1; };
            if (fl != 6) {
                s = 'n';
                if (gpk == 1) {
                    std::cout << "Create a new vector or use existing? [n/e] " << std::endl;
                    if (fscanf(f, "%s", &s) != 1) { std::cout << "Data input error"; free(array), fclose(f); return -1; };
                }
                if (s == 'n') {
                    if (gpk == 1)std::cout << "Enter coords of the second vector: " << std::endl;
                    if (fscanf(f, "%lf", &c) != 1)
                    {
                        std::cout << "Data input error"; free(array); fclose(f); return -1;
                    }

                    if (fscanf(f, "%lf", &d) != 1)
                    {
                        std::cout << "Data input error"; free(array); fclose(f); return -1;

                    }

                }


                else if (s == 'e') {
                int q, numb=0;
                std::cout << "Enter number of the vector [1/2/3....] " << std::endl;
                for (int zbl = 1; zbl < i+1; zbl++){
                numb++;
                std::cout << "Vec # " << numb << ": "<< array[zbl*2-2]<<" "<< array[zbl*2-1]<< std::endl;}
                if (fscanf(f, "%d", &q) != 1)
                {
                    std::cout << "Data input error"; free(array); fclose(f); return -1;
                }
                if ((q>i) or (q<1)){
                    std::cout << "Data input error"; free(array); fclose(f); return -1;}
                c = array[q * 2 - 2];
                d = array[q * 2 - 1];
                }
                else { std::cout << "Data input error"; free(array), fclose(f); return -1; };
            }
  
                CPVector vec(a, b);
                CPVector vecmore(c, d);
                CPVector vecresult;
                if (fl == 4) {
                    vecresult = vec + vecmore;
                    std::cout << "vecsum.x = " << vecresult.x
                        << " vecsum.y = " << vecresult.Y() << std::endl;
                }
                else if (fl == 5) {
                    vecresult = vec - vecmore;
                    std::cout << "vecsub.x = " << vecresult.X()
                        << " vecsub.y = " << vecresult.Y() << std::endl;
                }
                else if (fl == 6) {
                    if (gpk == 1) std::cout << "Enter lambda" << std::endl;
                    if (fscanf(f, "%lf", &c) != 1)
                    {
                        std::cout << "Data input errorX"; free(array); fclose(f); return -1;
                    }
                    vecresult = vec * c;
                    std::cout << "vecmul.x = " << vecresult.X()
                        << " vecmul.y = " << vecresult.Y() << std::endl;
                }
                if (gpk == 1) {
                    std::cout << "Do you want to save the result? [y/n]" << std::endl;
                    if (fscanf(f, "%s", &s) != 1) { std::cout << "Data input error"; free(array), fclose(f); return -1; };
                }
                if (s == 'y')
                {
                    i++;
                    array = (double*) realloc(array, i * 2 * sizeof(double));
                    if (array == NULL)
                    {
                        printf("File memory error");
                        free(array);
                        return 1;
                    }
                    array[i * 2 - 2] = vecresult.X();
                    array[i * 2 - 1] = vecresult.Y();
                    std::cout << "Vec # " << i << " successfully created" << std::endl;
                }

            }
     else { std::cout << "Data input error"; free(array); fclose(f); return -1; }
     if (gpk == 1)std::cout << "Enter number of the operation: ['1': length, '2': quater, '3': angle, '4': +, '5': -, '6': *] " << std::endl;
    }
    free(array);
    fclose(f);
    return 0;
}
