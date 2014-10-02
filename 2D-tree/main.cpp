#include <iostream>
#include <fstream>
#include <vector>
#include "vec2.h"
#include "tree.h"

using namespace std;

int main(int argc, const char * argv[]) {
    int n = 0, cant;
    vec2* arr;
    ifstream fin("datos.in");
    //carga los valores en arr
    if (fin.is_open()) {
        fin>>n;
        cant = n;
        arr = new vec2[n];
        while (n>0) {
            float x, y;
            fin>>x;
            fin>>y;
            arr[cant-n].x = x;
            arr[cant-n].y = y;
            n--;
        }
        fin.close();
    } else
        return -1;
    cout<<"Termino de leer el archivo"<<endl;
    tree t(arr, cant);
    string s = "";
    while (s != "exit") {
        if (s=="search") {
            float x, y;
            cout<<"Ingrese x: ";
            cin>>x;
            cout<<"Ingrese y: ";
            cin>>y;
            if (t.searchFor({ x, y}))
                cout<<"Este numero esta indexado."<<endl;
            else
                cout<<"Este numero no esta indexado."<<endl;
        } else if (s=="add") {
            float x, y;
            cout<<"Ingrese x: ";
            cin>>x;
            cout<<"Ingrese y: ";
            cin>>y;
            t.add({x, y});
            cout<<"El punto ("<<x<<", "<<y<<") se a indexado correctamente."<<endl;
        } else if(s=="find") {
            float x1, y1;
            cout<<"Ingrese x del minimo: ";
            cin>>x1;
            cout<<"Ingrese y del minimo: ";
            cin>>y1;
            float x2, y2;
            cout<<"Ingrese x del maximo: ";
            cin>>x2;
            cout<<"Ingrese y del maximo: ";
            cin>>y2;
            vector<vec2> points = t.rangeSearch({x1, y1}, {x2, y2});
            if (points.empty())
                cout<<"No se encontro ninguna coordenada asociada a su busqueda"<<endl;
            else {
                cout<<"Los elementos encontrados fueron: "<<endl;
                for (vector<vec2>::iterator it = points.begin(); it != points.end(); ++it)
                    cout<<' '<<"("<<it->x<<", "<<it->y<<")"<<endl;
            }
        } else if (s=="close") {
            float x, y;
            cout<<"Ingrese x: ";
            cin>>x;
            cout<<"Ingrese y: ";
            cin>>y;
            vec2 v = t.closest({x, y});
            cout<<"El punto mas cercano es: ("<<v.x<<", "<<v.y<<")"<<endl;
        } else if(s!="exit" && s!="")
            cout<<"El comando que usted a ingresado no existe, intente con otro";
        cout<<endl<<"Ingrese un comando"<<endl<<endl;
        cin>>s;
    }
    return 0;
}

