#include <iostream>
#include <string>

using namespace std;

class Fila {

private:

	int CapMax; // Capacidade M�xima de elementos

	int Inicio; //Inicio da Fila

	int Fim; //Fim da Fila

	int NumItens; //N�mero de itens da fila

	float *Items; //Os items/elementos da fila (que ser�o alocados dinamicamente)

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

	Fila(int N); /*Construtor padr�o, aloca dinamicamente

				 N floats para o atributo Items, e seta os atributos de

				 controle da fila */

	~Fila(); /*Destrutor da fila, deve-se desalocar a

			 mem�ria que foi adquirida no construtor.*/

	void inserir(float NovoItem); //Enfileira um novo item

	float retirar(); //Desenfileira um item (retornando-o)

	bool vazia(); //Verifica se a fila est� vazia

	bool cheia(); //Verifica se a fila est� cheia

	int tamanho(); //Retorna quantos itens existem na fila

	Fila operator+(Fila); //Soma os valores de cada posi��o das duas filas

	Fila operator+(float); //Soma cada posi��o da fila com o valor float passado

	Fila &operator+=(Fila); //Soma nas posi��es da fila os valores da fila passada como parametro

	bool operator==(Fila); //S� ser�o iguais se tiverem os mesmos elementos na mesma ordem (considerando a ordem dos elementos na fila, e n�o do vetor de armazenamento).

	bool operator!=(Fila); //O oposto da anterior. Se as filas tiverem tamanhos diferentes, j� � poss�vel consider�-las diferentes.

	friend ostream& operator<<(ostream&, Fila); //Permite que uma fila seja impressa no cout. Mostra os elementos na ordem de sa�da da fila.

	Fila operator[](float); //Exibe valor armazenado nessa posi��o da ordem da fila.
};

Fila::Fila(int N) {
	this->CapMax = N; //Define propriedades iniciais de uma fila
	this->Items = new float[N];
	this->Inicio = 0;
	this->Fim = 0;
	this->NumItens = 0;
}

Fila::~Fila() {
	delete this->Items; //Libera ponteiro de itens na destrui��o da classe
}

void Fila::inserir(float item) {
	if (this->Fim == this->CapMax -1) { //Caso chegue no fim do array da fila, valor final estar� na primeira posi��o dela
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
	return this->NumItens == 0; //Se o numero de itens for igual a 0, ela est� vazia
}

bool Fila::cheia() {
	return this->NumItens == this->CapMax; //Se o num de itens for igual a sua capacidade, est� cheia
}

int Fila::tamanho() {
	return this->NumItens; //Retorna o num de itens
}

Fila &Fila::operator+=(Fila fila) {
	for (int i = 0; i < this->CapMax; i++) {
		this->Items[i] = this->Items[i] + fila.Items[i]; //Percorre os dois arrays, somando seus valores
	}

	return *this;
}

bool Fila::operator==(Fila fila) {
	bool resultado = true;
	for (int i = 0; i < this->CapMax; i++) {
		if (this->Items[i] != fila.Items[i]) { //Se um n�mero for diferente, j� basta para serem diferentes
			resultado = false;
		}
	}

	return resultado;
}

bool Fila::operator!=(Fila fila) {
	bool resultado = true;
	int contIguais = 0;
	for (int i = 0; i < this->CapMax; i++) {
		if (this->Items[i] == fila.Items[i]) { //Conta quantidade de itens iguais
			contIguais++;
		}
	}

	if (contIguais == fila.getNumItens()) { //Se a qtd de itens iguais for a mesma de itens da fila, s�o iguais
		resultado = false;
	}

	return resultado;
}

Fila Fila::operator+(Fila fila) {
	Fila *filaResultante = new Fila(this->getCapacidade()); //Cria fila que conter� o resultado da soma e define suas propriedades iniciais
	filaResultante->CapMax = this->getCapacidade();
	filaResultante->Inicio = 0;
	filaResultante->Fim = -1;
	
	for(int i = 0; i < this->getCapacidade(); i++) {
		float soma = this->Items[i] + fila.Items[i]; //Calcula soma dos itens das duas filas e insere na fila resultante
		filaResultante->inserir(soma);
	}

	return (*filaResultante);
}

ostream& operator<<(ostream& o, Fila& fila) {
	int i, cont;

	cont = 0;

	int f = fila.getFim();

	for (i = fila.getInicio(); cont != fila.getNumItens(); i++) { //Itera de acordo com o numero de itens da fila

		if (i == fila.getCapacidade()) //Se o fim estiver na posi��o 1 e o inicio na 2 por exemplo, ser� necess�rio voltar pro inicio da fila pra terminar
			i = 0;

		if (fila.getItems()[i] == f) {//Se for a ultima posi��o, nao precisa de colocar a virgula
			o << fila.getItems()[i++];
		}
		else {
			o << fila.getItems()[i++] << ", "; //e n�o for, vai precisar de virgula para o proximo n�mero
		}

		if (i == fila.getCapacidade()) //Se o fim estiver na posi��o 1 e o inicio na 2 por exemplo, ser� necess�rio voltar pro inicio da fila pra terminar
			i = 0;

		cont++; //Adiciona item percorrido ao contador

	}

	return o;
}

int main(){
	//Realizar opera��es aqui para testar a fila
	Fila *fila = new Fila(5);
	Fila *fila2 = new Fila(5);
	fila->inserir(1);
	fila2->inserir(2);
	fila->inserir(3);
	fila2->inserir(4);
	cout << "Fila: " << fila;
	getchar();
	
	return 0;
}