#include <iostream>
#include <string>

using namespace std;

class Fila {

private:

	int CapMax; // Capacidade M�xima de elementos

	int Inicio; //Inicio da Fila

	int Fim; //Fim da Fila

	float *Items; /*Os items/elementos da fila (que ser�o

				  alocados dinamicamente)*/

public:

	Fila(int N); /*Construtor padr�o, aloca dinamicamente

				 N floats para o atributo Items, e seta os atributos de

				 controle da fila */

	~Fila(); /*Destrutor da fila, deve-se desalocar a

			 mem�ria que foi adquirida no construtor.*/

	void inserir(float NovoItem); //enfileira um novo item

	float retirar(); //desenfileira um item (retornando-o)

	bool vazia(); //verifica se a fila est� vazia

	bool cheia(); //verifica se a fila est� cheia

	int tamanho();//retorna quantos itens existem na fila

};

Fila::Fila(int N) {

}

Fila::~Fila() {

}

void Fila::inserir(float item) {

}

float Fila::retirar() {

}

bool Fila::vazia() {

}

bool Fila::cheia() {

}

int Fila::tamanho() {

}