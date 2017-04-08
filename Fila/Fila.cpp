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

	int tamanho(); //Retorna quantos itens existem na fila

	Fila &operator+(Fila&); //Soma os valores de cada posição das duas filas

	Fila &operator+(float); //Soma cada posição da fila com o valor float passado

	Fila &operator+=(Fila&); //Soma nas posições da fila os valores da fila passada como parametro

	bool operator==(Fila); //Só serão iguais se tiverem os mesmos elementos na mesma ordem (considerando a ordem dos elementos na fila, e não do vetor de armazenamento).

	bool operator!=(Fila); //O oposto da anterior. Se as filas tiverem tamanhos diferentes, já é possível considerá-las diferentes.

	friend ostream& operator<<(ostream&, Fila&); //Permite que uma fila seja impressa no cout. Mostra os elementos na ordem de saída da fila.

	float operator[](float); //Exibe valor armazenado nessa posição da ordem da fila.

	Fila(const Fila&);
};

Fila::Fila(const Fila& fila)
{
	//Aloca a memória
	Items = new float;

	//Copia valores pro objeto passado
	*Items = *fila.Items;
	CapMax = fila.CapMax;
	Inicio = fila.Inicio;
	NumItens = fila.NumItens;
	Fim = fila.Fim;
}

Fila::Fila(int N) {
	this->CapMax = N; //Define propriedades iniciais de uma fila
	this->Items = new float[N];
	this->Inicio = 0;
	this->Fim = 0;
	this->NumItens = 0;
}

Fila::~Fila() {
	delete[] this->Items; //Libera ponteiro de itens na destruição da classe
}


void Fila::inserir(float item) {
	if (this->Fim == this->CapMax) { //Caso chegue no fim do array da fila, valor final estará na primeira posição dela
		this->Fim = 0;
	}

	(*this).Items[(*this).Fim] = item; //adiciona item a fila
	(*this).Fim++; //Atualiza posicao final da lista
	(*this).NumItens++; //Acresce contador de numero de itens
}

float Fila::retirar() {
	float aux = this->Items[this->Inicio++]; //Pega o valor da posicao e acresce o primeiro

	if ((*this).Inicio == (*this).CapMax) {
		(*this).Inicio = 0;
	}

	(*this).NumItens--; //Retira item do contador

	return aux;
}

bool Fila::vazia() {
	return this->NumItens == 0; //Se o numero de itens for igual a 0, ela está vazia
}

bool Fila::cheia() {
	return this->NumItens == this->CapMax; //Se o num de itens for igual a sua capacidade, está cheia
}

int Fila::tamanho() {
	return this->NumItens; //Retorna o num de itens
}

Fila &Fila::operator+=(Fila& fila) {

	for (int i = 0; i < this->CapMax; i++) {
		this->Items[i] = (*this).Items[(getInicio() + i) % getCapacidade()] + fila.Items[(fila.getInicio() + i) % fila.getCapacidade()]; //Percorre os dois arrays, somando seus valores
	}

	return *this;
}

Fila &Fila::operator+(float num) {
	for (int i = this->getInicio(); i != this->Fim; i++) {
		if (i == (*this).getCapacidade()) //Se o fim estiver na posição 1 e o inicio na 2 por exemplo, será necessário voltar pro inicio da fila pra terminar
			i = 0;

		this->Items[i] = (*this).Items[i] + num; //Percorre os dois arrays, somando seus valores
	}

	return *this;
}

Fila &Fila::operator+(Fila& fila) {

	Fila *filaResultante = new Fila(fila.getNumItens());

	for (int i = 0; i < this->CapMax; i++) {
		(*filaResultante).Items[i] = (*this).Items[(getInicio() + i) % getCapacidade()] + fila.Items[(fila.getInicio() + i) % fila.getCapacidade()]; //Percorre os dois arrays, somando seus valores
	}

	return *this;
}

bool Fila::operator==(Fila fila) {
	bool resultado = true;
	for (int i = 0; i < this->CapMax; i++) {
		if (this->Items[i] != fila.Items[i]) { //Se um número for diferente, já basta para serem diferentes
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

	if (contIguais == fila.getNumItens()) { //Se a qtd de itens iguais for a mesma de itens da fila, são iguais
		resultado = false;
	}

	return resultado;
}

float Fila::operator[](float index) {
	int i, cont = 0;

	//e a fila tiver tamanho igual ou maior ao indice buscado, vai encontrar o numero armazenado nela
	if ((*this).getCapacidade() >= index) {
		for (i = (*this).getInicio(); cont != (*this).getNumItens(); i++) { //Itera de acordo com o numero de itens da fila

			if (i == (*this).getCapacidade()) //Se o fim estiver na posição 1 e o inicio na 2 por exemplo, será necessário voltar pro inicio da fila pra terminar
				i = 0;

			if (i == index) {//Se for a ultima posição, nao precisa de colocar a virgula
				return (*this).getItems()[i];
			}

			cont++; //Adiciona item percorrido ao contador

		}
	}

	return NULL;
}

ostream& operator<<(ostream& o, Fila& fila) {
	int posicao = fila.getInicio();

	for (int i = 0; i < fila.getNumItens(); i++)
	{
		o << fila.getItems()[posicao++ % fila.getCapacidade()];
		if (i != fila.getNumItens() - 1)
		{
			o << ", ";
		}
	}

	return o;
}

int main() {
	Fila *f = new Fila(3);
	Fila *f2 = new Fila(3);
	Fila *f3 = new Fila(3);
	//inserções
	f->inserir(1);
	f->inserir(2);
	f->inserir(3);
	f2->inserir(1);
	f2->inserir(2);
	f2->inserir(3);
	//remoções
	f2->retirar();
	//comparação
	bool ehIgual = (*f2) == (*f);
	cout << ehIgual;
	cout << "\n";
	//somas
	(*f3) = (*f) + (*f2);
	cout << (*f3);
	cout << "\n";
	(*f2) = (*f2) += (*f);
	cout << (*f2);
	cout << "\n";
	cout << (*f);
	getchar();
	return 0;
}