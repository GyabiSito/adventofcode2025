#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
using namespace std;

// Lista de líneas del input
struct nodoLista
{
    long long valor;
    nodoLista *sig;
} typedef *Lista;

struct nodoListaString{
    string valor;
    nodoListaString * sig;
} typedef * ListaString;

struct nodoRes
{
    Lista l1;
    Lista l2;
    Lista l3;
    Lista l4;
    ListaString operadores;
} typedef *Res;

Lista crearLista()
{
    nodoLista *nodo = new nodoLista;
    nodo->valor = 0;
    nodo->sig = NULL;
    return nodo;
}

Res crearRes()
{
    nodoRes *res = new nodoRes;
    res->l1 = NULL;
    res->l2 = NULL;
    res->l3 = NULL;
    res->l4 = NULL;
    res->operadores = NULL;
    return res;
}

void insertarvalor(Lista &L, long long valor)
{
    nodoLista *nuevo = new nodoLista;
    nuevo->valor = valor;
    nuevo->sig = NULL;
    if (L == NULL)
        L = nuevo;
    else
    {
        nodoLista *aux = L;
        while (aux->sig != NULL)
            aux = aux->sig;
        aux->sig = nuevo;
    }
}
void insertarOperador(ListaString &L, string valor)
{
    nodoListaString *nuevo = new nodoListaString;
    nuevo->valor = valor;
    nuevo->sig = NULL;
    if (L == NULL)
        L = nuevo;
    else
    {
        nodoListaString *aux = L;
        while (aux->sig != NULL)
            aux = aux->sig;
        aux->sig = nuevo;
    }
}

void insertarValores(Res &r)
{
    ifstream file("input.txt");
    if (!file.is_open()) return;

    string valorActual = "";
    char c;
    int fila = 1;

    Lista* listaNumerica = &r->l1;
    ListaString* listaStr = nullptr;

    while (file.get(c))
    {
        if (c == '\n')
        {
            if (!valorActual.empty())
            {
                if (fila < 5)
                    insertarvalor(*listaNumerica, stoll(valorActual));
                else if (fila == 5)
                    insertarOperador(*listaStr, valorActual);
                valorActual = "";
            }

            fila++;

            switch (fila)
            {
            case 2: listaNumerica = &r->l2; break;
            case 3: listaNumerica = &r->l3; break;
            case 4: listaNumerica = &r->l4; break;
            case 5: listaStr = &r->operadores; break;
            default: break;
            }

            continue;
        }

        if (c == ' ')
        {
            if (!valorActual.empty())
            {
                if (fila < 5)
                    insertarvalor(*listaNumerica, stoll(valorActual));
                else if (fila == 5)
                    insertarOperador(*listaStr, valorActual);
                valorActual = "";
            }
        }
        else
        {
            valorActual += c;
        }
    }

    // Último valor
    if (!valorActual.empty())
    {
        if (fila < 5)
            insertarvalor(*listaNumerica, stoll(valorActual));
        else if (fila == 5)
            insertarOperador(*listaStr, valorActual);
    }

    file.close();
}


void imprimirLista(Lista l)
{
    nodoLista *aux = l;
    while (aux != NULL)
    {
        cout << aux->valor << "->";
        aux = aux->sig;
    }
    cout << endl;
    return;
}
void imprimirLista(ListaString l)
{
    nodoListaString *aux = l;
    while (aux != NULL)
    {
        cout << aux->valor << "->";
        aux = aux->sig;
    }
    cout << endl;
    return;
}
int main()
{
    Res res = crearRes();
    insertarValores(res);
    // imprimirLista(res->l1);
    // imprimirLista(res->l2);
    // imprimirLista(res->l3);
    // imprimirLista(res->l4);
    // imprimirLista(res->operadores);

    long long total = 0;
    nodoLista *aux1 = res->l1;
    nodoLista *aux2 = res->l2;
    nodoLista *aux3 = res->l3;
    nodoLista *aux4 = res->l4;
    nodoListaString *auxOper = res->operadores;

    while (aux1 != NULL && aux2 != NULL && aux3 != NULL && aux4 != NULL && auxOper != NULL)
    {
        long long resLocal=0;
        if(auxOper->valor == "*"){
            resLocal = aux1->valor * aux2->valor * aux3->valor * aux4->valor;
        }
        if(auxOper->valor == "+"){
            resLocal = aux1->valor + aux2->valor + aux3->valor + aux4->valor;
        }
        aux1=aux1->sig;
        aux2=aux2->sig;
        aux3=aux3->sig;
        aux4=aux4->sig;
        auxOper=auxOper->sig;
        total+=resLocal;
    }

    cout << "el total es: " << total << endl;

    return 0;
}