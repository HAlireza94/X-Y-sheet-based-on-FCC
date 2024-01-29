#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>


using namespace std;
struct unitCell {

    double x;
    double y;
    double z;
};
int main(){

    vector<unitCell> vec;
    ifstream input("/Users/alirezahosseini/CLionProjects/FCC/cmake-build-debug/unit-cell");

    if (!input){
        cerr << " Failed to open file " << endl;
        return 1;
    }

    string line;

    while (getline(input,line)){

        stringstream ss(line);
        string xStr, yStr, zStr, atomNames;
        getline(ss,xStr,'\t');
        getline(ss,yStr,'\t');
        getline(ss,zStr,'\t');

        unitCell data;
        try {
            data.x = stod(xStr);
            data.y = stod(yStr);
            data.z = stod(zStr);
        } catch (const invalid_argument& ia){
            cerr << " Invalid argument " << ia.what() << '\n';
            continue;
        }

        vec.push_back(data);

    }

    vector <double> xl;
    vector <double> yl;
    vector <double> zl;
    for (const unitCell& cell : vec){
        xl.push_back(cell.x);
        yl.push_back(cell.y);
        zl.push_back(cell.z);
    }


    cout << "Unit Cell Length [A] = " << endl;
    short a;
    cin >> a;

    cout << "Nx = " << endl;
    short nx;
    cin >> nx;

    cout << "Ny = " << endl;
    short ny;
    cin >> ny;

    vector <double> x1(xl.size());
    vector <double> y1(yl.size());
    vector <double> z1(zl.size());

    for (int i = 0; i < xl.size(); i++){
        x1[i] = (xl[i]*a);
        y1[i] = (yl[i]*a);
        z1[i] = (zl[i]*a);
    }

    char atomName = 'X';

    ofstream output("FCC.xyz");
    int totalnumberAtoms = nx * ny* 9;
    output << to_string(totalnumberAtoms) <<'\n';
    output << "3D" << '\n';

    vector <double> X;
    vector <double> Y;
    vector <double> Z;
    for (int i = 0; i < nx; i++){
        for (int j = 0; j < ny; j++){
            for (size_t k = 0; k < x1.size(); k++){

                if (z1[k] == 0 || z1[k] == 0.5 * a) {
                    X.push_back(x1[k] + i);
                    Y.push_back(y1[k] + j);
                    Z.push_back(z1[k]);

                }
            }
        }
    }


    float z = 0;

    for (size_t i = 0; i < X.size(); i++){
//        cout << fixed << setprecision(1) << X[0];
//        cout << "\n\n";
        output << atomName << "      " << fixed << setprecision(1) << X[i] << "      " << fixed << setprecision(1) << Y[i] << "      " << fixed << setprecision(1) << z << '\n';
    }




    output.close();

    return 0;
}