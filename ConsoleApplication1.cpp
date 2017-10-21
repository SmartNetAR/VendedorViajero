//
//
//  Created by Leonardo Casales on 11/10/17.
//  Copyright © 2017 Leonardo Casales. All rights reserved.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
using namespace std;

#define maxn 110
int w[maxn][maxn]; // fila columna
bool check[maxn];
int nNodos; // numero de vertices
int nAristas; // numero de Aristas
int partida; // nodo de partida


struct arista {
	int nodoA;
	int nodoB;
	int peso;
};
//arista lista[maxn];
vector<arista> vecNodos ;
vector<int> caminoActual(0);


int a, b, peso;
int k;
void CrearNodo(int a, int b, int peso);
void GirarNodo(arista & nodoAGirar);
void LeerEntrada();
int MarcarPartida();
void LeerEntradaEjemplo();
void LeerEntradaEjemplo2();
void LeerEntradaEjemplo3();

void Insertar(arista nuevoNodo);


int main(){
	// insert code here...
	int menor = 999;
	int pos, newPos;
	newPos = 0;
	k = 0;
	arista vNodo ;
	vNodo.nodoA = 0;
	vNodo.nodoB = 0;
	vNodo.peso = 0;

	//LeerEntrada();
	LeerEntradaEjemplo();


	pos = MarcarPartida() - 0;
	caminoActual.push_back(partida - 0);

	int touch = 1;
	while (touch < nNodos) {

		menor = 999;
		for (int i = 1; i < nNodos; i++) {
			if (w[pos][i] < menor) {
				if (check[i] == false) {
					menor = w[pos][i];
					newPos = i;

					vNodo.nodoA = pos ;
					vNodo.nodoB = i ;
					vNodo.peso = menor ;
				}
			}
		}

		//cargo el primer nodo de vuelta a->b, b->a
		if (vecNodos.size() == 0) {
			caminoActual.push_back(vNodo.nodoB);
			vecNodos.push_back(vNodo);
			k = vNodo.peso * 2;
			GirarNodo(vNodo);
			caminoActual.push_back(vNodo.nodoB);
			vecNodos.push_back(vNodo);
		}
		else {
			Insertar(vNodo);
		}

		pos = newPos;
		check[pos] = true;
		touch++;
	}

	//muestro el recorrido
	for (int i = 0; i < caminoActual.size() - 1; i++) {
		printf("%d -> ", caminoActual[i]);
	}
	printf("%d\n", caminoActual[caminoActual.size() - 1]);
	printf("Peso total: %d\n", k);

	//muestro el conjunto de nodos
	printf("Lista de Nodos: %d\n", k);
	for (int i = 0; i < vecNodos.size(); i++) {
		printf("%d -> %d : %d\n", vecNodos[i].nodoA , vecNodos[i].nodoB , vecNodos[i].peso );
	}

	system("pause");
	return 0;
}

void LeerEntrada() {
	printf("Leyendo datos...\n");

	printf("ingrese el numero de nodos: ");
	scanf("%d", &nNodos);

	printf("ingrese el numero de aristas: ");
	scanf("%d", &nAristas);

	for (int i = 0; i < nAristas; i++) {
		for (int j = 0; j < nAristas; j++) {
			w[i][j] = 999;
		}
	}

	for (int i = 0; i < nAristas; i++) {
		printf("ingrese nodo a, b y peso: "); 
		scanf("%d%d%d", &a, &b, &peso);
		CrearNodo(a, b, peso);
	}
}

int MarcarPartida() {
	int valor = 0;
	printf("indica el nodo de partida:\n");
	scanf("%d", &valor);
	partida = valor;
	//inicializar checks
	for (int i = 0; i < nNodos; i++) {
		check[i] = false;
	}

	check[partida] = true;
	return partida;
}

void LeerEntradaEjemplo() {

	nNodos = 5;

	nAristas = 10;

	for (int i = 0; i < nAristas; i++) {
		for (int j = 0; j < nAristas; j++) {
			w[i][j] = 999;
		}
	}
	CrearNodo(0, 1, 2);
	CrearNodo(0, 2, 1);
	CrearNodo(0, 3, 10);
	CrearNodo(0, 4, 25);
	CrearNodo(1, 2, 18);
	CrearNodo(1, 3, 5);
	CrearNodo(1, 4, 5);
	CrearNodo(2, 3, 20);
	CrearNodo(2, 4, 2);
	CrearNodo(3, 4, 8);
}

void LeerEntradaEjemplo2() {

	nNodos = 4;

	nAristas = 6;

	for (int i = 0; i < nAristas; i++) {
		for (int j = 0; j < nAristas; j++) {
			w[i][j] = 999;
		}
	}
	CrearNodo(0, 1, 3);
	CrearNodo(0, 2, 5);
	CrearNodo(0, 3, 9);
	CrearNodo(1, 2, 2);
	CrearNodo(1, 3, 6);
	CrearNodo(2, 3, 1);

}

void LeerEntradaEjemplo3() {

	nNodos = 6;

	nAristas = 9;

	for (int i = 0; i < nAristas; i++) {
		for (int j = 0; j < nAristas; j++) {
			w[i][j] = 999;
		}
	}
	CrearNodo(0, 1, 4);
	CrearNodo(0, 2, 2);
	CrearNodo(1, 2, 1);
	CrearNodo(1, 3, 5);
	CrearNodo(2, 3, 8);
	CrearNodo(2, 4, 10);
	CrearNodo(3, 4, 2);
	CrearNodo(3, 5, 6);
	CrearNodo(4, 5, 2);

}


void CrearNodo(int a, int b, int peso ) {
	w[a ][b ] = peso;
	w[b ][a ] = peso;
}

void GirarNodo(arista & nodoAGirar) {
	int temp;
	temp = nodoAGirar.nodoA;
	nodoAGirar.nodoA = nodoAGirar.nodoB;
	nodoAGirar.nodoB = temp;
}

void Insertar(arista nuevoNodo) {
	arista temp;
	int nodoMenor = 0;
	int posMenor = 0;
	int pesoInsertadoA = 0;
	int pesoInsertadoB = 0;
	int pesoActual = 0;
	int marginal = 0;
	int marginalMenor = 999;

	printf("insertando: %d dentro de ", nuevoNodo.nodoB);
	for (int i = 0; i < caminoActual.size()-1; i++) {
		printf("%d -> ", caminoActual[i]);
	}
	printf("%d\n", caminoActual[caminoActual.size()-1]);

	for (int i = 0; i < vecNodos.size(); i++) {
		temp = vecNodos[i];
		pesoInsertadoA = w[temp.nodoA][nuevoNodo.nodoB];
		pesoInsertadoB = w[temp.nodoB][nuevoNodo.nodoB];
		if (pesoInsertadoA != 999 && pesoInsertadoB != 999) {
			pesoActual = temp.peso;
			marginal = pesoInsertadoA + pesoInsertadoB - pesoActual;
			printf("marginal: %d,%d = %d + %d - %d = %d\n", temp.nodoA, temp.nodoB,
				pesoInsertadoA, pesoInsertadoB, pesoActual, marginal);
			if (marginal < marginalMenor) {
				marginalMenor = marginal;
				nodoMenor = temp.nodoA;
				posMenor = i;
			}
		}
	}
	temp = vecNodos[posMenor];
	printf("la insercion menor es entre los nodos %d y %d con un peso marginal de %d\n\n\n",
			temp.nodoA, temp.nodoB  , marginalMenor);

	
	GirarNodo(nuevoNodo);
	caminoActual.insert(caminoActual.begin() + posMenor + 1, nuevoNodo.nodoA);
	vecNodos[posMenor].nodoB = nuevoNodo.nodoA;	//Modifico la conexión del nodo anterior hacia el nuevo nodo
	vecNodos[posMenor].peso = w[vecNodos[posMenor].nodoA][vecNodos[posMenor].nodoB]; //Actualizo el peso de la arista de nodos anteriorers
	if (vecNodos[posMenor].nodoB != nuevoNodo.nodoB) {
		nuevoNodo.nodoB = vecNodos[posMenor + 1].nodoA ;	//Modifico la conexión del nuevo nodo con el nodo siguiente
		nuevoNodo.peso = w[nuevoNodo.nodoA][nuevoNodo.nodoB]; //Actualizo el peso de la arista del nuevo nodo
	}	
	vecNodos.insert(vecNodos.begin() + posMenor + 1, nuevoNodo);
	k += marginalMenor;
}
