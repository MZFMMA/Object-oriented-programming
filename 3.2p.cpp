#include <stdlib.h>
#include <iostream>
#include <cmath>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstring>

/*bool bad_side(int n, std::vector<double> coords);

bool point_loc_convex(std::vector<double> coords, double x, double y);

bool bad_side(int n, std::vector<double> coords){
int fl=1;
double x1,y1,x2,y2 = coords[2*n], coords[2*n+1], coords[(2*n+2)%coords.size()], coords[(2*n+3)%coord.size()];

for (long long unsigned int i=0; i<coords.size(); i=i+2){

if (((y2-y1)*coords[i]-(x2-x1)*coords[i+1]+y1(x2-x1)-x1(y2-y1))>0) {fl*=2;}
else if (((y2-y1)*coords[i]-(x2-x1)*coords[i+1]+y1(x2-x1)-x1(y2-y1))<0) {fl*=3;}
if ((fl%3==0) && (fl%2==0)) {return True;}}
return False;}

bool point_loc_convex(std::vector<double> coords, double x, double y){
int fl=0;
for (long long unsigned int i=0; i<coords.size(); i=i+2){     
    double x1,y1,x2,y2 = coords[i], coords[(i+1)], coords[(i+2)%coords.size()], coords[(i+3)%coord.size()];
    for (long long unsigned int j=0; j<coords.size(); j=i+2){
    if (((y2-y1)*coords[j]-(x2-x1)*coords[j+1]+y1(x2-x1)-x1(y2-y1))*((y2-y1)*x-(x2-x1)*y+y1(x2-x1)-x1(y2-y1)) < 0) {return -1;}
    else if (((y2-y1)*coords[j]-(x2-x1)*coords[j+1]+y1(x2-x1)-x1(y2-y1))*((y2-y1)*x-(x2-x1)*y+y1(x2-x1)-x1(y2-y1)) == 0) {fl+=1;}}}
if (fl==coords.size()) {return 0;}
return 1;}}*/



std::vector<double> sect_inter(double x1,double x2,double x3, double x4);    
std::vector<double> Intersect_c(std::vector<double> coords1,std::vector<double> coords2);
std::vector<double> Union_c(std::vector<double> coords1, std::vector<double> coords2);
int Point_loc(std::vector<double> coords, double p, double q);


std::vector<double> sect_inter(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4) {

    double A1 = y1 - y2, B1 = x2 - x1, C1 = -A1 * x1 - B1 * y1, A2 = y3 - y4, B2 = x4 - x3, C2 = -A2 * x3 - B2 * y3;
    int det = A1 * B2 - B1 * A2;

    if (det == 0) return {};
    else {
        double x = (C2 * B1 - C1 * B2) / det;
        double y = (A2 * C1 - A1 * C2) / det;
        if (((((x <= x2) && (x >= x1)) || ((x >= x2) && (x <= x1))) && (((y <= y2) && (y >= y1)) || ((y >= y2) && (y <= y1))))
            && ((((x <= x3) && (x >= x4)) || ((x >= x3) && (x <= x4))) && (((y <= y4) && (y >= y3)) || ((y >= y4) && (y <= y3)))))
        {
            if (fabs(y) < 5.96e-08) return { x,fabs(y) };
            return { x,y };
        }
        else return{};
    }
}



std::vector<double> Intersect_c(std::vector<double> coords1, std::vector<double> coords2) {
    std::vector <double> intersect;
    std::vector <double> inter;
    for (long long unsigned int i = 0; i < coords1.size(); i = i + 2) {
        if (Point_loc(coords2, coords1[i], coords1[i + 1]) > 0) { intersect.insert(intersect.begin() + intersect.size(), coords1[i]); intersect.insert(intersect.begin() + intersect.size(), coords1[i + 1]); }
        double x1 = coords1[i];
        double y1 = coords1[(i + 1)];
        double x2 = coords1[(i + 2) % (coords1.size())];
        double y2 = coords1[(i + 3) % (coords1.size())];
        for (long long unsigned int j = 0; j < coords2.size(); j = j + 2) {
            if (((Point_loc(coords1, coords2[j], coords2[j + 1])) > 0) && (i==0)) { intersect.insert(intersect.begin() + intersect.size(), coords2[j]); intersect.insert(intersect.begin() + intersect.size(), coords2[j + 1]); }
            double x3 = coords2[j];
            double y3 = coords2[(j + 1)];
            double x4 = coords2[(j + 2) % (coords2.size())];
            double y4 = coords2[(j + 3) % (coords2.size())];
            inter = sect_inter(x1, y1,x2, y2, x3, y3, x4, y4);
            
            if (inter.size() != 0) { intersect.insert(intersect.begin() + intersect.size(), inter[0]); intersect.insert(intersect.begin() + intersect.size(), inter[1]); }
        }
    }
    return intersect;
}

std::vector<double> Union_c(std::vector<double> coords1, std::vector<double> coords2) {
    std::vector <double> intersect = {};
    std::vector <double> inter = {};
    for (long long unsigned int i = 0; i < coords1.size(); i = i + 2) {
        if ((Point_loc(coords2, coords1[i], coords1[i + 1]) < 0)) { intersect.insert(intersect.begin() + intersect.size(), coords1[i]); intersect.insert(intersect.begin() + intersect.size(), coords1[i + 1]); }
        double x1 = coords1[i];
        double y1 = coords1[(i + 1)];
        double x2 = coords1[(i + 2) % (coords1.size())];
        double y2 = coords1[(i + 3) % (coords1.size())];
        for (long long unsigned int j = 0; j < coords2.size(); j = j + 2) {
            if (((Point_loc(coords1, coords2[j], coords2[j + 1]) < 0)) && (i==0)) { intersect.insert(intersect.begin() + intersect.size(), coords2[j]); intersect.insert(intersect.begin() + intersect.size(), coords2[j + 1]); }
           
            double x3 = coords2[j];
            double y3 = coords2[(j + 1)];
            double x4 = coords2[(j + 2) % (coords2.size())];
            double y4 = coords2[(j + 3) % (coords2.size())];
            
            inter = sect_inter(x1, y1, x2, y2, x3, y3, x4, y4);
            
            if (inter.size() != 0) { intersect.insert(intersect.begin() + intersect.size(), inter[0]); intersect.insert(intersect.begin() + intersect.size(), inter[1]); }
        }
    }
    return intersect;
}


int Point_loc(std::vector<double> coords, double p, double q){

int counter=0;
for (long long unsigned int i=0; i<coords.size(); i=i+2){     
    double x1 = coords[i];
    double y1 = coords[(i + 1)];
    double x2 = coords[(i + 2) % (coords.size())];
    double y2 = coords[(i + 3) % (coords.size())];
    double x3 = p;
    double y3 = q;
    double x4 = -241 + p + q * 0.241;
    double y4 = 1000;
    double A1 = y1 - y2, B1 = x2 - x1, C1 = -A1 * x1 - B1 * y1, A2 = y3 - y4, B2 = x4 - x3, C2 = -A2 * x3 - B2 * y3;
    int det = A1 * B2 - B1 * A2;
    double y = (A2 * C1 - A1 * C2) / det;
    if ((((x1 + y1 * 0.241 - p - q * 0.241) * (x2 + y2 * 0.241 - p - q * 0.241)) <= 0) && (y > q)) {  counter += 1; }
    else if ((fabs((y2-y1)*p-(x2-x1)*q+y1*(x2-x1)-x1*(y2-y1)) < 5.96e-08) && (((p>=x1 && p<=x2) || (p>=x2 && p<=x1)) && ((q>=y1 && q<=y2) || (q>=y2 && q<=x1))))
    return 0;} 
if (counter % 2 != 0) return 1;
return -1;}    
   
class Polyarea {

private:


std::vector<std::vector<double>> area_c;

public:

Polyarea(std::vector<std::vector<double>> area_coords){
area_c=area_coords;}

Polyarea() {

area_c = {};}

std::vector<std::vector<double>> coords() { return area_c; };

~Polyarea() {};

void Add_point(int comp_sv,double x, double y){
    area_c[comp_sv].insert((area_c[comp_sv]).begin() + (area_c[comp_sv]).size(), x);
area_c[comp_sv].insert((area_c[comp_sv]).begin()+(area_c[comp_sv]).size(), y);}

void Delete_point(int comp_sv, int n){
area_c[comp_sv].erase((area_c[comp_sv]).begin()+2*n, (area_c[comp_sv]).begin()+2*n+2);}

int Point_location(double x, double y){
for (long long unsigned int i = 0; i < area_c.size(); i++) {
if (Point_loc(area_c[i], x, y) == 0) {return 0;}
else if (Point_loc(area_c[i], x, y) == 1) {return 1;}}
return -1;}

Polyarea Intersect (Polyarea area1){
Polyarea area3;
std::vector<double> Intgh;
for (long long unsigned int i=0; i<(area_c.size()); i++){
    for (long long unsigned int j=0; j<((area1.area_c).size()); j++){
        Intgh=Intersect_c(area_c[i],(area1.area_c)[j]);
        if (Intgh.size() != 0) (area3.area_c).insert((area3.area_c).begin() + (area3.area_c).size(), Intgh); } }
return area3;}

Polyarea Union(Polyarea area1) {

    Polyarea area3;
    std::vector<double> Intgh = {};
    int yoyo = 0;
    for (long long unsigned int i = 0; i < (area_c.size()); i++) {
        for (long long unsigned int j = 0; j < ((area1.area_c).size()); j++) {
            if ((Intersect_c(area_c[i], area1.area_c[j])).size() != 0) {
                yoyo++;
            }
        }
    }

    if (yoyo == 0) {
        for (long long unsigned int i = 0; i < (area_c.size()); i++) {
            (area3.area_c).insert((area3.area_c).begin() + (area3.area_c).size(), area_c[i]);
        }
        for (long long unsigned int j = 0; j < ((area1.area_c).size()); j++) {
            (area3.area_c).insert((area3.area_c).begin() + (area3.area_c).size(), area1.area_c[j]);
        }
        return area3;
    }
     {
        for (long long unsigned int i = 0; i < (area_c.size()); i++) {
            for (long long unsigned int j = 0; j < ((area1.area_c).size()); j++) {
                if ((Intersect_c(area_c[i], area1.area_c[j])).size() != 0) {
                    Intgh = Union_c(area_c[i], area1.area_c[j]);
                    if (Intgh.size() != 0) (area3.area_c).insert((area3.area_c).begin() + (area3.area_c).size(), Intgh);
                }
            }
        }
        return area3;
    }
}


void Ch_coord(int comp_sv,int n, double x, double y){
area_c[comp_sv][2*n] = x;
area_c[comp_sv][2*n+1] = y;}

int Numb_compsv(){
return area_c.size();}
int Numb_verc(){
    int counter = 0;
    for (long long unsigned int i = 0; i < area_c.size(); i++) {
        counter += (area_c[i].size()) / 2;
        }
    return counter;}

};




int main()
{
    int a, b, fl, gpk = 0;

    double x, y, z, n;
    std::vector<std::vector<double>> areayyy;

    FILE* f;
    f = fopen("3.2.txt", "r");
    if (f == NULL)
    {
        printf("File open error\n");
        f = stdin;
        gpk = 1;
    }
    if (gpk == 1) std::cout << "Enter number of the operation: ['1': Point location, '2': Amount of vercities and connectivity components, '3': Delete vercity, '4': Add point, '5': Change coordinat, '6': Intersection, '7': Union] " << std::endl;
    while (fscanf(f,"%d", &fl) == 1) {
        

        if (fl<=5)
        {
            if (gpk == 1) std::cout << "Enter number of connectivity components" << std::endl;
            if (fscanf(f, "%d", &a) != 1) { std::cout << "Data input error"; fclose(f); return -1; };
            int numb_con_com = a;

            for (int i = 0; i < a; ++i)
            {
                if (gpk == 1) std::cout << "Enter number of vercities in the component # "<< i << std::endl;
                if (fscanf(f, "%d", &b) != 1) { std::cout << "Data input error"; fclose(f); return -1; };
                if (gpk == 1) std::cout << "Enter component" << std::endl;
                std::vector<double> array(2 * b);
                for (int t = 0; t < 2 * b; t++) {

                    if (fscanf(f, "%le", &array[t]) != 1) {
                        printf("Data type error");
                        fclose(f);
                        return 1;
                    }

                }

                areayyy.insert((areayyy).begin() + (areayyy).size(), array);
                array.clear();


            }
            Polyarea areaxxx(areayyy);
            if (fl==1) {

                //Pointlocation
                if (gpk == 1) std::cout << "Enter coords of the point" << std::endl;
                if (fscanf(f, "%lf", &x) != 1) { std::cout << "Data input error"; fclose(f); return -1; };
                if (fscanf(f, "%lf", &y) != 1) { std::cout << "Data input error"; fclose(f); return -1; };

                std::cout << "Location of the point (1 - inside, 0 - boarder, -1 - outside): { " << areaxxx.Point_location(x, y) << " }" << std::endl;
                std::cout << std::endl;
            }
            else if (fl==2) {
                //amount
                 std::cout << "Amount of connectivity components is " << areaxxx.Numb_compsv() << std::endl;
                 std::cout << "Amount of verticies is " << areaxxx.Numb_verc() << std::endl;
                std::cout << std::endl;
            }
            else if (fl == 3) {
                //delete vercity
                if (gpk == 1) std::cout << "Enter number of the component" << std::endl;
                if (fscanf(f, "%lf", &x) != 1) { std::cout << "Data input error"; fclose(f); return -1; };
                if (x >= numb_con_com) { std::cout << "Data input error"; fclose(f); return -1; };
                if (gpk == 1) std::cout << "Enter number of the vercity" << std::endl;
                if (fscanf(f, "%lf", &y) != 1) { std::cout << "Data input error"; fclose(f); return -1; };
                int nv = areaxxx.coords()[x].size();
                if (y >= nv) { std::cout << "Data input error"; fclose(f); return -1; };
                areaxxx.Delete_point(x, y);
                std::cout << "Vercity # " << y << " was successfully deleted from the component # " << x << std::endl;
                for (long long unsigned int i = 0; i < (areaxxx.coords()).size(); i++)
                {
                    if (i != 0) std::cout << std::endl;
                    for (long long unsigned int j = 0; j < (areaxxx.coords()[i]).size(); j = j + 2)
                    {
                        std::cout << "{" << (areaxxx.coords())[i][j] << " " << (areaxxx.coords())[i][j + 1] << "} ";

                    }
                }
                std::cout << std::endl;
                std::cout << std::endl;
            }
            else if (fl==4) {
                //add point
                if (gpk == 1) std::cout << "Enter number of the component" << std::endl;
                if (fscanf(f, "%lf", &z) != 1) { std::cout << "Data input error"; fclose(f); return -1; };
                if (z >= numb_con_com) { std::cout << "Data input error"; fclose(f); return -1; };
                if (gpk == 1) std::cout << "Enter coords of the point" << std::endl;
                if (fscanf(f, "%lf", &x) != 1) { std::cout << "Data input error"; fclose(f); return -1; };
                if (fscanf(f, "%lf", &y) != 1) { std::cout << "Data input error"; fclose(f); return -1; };

                areaxxx.Add_point(z, x, y);
                std::cout << "Vercity was successfully added to the component # " << z << std::endl;
                for (long long unsigned int i = 0; i < (areaxxx.coords()).size(); i++)
                {
                    if (i != 0) std::cout << std::endl;
                    for (long long unsigned int j = 0; j < (areaxxx.coords()[i]).size(); j = j + 2)
                    {
                        std::cout << "{" << (areaxxx.coords())[i][j] << " " << (areaxxx.coords())[i][j + 1] << "} ";

                    }
                }
                std::cout << std::endl;
                std::cout << std::endl;
            }
            else if (fl==5) {
                //change coordinat
                if (gpk == 1)std::cout << "Enter number of the component" << std::endl;
                if (fscanf(f, "%lf", &z) != 1) { std::cout << "Data input error"; fclose(f); return -1; };
                if (z >= numb_con_com) { std::cout << "Data input error"; fclose(f); return -1; };
                if (gpk == 1)std::cout << "Enter number of the vercity" << std::endl;
                if (fscanf(f, "%lf", &n) != 1) { std::cout << "Data input error"; fclose(f); return -1; };
                int nv = areaxxx.coords()[z].size();
                if (n >= nv) { std::cout << "Data input error"; fclose(f); return -1; };
                if (gpk == 1)std::cout << "Enter coords of the point" << std::endl;
                if (fscanf(f, "%lf", &x) != 1) { std::cout << "Data input error"; fclose(f); return -1; };
                if (fscanf(f, "%lf", &y) != 1) { std::cout << "Data input error"; fclose(f); return -1; };
                areaxxx.Ch_coord(z, n, x, y);
                std::cout << "Vercity was successfully changed " << std::endl;
                for (long long unsigned int i = 0; i < (areaxxx.coords()).size(); i++)
                {
                    if (i != 0) std::cout << std::endl;
                    for (long long unsigned int j = 0; j < (areaxxx.coords()[i]).size(); j = j + 2)
                    {
                        std::cout << "{" << (areaxxx.coords())[i][j] << " " << (areaxxx.coords())[i][j + 1] << "} ";
                    }
                }
            }

            areayyy.clear();
            std::cout << std::endl;
        }


        else if ((fl==6) or (fl==7)) {
        if (gpk == 1) std::cout << "Enter number of connectivity components in the first area" << std::endl;
        if (fscanf(f, "%d", &a) != 1) { std::cout << "Data input error"; fclose(f); return -1; }
            for (int i = 0; i < a; ++i)
            {
                if (gpk == 1) std::cout << "Enter number of vercities in the component # " << i << std::endl;
                if (fscanf(f, "%d", &b) != 1) { std::cout << "Data input error"; fclose(f); return -1; };
                if (gpk == 1)std::cout << "Enter component" << std::endl;
                std::vector<double> array(2 * b);
                for (int t = 0; t < 2 * b; t++) {

                    if (fscanf(f, "%le", &array[t]) != 1) {
                        printf("Data type error");
                        fclose(f);
                        return 1;
                    }

                }

                areayyy.insert((areayyy).begin() + (areayyy).size(), array);
                array.clear();


            }
            Polyarea area1(areayyy);
            areayyy.clear();
            if (gpk == 1) std::cout << "Enter number of connectivity components in the second area" << std::endl;
            if (fscanf(f, "%d", &a) != 1) { std::cout << "Data input error"; fclose(f); return -1; }

            for (int i = 0; i < a; ++i)
            {
                if (gpk == 1) std::cout << "Enter number of vercities in the component # " << i << std::endl;
                if (fscanf(f, "%d", &b) != 1) { std::cout << "Data input error"; fclose(f); return -1; };
                std::vector<double> array(2 * b);
                if (gpk == 1)std::cout << "Enter component" << std::endl;
                for (int t = 0; t < 2 * b; t++) {

                    if (fscanf(f, "%le", &array[t]) != 1) {
                        printf("Data type error");
                        fclose(f);
                        return 1;
                    }

                }

                areayyy.insert((areayyy).begin() + (areayyy).size(), array);
                array.clear();


            }

            Polyarea area2(areayyy);
            areayyy.clear();
            std::cout << std::endl;
            if (fl==6) {
                std::cout << std::endl;
                Polyarea areaintersecteria = area1.Intersect(area2);
                std::cout << "Intersection:";
                for (long long unsigned int i = 0;i < (areaintersecteria.coords()).size(); i++)
                {
                    std::cout << std::endl;
                    for (long long unsigned int j = 0; j < (areaintersecteria.coords()[i]).size(); j = j + 2)
                    {
                        std::cout << "{" << (areaintersecteria.coords())[i][j] << " " << (areaintersecteria.coords())[i][j + 1] << "} ";
                    }
                }
                std::cout << std::endl;
                std::cout << std::endl;
            }
            else if (fl==7) {
                Polyarea areaunioneria = area1.Union(area2);
                std::cout << "Union:";
                for (long long unsigned int i = 0; i < (areaunioneria.coords()).size(); i++)
                {
                    std::cout << std::endl;
                    for (long long unsigned int j = 0; j < (areaunioneria.coords()[i]).size(); j = j + 2)
                    {
                        std::cout << "{" << (areaunioneria.coords())[i][j] << " " << (areaunioneria.coords())[i][j + 1] << "} ";
                    }
                    
                }
                std::cout << std::endl;
                std::cout << std::endl;
            }



        }
        else { std::cout << "Data input error"; fclose(f); return -1; }
        if (gpk == 1) std::cout << "Enter number of the operation: ['1': Point location, '2': Amount of vercities and connectivity components, '3': Delete vercity, '4': Add point, '5': Change coordinat, '6': Intersection, '7': Union] " << std::endl;
    }
    fclose(f);
    return 0;
}