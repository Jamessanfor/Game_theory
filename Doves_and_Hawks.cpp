
#include <Python.h>
#include <Windows.h>
#include <iostream>
#include <random>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <vector>



using namespace std;
default_random_engine gen;
uniform_real_distribution<double> dist(0, 1);
uniform_int_distribution<int> dist1(0, 100000);
const double T = 1.0; // the value of the resource
const double C = 1; // the cost of fighting


class Doves {
public:
    vector<int> DVS;

    Doves() {
        DVS.push_back(1);
        DVS.push_back(1);
        DVS.push_back(1);
        DVS.push_back(1);
        DVS.push_back(1);
        DVS.push_back(1);

    }
    void remove() {
        DVS.pop_back();

    }

};

class Hawks {
public:
    vector<vector<int>> HWK;
    vector<int> temp;
    Hawks() {
        temp.push_back(1);
        temp.push_back(0);
        HWK.push_back(temp);
        temp.clear();
    }
    void addnew(int wins) {
        temp.push_back(1);
        temp.push_back(wins);
        HWK.push_back(temp);
        temp.clear();

    }
    void shuffle() {
        for (int i = 0; i < HWK.size(); i++) {
            swap(HWK[i], HWK[dist1(gen) % HWK.size()]);
        }
    }
    void remove(int index) {
        if (HWK.size()) {
            swap(HWK[index], HWK[HWK.size() - 1]);
            HWK.pop_back();

        }
    }

};



void sim_interation_part1(int& ds, int& hs, int food) {
    int tempdoves_size = ds;
    int temphawks_size = hs;
    int count = 0;
    int flag = 0;
    double DVD = (double)((tempdoves_size) / (food) * (tempdoves_size) / (food));

    double HVD = (double)(((temphawks_size) / (food)) * (tempdoves_size) / (food));

    double HVH = (temphawks_size > 2) ? (double)((temphawks_size / food) * (temphawks_size / food)) : 0;


    for (int i = 0; i < tempdoves_size; i++) {
        HVD = (double)(((temphawks_size - count) / food) * (tempdoves_size - i) / (food));

        DVD = (double)((tempdoves_size - i) / (food) * (tempdoves_size - i) / (food));

        if (dist(gen) < HVD && hs && ds) {
            if (dist(gen) > 0.5) ds--;
            if (dist(gen) > 0.5) hs++;
            count++;
        }
        else if (dist(gen) < DVD) {
            i++;
        }
        else {
            ds++;
        }
        //        food--;
    }

    if (count < temphawks_size) {

        for (int i = 0; i < temphawks_size - count; i++) {
            HVH = ((temphawks_size - count - i) > 2) ? (double)((((temphawks_size - count - i) / food) * ((temphawks_size - count - i) / food))) : 0;

            if (dist(gen) < HVH) {
                hs -= 2;
                i++;
            }
            else {
                hs++;
            }
            if (food - 1)
                food--;
        }

    }



};






void Part1_sim() {
    ofstream myfile;
    myfile.open("Doves_Hawks1.csv");
    int DAYS = 1000;
    int food = 100;
    Doves D = Doves();
    Hawks H = Hawks();
    int dove_size = D.DVS.size();
    int hawk_size = H.HWK.size();

    for (int i = 0; i < DAYS; i++) {
        sim_interation_part1(dove_size, hawk_size, food);
        while (dove_size != D.DVS.size()) {
            //         cout << dove_size<< endl;
            if (dove_size > D.DVS.size())D.DVS.push_back(1);
            else if (dove_size < D.DVS.size())D.DVS.pop_back();
        }
        while (hawk_size != H.HWK.size()) {
            //            cout<<hawk_size<<endl;
            vector<int>temp = { 1,0 };
            if (hawk_size > H.HWK.size())H.HWK.push_back(temp);
            else if (hawk_size < H.HWK.size())H.HWK.pop_back();
        }

        myfile << dove_size << "," << hawk_size << "\n";
    }
    //cout << " Hawks: " << hawk_size << " Doves: " << dove_size << endl;
    myfile.close();

};




void sim_interation_part2(Doves& D, Hawks& H, int& ds, int& hs, int food) {



    vector<int> remove_index;
    int tempdoves_size = ds;
    int temphawks_size = hs;
    int count = 0;

    int flag = 0;

    double DVD = (double)((tempdoves_size) / (food) * (tempdoves_size) / (food));

    double HVD = (double)(((temphawks_size) / (food)) * (tempdoves_size) / (food));

    double HVH = (temphawks_size > 2) ? (double)((temphawks_size / food) * (temphawks_size / food)) : 0;


    for (int i = 0; i < tempdoves_size; i++) {
        HVD = (double)(((temphawks_size - count) / food) * (tempdoves_size - i) / (food));

        DVD = (double)((tempdoves_size - i) / (food) * (tempdoves_size - i) / (food));



        if (dist(gen) < HVD && (count < temphawks_size)) {
            if (dist(gen) > 0.5) ds--;
            if (dist(gen) > 0.5) hs++;
            H.HWK[count][1]++;//count wins
            count++;
            //cout<<"1" << endl;
        }
        else if (dist(gen) < DVD) {
            i++;
        }
        else if (dist(gen) < 0.0001) {//bunch of doves split
            int temp0 = (dist1(gen) % (tempdoves_size - i));
            for (int j = 0; j < temp0; j++) {
                if (dist(gen) > (double)(2 / temp0)) {
                    ds--;
                }


            }
            i += temp0;

        }
        else if (dist(gen) < 0.0001 && (count < temphawks_size)) {//bunch of doves split and hawks
            int temp0 = (dist1(gen) % ((tempdoves_size - i)));
            for (int j = 0; j < (temp0 - 1); j++) {
                if (dist(gen) > (double)(1 / (temp0 - 1))) {
                    ds--;
                }

            }
            H.HWK[count][1]++;//count wins;
            count++;
            i += (temp0 - 1);

        }
        else {
            ds++;
        }
    }
    if (count < temphawks_size) {
        for (int i = 1; i < (temphawks_size - count); i++) {
            HVH = ((temphawks_size - count - i) > 2) ? (double)((((temphawks_size - count - i) / food) * ((temphawks_size - count - i) / food))) : 0;

            if (dist(gen) < HVH) {
                if (H.HWK[i][1] == H.HWK[i - 1][1]) {
                    hs -= 2;
                    H.HWK[i][0] = 0;
                    H.HWK[i - 1][0] = 0;
                }
                else if (H.HWK[i][1] > H.HWK[i - 1][1]) {
                    H.HWK[i - 1][0] = 0;
                    hs--;
                }
                else {
                    H.HWK[i][0] = 0;
                    hs--;
                }
                flag = 1;
                i++;
            }
            else {
                hs++;
            }

        }
        if (flag) {
            for (int i = 0; i < H.HWK.size(); i++) {
                if (H.HWK[i][0] == 0) {
                    H.remove(i);
                }
            }

        }
        H.shuffle();
        H.shuffle();
        H.shuffle();
    }



};


void Part2_sim() {
    ofstream myfile;
    myfile.open("Doves_Hawks2.csv");
    int DAYS = 1000;
    int food = 100;
    Doves D = Doves();
    Hawks H = Hawks();
    H.addnew(0);

    int dove_size = D.DVS.size();
    int hawk_size = H.HWK.size();
    for (int i = 0; i < DAYS; i++) {
        sim_interation_part2(D, H, dove_size, hawk_size, food);
        while (dove_size != D.DVS.size()) {
            //        cout << dove_size<< endl;
            if (dove_size > D.DVS.size())D.DVS.push_back(1);
            else if (dove_size < D.DVS.size())D.DVS.pop_back();
        }
        while (hawk_size != H.HWK.size()) {
            //         cout<< hawk_size<<endl;
            vector<int>temp = { 1,0 };
            if (hawk_size > H.HWK.size())H.HWK.push_back(temp);
            else if (hawk_size < H.HWK.size())H.HWK.pop_back();
        }
        // cout << " Hawks: " << H.HWK.size() << " Doves: " << D.DVS.size() << endl;
        // cout << " Hawks: " << hawk_size << " Doves: " << dove_size << endl;
        myfile << D.DVS.size() << "," << H.HWK.size() << "\n";
    }
    // cout << " Hawks: " << H.HWK.size() << " Doves: " << D.DVS.size() << endl;
     //cout << " Hawks: " << hawk_size << " Doves: " << dove_size << endl;
     //myfile.close();

};


PyObject* Problem1(PyObject* /* unused module reference */, PyObject* o) {
    double x = PyFloat_AsDouble(o);
    Part1_sim();

    return PyFloat_FromDouble(0);
}



PyObject* Problem2(PyObject* /* unused module reference */, PyObject* o) {
    double x = PyFloat_AsDouble(o);
    Part2_sim();

    return PyFloat_FromDouble(0);
}












static PyMethodDef Doves_and_Hawks_methods[] = {
    // The first property is the name exposed to Python, fast_tanh
    // The second is the C++ function with the implementation
    // METH_O means it takes a single PyObject argument
    { "first_Problem", (PyCFunction)Problem1, METH_O, nullptr },
        { "second_Problem", (PyCFunction)Problem2, METH_O, nullptr },
        // Terminate the array with an object containing nulls.
        { nullptr, nullptr, 0, nullptr }
};

static PyModuleDef Doves_and_Hawks_module = {
    PyModuleDef_HEAD_INIT,
    "Doves_and_Hawks",                        // Module name to use with Python import statements
    "Provides some functions",  // Module description
    0,
    Doves_and_Hawks_methods                   // Structure that defines the methods of the module
};

PyMODINIT_FUNC PyInit_Doves_and_Hawks() {
    return PyModule_Create(&Doves_and_Hawks_module);
}
















