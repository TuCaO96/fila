#include <iostream>
#include <string>

using namespace std;

class Fila {

private:

	int CapMax; // Capacidade Máxima de elementos

	int Inicio; //Inicio da Fila

	int Fim; //Fim da Fila

	int NumItens; //Número de itens da fila

	float *Items; /*Os items/elementos da fila (que serão

				  alocados dinamicamente)*/

public:

	Fila(int N); /*Construtor padrão, aloca dinamicamente

				 N floats para o atributo Items, e seta os atributos de

				 controle da fila */

	~Fila(); /*Destrutor da fila, deve-se desalocar a

			 memória que foi adquirida no construtor.*/

	void inserir(float NovoItem); //Enfileira um novo item

	float retirar(); //Desenfileira um item (retornando-o)

	bool vazia(); //Verifica se a fila está vazia

	bool cheia(); //Verifica se a fila está cheia

	int tamanho();//Retorna quantos itens existem na fila

};

Fila::Fila(int N) {
	this->CapMax = N;
	this->Items = (float*)malloc(this->CapMax * sizeof(float));
	this->Inicio = 0;
	this->Fim = -1;
	this->NumItens = 0;
}

Fila::~Fila() {
	delete this;
}

void Fila::inserir(float item) {
	if (this->Fim == this->CapMax - 1) {
		this->Fim = -1;
	}

	this->Fim++; //Atualiza posicao final da lista
	this->Items[this->Fim] = item; //adiciona item a fila
	this->NumItens++; //Acresce contador de numero de itens
}

float Fila::retirar() {
	float aux = this->Items[this->Inicio++]; //Pega o valor da posicao e acresce o primeiro

	if (this->Inicio == this->CapMax) {
		this->Inicio = 0;
	}

	this->NumItens--; //Retira item do contador

	return aux;
}

bool Fila::vazia() {
	return this->NumItens == 0;
}

bool Fila::cheia() {
	return this->NumItens == this->CapMax;
}

int Fila::tamanho() {
	return this->CapMax;
}