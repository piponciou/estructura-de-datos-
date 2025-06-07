#include <stdio.h>
#include <string.h>

struct Maquina {
    int codigo;
    char *nombre;
    char *categoria;
};
struct NodoMaquina {
    struct Maquina *dato;
    struct NodoMaquina *sig;
};
struct Sucursal {
    char *nombreSucursal;
    struct NodoMaquina *maquinas;
};
struct NodoSucursal {
    struct Sucursal *sucursal;
    struct NodoSucursal *izq;
    struct NodoSucursal *der;
};
struct Catalogo {
    struct NodoSucursal *raiz;
};

/* Pasos primera funcion
 * 1.contar cantidad de maquinas en UNA sucursal, la funcion recibe el head de las maquinas la cual es una lista circular simplemente enlazada
 * 2.buscar sucursal en arbol binario de busqueda, el recorrido debe ser en in-orden
 * 3.implementarlo en funcion principal
 */



int contarMaquinasUnaSucursal(struct NodoMaquina *headMaquinas) {
    int contador = 0;
    struct NodoMaquina *rec;

    if (headMaquinas == NULL) return 0;

    rec = headMaquinas;

    do {
        contador++;
        rec = rec->sig;
    }while (rec != headMaquinas);

    return contador;
}

/*recorrer el arbol binario de busqueda por el nombre, y en in-orden*/
struct Sucursal *buscarSucursalInOrden(struct NodoSucursal *nodo, char *nombreSucursal){
    int comparador;
    if (nodo!=NULL) {
        comparador = strcmp(nombreSucursal,nodo->sucursal->nombreSucursal);

        if (comparador < 0)
            return buscarSucursalInOrden(nodo->izq,nombreSucursal);

        if (comparador == 0)
            return nodo->sucursal;

        return buscarSucursalInOrden(nodo->der,nombreSucursal);
    }
    return NULL;
}

/*funcion principal*/
int contarMaquinasEnSucursal(struct Catalogo *cat, char *nombreSucursal){
    int contador;
    struct Sucursal *sucursalBuscada = buscarSucursalInOrden(cat->raiz,nombreSucursal);

    if (sucursalBuscada!=NULL) {
        contador = contarMaquinasUnaSucursal(sucursalBuscada->maquinas);
        return contador;
    }
    return 0;
}

/* Pasos segunda funcion
 * 1.buscar sucursal pre-orden
 * 2.desenlazar maquina en sucursal (lista circular)
 */

struct Sucursal *buscarSucursalPreOrden(struct NodoSucursal *nodo, char *nombreSucursal) {
    int comparador;
    if (nodo!=NULL) {
        comparador = strcmp(nombreSucursal,nodo->sucursal->nombreSucursal);

        if (comparador == 0)
            return nodo->sucursal;

        if (comparador < 0)
            return buscarSucursalPreOrden(nodo->izq,nombreSucursal);

        return buscarSucursalPreOrden(nodo->der,nombreSucursal);
    }

    return NULL;
}

void desenlazarMaquina(struct NodoMaquina **headMaquinas, int idMaquinaDesenlazar) {
    struct NodoMaquina *rec ;
    struct NodoMaquina *ultimo = NULL;

    //caso en que esta vacia la lista circular
    if ((*headMaquinas) == NULL)
        return;

    /*primer caso donde la lista tiene solo un dato y es el que quiero desenlazar*/
    if ((*headMaquinas)->dato->codigo == idMaquinaDesenlazar && (*headMaquinas)->sig == *headMaquinas) {
        (*headMaquinas) = NULL;
        return;
    }


    /*caso donde el que quiero desenlazar es el head y hay más nodos*/
    if ((*headMaquinas)->dato->codigo == idMaquinaDesenlazar) {
        ultimo = (*headMaquinas)->sig;
        while (ultimo->sig != *headMaquinas) {
            ultimo = ultimo->sig;
        }
        ultimo->sig = (*headMaquinas)->sig;
        (*headMaquinas) = (*headMaquinas)->sig;
        return;
    }


    /*no es ni caso 1 ni caso 2, osea que el que busco esta en medio*/
    rec = (*headMaquinas);
    while(rec->sig->dato->codigo != idMaquinaDesenlazar && rec->sig != *headMaquinas) {
        rec = rec->sig;
    }
    if (rec->sig->dato->codigo == idMaquinaDesenlazar) {
        rec->sig = rec->sig->sig;
        return;
    }
    return ;
}


void eliminarMaquinaDeSucursal(struct Catalogo *cat, char *nombreSucursal, int codigoMaquina){
    struct Sucursal *sucursal;
    sucursal = buscarSucursalPreOrden(cat->raiz, nombreSucursal);

    if (sucursal!=NULL) {
        desenlazarMaquina(&sucursal->maquinas, codigoMaquina);
        return;
    }
    return;

}



