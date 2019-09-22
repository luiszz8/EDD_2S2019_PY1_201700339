#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <sstream>
using namespace std;


struct nodoL{
    int nivel;
    string capa;
    struct nodoL *abaj=0;
    struct nodoL *arri=0;
    struct nodoD *siguiente=0;

};
typedef struct nodoL *Llista;
struct nodoA{
    string nombre;
    nodoA *izq;
    nodoA *der;
    nodoL *adentro;
};

nodoA *crearNodoA(string);
void insertarArbol(nodoA *&,string);
void insertarCapa(nodoA*,int,string,string);
string recuperarColor(nodoA*,string);
void graficar(nodoA*,string,string);
void imprimirArbol(nodoA*);
void graficarArbol(nodoA*);

struct nodoD{
       string dato;
       int y;
       int x;
       int id;
       struct nodoD *sig=0;
       struct nodoD *abajo=0;
       struct nodoD *arriba=0;
       struct nodoD *ant=0;
};
typedef struct nodoD *Tlista;

void imprimir(Tlista listay)
{
     int i = 0;
     if(listay==0){
        cout <<"subnormal"<< endl;
     }
     while(listay != 0)
     {
          cout <<listay->x << endl;
          cout <<listay->y << endl;
          listay = listay->sig;
          i++;
     }

}

struct nodoD *buscarFila(Tlista lista,int y){
    Tlista t = new(struct nodoD);
    t->dato="null";
    while(lista!=0){
        if(lista->y==y){
            return lista;
        }
        lista=lista->abajo;
    }
    //cout <<"buscar F"<< endl;
    return 0;
}

struct nodoD *buscarColumna(Tlista lista,int x){
    Tlista t = new(struct nodoD);
    t->dato="nulle";
    //t=lista;
    while(lista!=0){
        if(lista->x==x){
            return lista;
        }
        //cout <<lista->x<< endl;
        lista=lista->sig;
        if(lista==0){
            return 0;
        }

    }
    //cout <<"buscar C"<< endl;
    return 0;
}
struct nodoD *insertar_ordenado_columna(Tlista &nuevo,Tlista &cabeza_col){
    Tlista temp = cabeza_col;
    int bandera = 0;
    while(1){
        //cout <<"cilco"<< endl;
        if(temp->x == nuevo->x){
            //cout <<"igual"<< endl;
            temp->y=nuevo->y;
            temp->dato=nuevo->dato;
            return temp;
        }else if(temp->x > nuevo->x){
            //cout <<"menor"<< endl;
            bandera = 1;
            break;
        }
        //cout <<"pisado"<< endl;
        if(temp->sig!=0){
            //cout <<"izquierda"<< endl;
            temp = temp->sig;
        }else{
            //cout <<"break"<< endl;
            break;
        }
    }
    if(bandera == 1){
        //cout <<"asig"<< endl;
        nuevo->sig=temp;
        temp->ant->sig=nuevo;
        nuevo->ant=temp->ant;
        temp->ant=nuevo;
    }else{
        //cout <<"asignado"<< endl;
        temp->sig=nuevo;
        //nuevo->sig=0;
        nuevo->ant=temp;
    }
    //cout <<"datos2"<< endl;
    return nuevo;
}

struct nodoD *insertar_ordenado_fila(Tlista &nuevo,Tlista &cabeza_fila){
    Tlista temp = cabeza_fila;
    int bandera = 0;
    //cout <<"insertar fila"<< endl;
    while(1){
        if(temp->y == nuevo->y){
            temp->x=nuevo->x;
            temp->dato=nuevo->dato;
            return temp;
        }else if(temp->y > nuevo->y){
            bandera = 1;
            break;
        }
        if(temp->abajo!=0){
            temp = temp->abajo;
        }else{
            break;
        }
    }
    if(bandera== 1){
        nuevo->abajo=temp;
        temp->arriba->abajo=nuevo;
        nuevo->arriba=temp->arriba;
        temp->arriba=nuevo;
    }else{
        temp->abajo=nuevo;
        //nuevo->abajo=0;
        nuevo->arriba= temp;
    }

    return nuevo;
}

struct nodoD *crearColumna(Tlista &lista,int x){
    Tlista cabeza_columna= lista;
    Tlista nuevo=new(struct nodoD);
    nuevo->x=x;
    nuevo->y=-1;
    nuevo->dato="COL";
    //cout <<"llega aca crear columna"<< endl;
    Tlista columna = insertar_ordenado_columna(nuevo,cabeza_columna);
    //cout <<"despues"<< endl;
    return columna;
}

struct nodoD *crearFila(Tlista &lista,int y){
    Tlista cabeza_fila= lista;
    Tlista nuevo=new(struct nodoD);
    nuevo->x=-1;
    nuevo->y=y;
    nuevo->dato="FIL";
    Tlista fila = insertar_ordenado_fila(nuevo,cabeza_fila);
    return fila;
}

void insertar(int x,int y,string dato,Tlista &lista,int id){
    Tlista nuevo = new(struct nodoD);
    nuevo->x=x;
    nuevo->y=y;
    nuevo->dato=dato;
    nuevo->id=id;
    Tlista nodoColumna,nodoFila;
    nodoColumna = buscarColumna(lista,x);
    nodoFila = buscarFila(lista,y);
    /*if(nodoColumna==0){
        cout <<"nuloC"<< endl;
    }
    if(nodoFila==0){
        cout <<"nuloF"<< endl;
    }*/
    if(nodoColumna==0 && nodoFila==0){
        //cout <<"nulo todo"<< endl;
        //imprimir(lista);
        //cout <<"datos"<< endl;
        nodoColumna=crearColumna(lista,x);
        nodoFila=crearFila(lista,y);
        nuevo=insertar_ordenado_columna(nuevo,nodoFila);
        nuevo=insertar_ordenado_fila(nuevo,nodoColumna);
        return;
    }else if(nodoColumna==0 && nodoFila!=0){
        //cout <<"caso 2"<< endl;
        nodoColumna=crearColumna(lista,x);
        nuevo=insertar_ordenado_columna(nuevo,nodoFila);
        nuevo=insertar_ordenado_fila(nuevo,nodoColumna);
        return;
    }else if(nodoColumna!=0 && nodoFila==0){
        //cout <<"caso 3"<< endl;
        nodoFila=crearFila(lista,y);
        nuevo=insertar_ordenado_columna(nuevo,nodoFila);
        nuevo=insertar_ordenado_fila(nuevo,nodoColumna);
        return;
    }else if(nodoColumna!=0 && nodoFila!=0){
        //cout <<"nada nuloF"<< endl;
        nuevo=insertar_ordenado_columna(nuevo,nodoFila);
        nuevo=insertar_ordenado_fila(nuevo,nodoColumna);
        return;
    }
}
void crearHTML(int vecesDiv,string nombre){
    ofstream archivo;
    string contenido;
    int veces=0;
    string aux=nombre;
    nombre=nombre +".html";
    archivo.open(nombre.c_str(),ios::out);
    contenido="<!DOCTYPE html> \n <html> \n <head> \n   <!-- Link to our stylesheet Painting our Pixel Art --> \n";
    contenido=contenido+"<link rel=\"stylesheet\" href=\""+aux+".css\"> \n </head> \n <body> \n";
    contenido=contenido+"<div class=\"canvas\"> \n";
    while(veces<vecesDiv){
        contenido=contenido+"<div class=\"pixel\"></div> \n";
        veces=veces+1;
    }
    contenido=contenido+"</div> \n </body> \n </html>";
    archivo<<contenido;
    archivo.close();
}

void crearCSS(nodoA *arbol,int pwidth,int pheight,int iwidth,int iheight,string nombre){
    ofstream archivo;
    string contenido;
    string oficial;
    int width=pwidth*iwidth;
    int height=pheight*iheight;
    std::stringstream sww;
    sww << width;
    string sw= sww.str();
    std::stringstream shh;
    shh << height;
    string sh= shh.str();
    std::stringstream pww;
    pww << pwidth;
    string pw= pww.str();
    std::stringstream phh;
    phh << pheight;
    string ph= phh.str();
    oficial=nombre;
    nombre=nombre+".css";
    archivo.open(nombre.c_str(),ios::out);
    contenido="body { \n background: #ffffff; \n height: 100vh; \n display: flex; \n justify-content: center; \n align-items: center; \n }";
    contenido=contenido+".canvas { \n width: "+sw+"px; \n height:"+sh+"px; \n } \n";
    contenido=contenido+".pixel { \n width: "+pw+"px; \n height: "+ph+"px; \n float: left; \n box-shadow: 0px 0px 1px #fe0000; \n}";

    //cout<<"aqui truena"<<endl;
    contenido=contenido+recuperarColor(arbol,oficial);
    archivo<<contenido;
    archivo.close();
}

void insertarNC(int nivel,string capa,Llista &inicio){
    Llista nuevo = new(struct nodoL);
    nuevo->nivel=nivel;
    nuevo->capa=capa;
    if (inicio==0){
        Tlista t = new(struct nodoD);
        t->dato="raiz";
        t->x=-1;
        t->y=-1;
        ifstream cape;
        char aux[100];
        char conte[500];//contenido
        strcpy(aux,capa.c_str());
        cape.open(aux,ios::in);
        string linea;
        getline(cape,linea);
        int contadorx=0;
        int contadory=0;
        int contadorId=0;
        while(!cape.eof()){
            strcpy(conte,linea.c_str());
            char* pieza=strtok(conte,",");
            //string color(pieza);
            //insertar(contadorx,contadory,color,t);
            while(pieza!=NULL){
                string color(pieza);
                insertar(contadorx,contadory,color,t,contadorId);
                contadorx=contadorx+1;
                contadorId=contadorId+1;
                pieza=strtok(NULL,",");
                /*if(pieza==0){
                    cout<<"vaina nula"<<endl;
                }*/
            }
            contadory=contadory+1;
            contadorx=0;
            getline(cape,linea);
        }
        nuevo->siguiente=t;
        inicio=nuevo;
        //imprimir(nuevo->siguiente);
    }else{
        Tlista t = new(struct nodoD);
        t->dato="raiz";
        t->x=-1;
        t->y=-1;
        ifstream cape;
        char aux[100];
        char conte[500];//contenido
        strcpy(aux,capa.c_str());
        cape.open(aux,ios::in);
        string linea;
        getline(cape,linea);
        int contadorx=0;
        int contadory=0;
        int contadorId=0;
        while(!cape.eof()){
            strcpy(conte,linea.c_str());
            char* pieza=strtok(conte,",");
            //string color(pieza);
            //insertar(contadorx,contadory,color,t);
            while(pieza!=NULL){
                string color(pieza);
                insertar(contadorx,contadory,color,t,contadorId);
                contadorx=contadorx+1;
                contadorId=contadorId+1;
                pieza=strtok(NULL,",");
                /*if(pieza==0){
                    cout<<"vaina nulo"<<endl;
                }*/
            }
            contadory=contadory+1;
            contadorx=0;
            getline(cape,linea);
        }
        nuevo->siguiente=t;


        Llista tem=inicio;
        Llista atras=inicio;
        if(nivel<inicio->nivel){
            nuevo->abaj=inicio;
            inicio->arri=nuevo;
            inicio=nuevo;
        }else{
            while(nivel>=tem->nivel &&  tem->abaj!=0){
                tem=tem->abaj;
            }
            if (nivel>=tem->nivel) {
                nuevo->arri=tem;
                tem->abaj=nuevo;
            } else {
                nuevo->abaj=tem;
                tem->arri->abaj=nuevo;
                nuevo->arri=tem->arri;
                tem->arri=nuevo;
            }
        }
    }
}

nodoA *arbol=NULL;

int main()
{
    int opcion= 999;
    while(opcion!=7){
        cout <<"--------------Menu--------------"<< endl;
        cout <<"1) Insertar imagen"<< endl;
        cout <<"2) Seleccionar imagen"<< endl;
        cout <<"3) Reportes"<< endl;
        int opcion= 999;
        cin >> opcion;
        switch(opcion){
            case 1:{
                int anchoImagen;
                int altoImagen;
                int anchoPixel;
                int altoPixel;
                char nombre[100];
                string texto;
                string figura;
                string nombreh;
                cout <<"Ingrese nombre de figura"<< endl;
                cin >> figura;
                nombreh=figura;
                char au[100];
                cout <<"Ingrese nombre de archivo"<< endl;
                cin >> nombre;
                ifstream capas;
                capas.open(nombre,ios::in);
                insertarArbol(arbol,figura);
                getline(capas,texto);
                getline(capas,texto);
                int contador=0;
                while(!capas.eof()){
                    strcpy(au,texto.c_str());
                    char* pieza=strtok(au,",");
                    char& ni=*pieza;
                    int niv= atoi(pieza);
                    pieza=strtok(NULL,",");
                    string n(pieza);
                    if(niv!=0){
                        insertarCapa(arbol,niv,figura,n);
                    }else{
                        ifstream seting;
                        char auxi[100];
                        char conte[500];//contenido
                        strcpy(auxi,n.c_str());
                        seting.open(auxi,ios::in);
                        string linea;
                        getline(seting,linea);
                        getline(seting,linea);
                        while(!seting.eof()){
                            strcpy(auxi,linea.c_str());
                            char* bloque=strtok(auxi,",");
                            string ver(bloque);
                            if(ver=="image_width"){
                                bloque=strtok(NULL,",");
                                anchoImagen=atoi(bloque);
                            }else if(ver=="image_height"){
                                bloque=strtok(NULL,",");
                                altoImagen=atoi(bloque);
                            }else if(ver=="pixel_height"){
                                bloque=strtok(NULL,",");
                                altoPixel=atoi(bloque);
                            }else if(ver=="pixel_width"){
                                bloque=strtok(NULL,",");
                                anchoPixel=atoi(bloque);
                            }
                            getline(seting,linea);
                        }
                        seting.close();

                    }
                    //cout<<niv<< endl;
                    getline(capas,texto);
                }
                //cout<<"cierra"<< endl;
                capas.close();
                int veces=altoImagen*anchoImagen;
                crearHTML(veces,nombreh);
                crearCSS(arbol,anchoPixel,altoPixel,anchoImagen,altoImagen,nombreh);
                //cout <<"si termina"<< endl;
            break;
            }
            case 2:{
                imprimirArbol(arbol);
            break;
            }
            case 3:{
                int opcion3=0;
                while(opcion3<4){
                    cout <<"---------Reportes---------"<< endl;
                    cout <<"1) IMPORTED IMAGES REPORT"<< endl;
                    cout <<"2) IMAGE LAYER REPORT"<< endl;
                    cout <<"3) TODA LA IMAGEN"<< endl;
                    cin >> opcion3;
                    switch(opcion3){
                        case 1:{
                            graficarArbol(arbol);
                            system("arbol.png");
                        break;
                        }
                        case 2:{
                            string nombreI;
                            string capaI;
                            cout <<"Ingrese nombre de imagen "<< endl;
                            cin >> nombreI;
                            cout <<"Ingrese nombre de capa "<< endl;
                            cin >> capaI;
                            graficar(arbol,nombreI,capaI);
                        break;
                        }

                    }
                }
            }
        }
        cin >> opcion;
    }
    return 0;
}
 nodoA *crearNodoA(string nombre){
    nodoA *nuevo=new nodoA();
    nuevo->nombre=nombre;
    nuevo->izq=0;
    nuevo->der=0;
    nuevo->adentro=0;

    return nuevo;
}

void insertarArbol(nodoA *&arbol,string n){
    if(arbol==NULL){
        nodoA *nuevo=crearNodoA(n);
        arbol=nuevo;
    }else{
        string valor=arbol->nombre;
        if(valor.compare(0,1,n,0,1)<0){//menor n
            insertarArbol(arbol->izq,n);
        }else{
            insertarArbol(arbol->der,n);
        }
    }
}

void insertarCapa(nodoA *arbol,int nivel,string nombre,string capa){
    if(arbol==NULL){
        return;
    }else{
        insertarCapa(arbol->der,nivel,nombre,capa);
        if(arbol->nombre==nombre){
            insertarNC(nivel,capa,arbol->adentro);
        }
        insertarCapa(arbol->izq,nivel,nombre,capa);
    }
}
string recuperarColor(nodoA *arbol,string nombre){
    //cout <<nombre<< endl;
    string poderoso="";
    if(arbol==NULL){
        //cout <<"aquiR"<< endl;
        return poderoso;
    }else{
        //cout <<"NO"<< endl;
        cout <<arbol->nombre<< endl;
        recuperarColor(arbol->der,nombre);
        if(arbol->nombre==nombre){
            //cout <<"aqui"<< endl;
            Llista temL=arbol->adentro;

            while(temL!=0){
                int contador=1;
                Tlista temN=temL->siguiente;
                Tlista temNIni=temN;
                while(temN->sig!=0 ||temN->abajo!=0){
                    if(temN->dato!="x" && (temN->x!=-1 && temN->y!=-1)){
                        char cadena[100];
                        strcpy(cadena,temN->dato.c_str());
                        char* pieza=strtok(cadena,"-");
                        string R1(pieza);
                        pieza=strtok(NULL,"-");
                        string G1(pieza);
                        pieza=strtok(NULL,"-");
                        string B1(pieza);
                        string supremo="rgb("+R1+","+G1+","+B1+")";
                        std::stringstream c;
                        c << contador;
                        string con= c.str();
                        poderoso=poderoso+".pixel:nth-child("+con+")";
                        poderoso=poderoso+"{background:"+supremo+";}";
                    }
                    if(temN->sig!=0){
                        temN=temN->sig;
                    }else{
                        temN=temNIni->abajo;
                        temNIni=temNIni->abajo;
                    }
                    if(temN->x!=-1 && temN->y!=-1){
                        contador=contador+1;
                    }
                    //cout <<contador<< endl;
                }
                temL=temL->abaj;
            }
        }
        recuperarColor(arbol->izq,nombre);
    }
    return poderoso;
}

void graficar(nodoA *arbol,string nombre,string capa){
    string maximo="digraph G { \n node[shape=box]; \n";
    if(arbol==NULL){
        return;
    }else{
        graficar(arbol->der,nombre,capa);
        if(arbol->nombre==nombre){
            Llista temL=arbol->adentro;
            while(temL!=0){
                if(temL->capa==capa){
                    Tlista temN=temL->siguiente;
                    Tlista temNIni=temN;
                    Tlista temN2=temL->siguiente;
                    Tlista temNIni2=temN2;
                    maximo=maximo+"{rank = same;\n";
                    while(temN->sig!=0 ||temN->abajo!=0){
                        if(temN->x!=-1 && temN->y!=-1){
                            if(temN->sig!=0){
                                std::stringstream c;
                                c << temN->id;
                                string con= c.str();
                                std::stringstream c2;
                                c2 << temN->sig->id;
                                string con2= c2.str();
                                maximo=maximo+"nodo"+con+"->"+"nodo"+con2+";\n";
                                maximo=maximo+"nodo"+con2+"->"+"nodo"+con+";\n";
                            }
                        }
                        if(temN->sig!=0){
                            temN=temN->sig;
                        }else{
                            maximo=maximo+"}\n";
                            maximo=maximo+"{rank = same;\n";
                            temN=temNIni->abajo;
                            temNIni=temNIni->abajo;
                        }
                    }
                    maximo=maximo+"}\n";
                    while(temN2->sig!=0 ||temN2->abajo!=0){
                        if(temN2->x!=-1 && temN2->y!=-1){
                            if(temN2->abajo!=0){
                                std::stringstream c;
                                c << temN2->id;
                                string con= c.str();
                                std::stringstream c2;
                                c2 << temN2->abajo->id;
                                string con2= c2.str();
                                maximo=maximo+"nodo"+con+"->"+"nodo"+con2+";\n";
                                maximo=maximo+"nodo"+con2+"->"+"nodo"+con+";\n";
                            }
                        }
                        if(temN2->abajo!=0){
                            temN2=temN2->abajo;
                        }else{
                            temN2=temNIni2->sig;
                            temNIni2=temNIni2->sig;
                            //cout <<"paasd"<< endl;
                        }
                    }
                    maximo=maximo+"}";
                }
                temL=temL->abaj;
                //cout <<"salee"<< endl;
            }
            //cout <<"sale"<< endl;
        }
        graficar(arbol->izq,nombre,capa);
    }
    //cout <<"archivo"<< endl;
    ofstream archivo;
    string nom="capa.dot";
    archivo.open(nom.c_str(),ios::out);
    archivo<<maximo;
    archivo.close();
    system("dot -Tpng capa.dot -o capa.png");
    system("capa.png");
    //cout <<"archivof"<< endl;
}

void imprimirArbol(nodoA *arbol){
    if(arbol==NULL){
        return;
    }else{
        imprimirArbol(arbol->izq);
        cout <<arbol->nombre<< endl;
        imprimirArbol(arbol->der);
    }
}
void graficarArbol(nodoA *arbol){
    string mamadisimo="digraph G { \n";
    if(arbol==NULL){
        return;
    }else{
        imprimirArbol(arbol->der);
        if(arbol->der!=0){
            mamadisimo=mamadisimo+"\""+arbol->nombre+"\"->\""+arbol->der->nombre+"\";";
        }
        mamadisimo=mamadisimo+"\""+arbol->nombre+"\"->\""+arbol->nombre+"\";";
        imprimirArbol(arbol->izq);
        if(arbol->izq!=0){
            mamadisimo=mamadisimo+"\""+arbol->nombre+"\"->\""+arbol->izq->nombre+"\";";
        }
    }
    mamadisimo=mamadisimo+"}";
    ofstream archivo;
    string nom="arbol.dot";
    archivo.open(nom.c_str(),ios::out);
    archivo<<mamadisimo;
    archivo.close();
    system("dot -Tpng arbol.dot -o arbol.png");
}
