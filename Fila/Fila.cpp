#include <iostream>
#include <string>

using namespace std;

class Fila {

private:

	int CapMax; // Capacidade Máxima de elementos

	int Inicio; //Inicio da Fila

	int Fim; //Fim da Fila

	int NumItens; //Número de itens da fila

	float *Items; //Os items/elementos da fila (que serão alocados dinamicamente)

public:
	/**********
		Inicio getters
	**********/

	int getInicio() {
		return this->Inicio;
	}

	int getFim() {
		return this->Fim;
	}

	int getCapacidade() {
		return this->CapMax;
	}

	int getNumItens() {
		return this->NumItens;
	}

	float* getItems() {
		return (*this).Items;
	}

	/**********
		Fim getters
	**********/

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

	Fila operator+(Fila); //Soma os valores de cada posição das duas filas

	Fila operator+(float); //Soma cada posição da fila com o valor float passado

	Fila& operator+=(Fila); //Soma nas posições da fila os valores da fila passada como parametro

	Fila operator==(Fila); //Só serão iguais se tiverem os mesmos elementos na mesma ordem (considerando a ordem dos elementos na fila, e não do vetor de armazenamento).

	Fila operator!=(Fila); //O oposto da anterior. Se as filas tiverem tamanhos diferentes, já é possível considerá-las diferentes.

	friend ostream& operator<<(ostream&, Fila); //Permite que uma fila seja impressa no cout. Mostra os elementos na ordem de saída da fila.

	Fila operator[](float); //Exibe valor armazenado nessa posição da ordem da fila.
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

Fila& Fila::operator+=(Fila fila) {
	for (int i = 0; i < this->CapMax; i++) {
		this->Items[i] = this->Items[i] + fila.Items[i];
	}

	return *this;
}

ostream& operator<<(ostream& o, Fila& fila) {
	int cont, i;

	for (cont = 0, i = fila.getInicio; cont < fila.getNumItens; cont++) {

		printf("%.2f\t", fila.getItems[i++]);

		if (i == fila.getCapacidade)
			i = 0;

	}
	printf("\n\n");
}