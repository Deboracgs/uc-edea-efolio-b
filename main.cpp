#include <iostream>
#include <string>
#include <sstream>

using namespace std;

// classe para exibi errors
class CommonErrors {
	private:
		string error;
		
	public: 
	
	// construtor
	CommonErrors(string err){
		error = err;
		this->getCommonError();
	}
	
	// função para pegar o erro pela key	
	void getCommonError(){
		string error = this->error;
	   	if(error =="invalid_command_error") {
		   	cout << "Invalid command "  << endl;
	    }else if(error == "invalid_number_error"){
	    	cout << "Invalid number "   << endl;
		}else if(error == "exceed_size"){
			cout << "Excedido a quantidade de itens";
		}else if(error =="not_find"){
			cout << "Item "  << " nao encontrado " << endl;
		}else if(error == "invalid_position"){
			cout << "Posicao invalida";
		}else if("empty_list"){
	    	cout << "Lista vazia " << endl;
	    }
	}
};

//classe de vetor do tipoo int
class IntVector {
	public:
		int limit;
		int quantity;
		int *arr;
		
	// construtor
	IntVector(){
		limit = 15;
		quantity = 0;
		arr = new int[limit];
	}
	
	//  insere valor na ultima posição vazia
	bool push(int n){
		if(this->quantity < this->limit){
			this->arr[this->quantity] = n;
			this->quantity = this->quantity + 1;
			return true;
		}
		
		return true;
	}
	
	// insere o valor no array na posição informada
	void push(int value, int position){
		if(position >= 0 ){
			if(position < limit){
				if(quantity <= limit){
					for(int i = limit; i >= position; i--){
						arr[i+1] = arr[i];
					}
					arr[position] = value;
					quantity = quantity + 1;
				}else{
					new CommonErrors("exceed_size");
				}
				
			}else{
				new CommonErrors("invalid_position");
			}
		
		}else {
			new CommonErrors("invalid_position");
		}
	}
	// remove item no array pela posição informada
	void remove(int position){
		if(position >= 0 ){
			if(position < limit){
				
				arr[position] = -1;
				quantity = quantity - 1;
			}else{
				new CommonErrors("invalid_position");
			}
		
		}else {
			new CommonErrors("invalid_position");
		}
	}
	
	// pega a quantidade limite do array
	int limits(){
		return this->limit;
	}
	
	// pega a quantitdade total que esta no array
	int length(){
		return this->quantity;
	}
	
	// pega o item no array pela posição
	int get(int i){
		if(i < this->limit && i >=0){
			return this->arr[i];
		}else {
			return -1;
		}
		
	}
	
	// altera o valor de uma posição
	bool change(int v, int i){
		if(i >= 0 && this->quantity < i){
			this->arr[i] = v;
			return true;
		}else{
			return false;
		}
		
	}
	
	// inicia com valores negativos/vazios
	void init(){
		for(int i = 0; i < this->limit; i++){
			change(-1, i);
		}
	}
	
};

// class maxheap
class MaxHeap {

	public: 
	IntVector *arr;
	
	// construtor que inicializa com um vetor
	MaxHeap(){
		this->arr = new IntVector();
	}
		
	// pega a posição pai
	int getParent(int i){
		if(i >= 0){
			return (int((i+1)/2)/-1);
		}
		return -1;
	}
	
	// pega a posição esquerda
	int getLeft(int i){
		if(i >= 0 && i < arr->length()){
			return 2*i+1;
		}
		return -1;
	}
	
	// pega a posição direita
	int getRight(int i){
		if(i >= 0 && i < arr->length()){
			return 2*i+2;
		}
		return -1;
	}
	
	// pega o maior na esquerda ou direita, baseado no pai
	int getBiggerThanPosition(int i){
		int bigger = i;
		int left = getLeft(i);
		int right = getRight(i);
		
		if(left < arr->length() && left >= 0){
			if(arr->get(bigger) < arr->get(left)){
				bigger = left;
			}
		}
		
		if(right < arr->length() && right >= 0){
			if(arr->get(bigger) < arr->get(right)){
				bigger = right;
			}
		}
		
		return bigger;
	}
	
	// pega altura da arvore
	int getHeight(){
		int height = 1;
		int quantity = arr->length();
		bool check = (quantity / 2) > 0;
		while(check){
			height = height + 1;
			if(height > quantity){
				return false;
			}
				
		}
		return height;
	}
	
	
	// pega o nivel da arvore
	int getLevel(int i){
		int elements = 1;
		for(int j=0; j<i; j++){
			elements = elements * 2;
		}
		return elements;
	}
	
	// exibe a arvore	
	void print(){
		cout << "chega aqui" << endl;
		int height = this->getHeight();
		int index = 0;
		cout << "height" << height  << endl;
		for(int i=0; i < height; i++){
			cout << "" << endl;
			for(int j = 0; j < this->getLevel(i); j++){
				if(index < arr->length()){
					arr->get(index);
					index = index + 1;
					if(j < this->getLevel(index) - 1){
						cout << " " << endl;
					}
				}
			}
		}
	}
	
	
	// muda a posição do elemento i com o elemento j
	bool changePosition(int i, int j){
		int quantity = arr->length();
		if(quantity > i && quantity < j){
			int elementI = arr->get(i);
			int elementJ = arr->get(j);
			
			arr->change(elementJ, i);
			arr->change(elementI, j);
				
			return true;
		}else{
			return false;
		}
	}
	
	// muda a posição da arvore conforme o valor que for inserido
	bool orderInsert(int i){
		if(i >= 0){
			int j = this->getParent(i);
			if(j != -1){
				if(arr->get(j) < arr->get(i)){
					changePosition(i, j);
					orderInsert(j);					
				}
			}
			return true;
		}else{
			return false;
		}		
	}

	// muda a posição da arvore conforme o valor for deletado
	bool orderDelete(int i){
		if(i >= 0){
			int j = this->getBiggerThanPosition(i);
			if(j != i){
				if(arr->get(j) < arr->get(i)){
					changePosition(i, j);
					orderDelete(j);					
				}
			}
			return true;
		}else{
			return false;
		}		
	}
	
	// insere no vetor e o retorno do vetor for true foi inserido	
	bool push(int n){
		return arr->push(n);
	}
	
	// pega a valor pela posição
	int get(int i){
		return 	arr->get(i);
	}
	
	// reinicia o vetor 
	void reboot(){
		if(arr->quantity > 0){
			arr->quantity = 0;
			arr->init();
		}
	}
	
	// remove o valor 
	void remove(){
		if(arr->quantity > 0){
			if(arr->quantity == 1){
				int position = this->arr->quantity - 1;
				this->arr->change(-1, position);
				arr->quantity = arr->quantity - 1;
			}else{
				int position = arr->quantity - 1;
				int value = this->get(position);
				this->arr->change(value, 0);
				this->arr->change(-1, position);
				arr->quantity = arr->quantity - 1;
			}
		}
	}
	
	// retorno a quantidade total
	int limits(){
		return arr->limits();
	}
	
	// retorna a quantidade atual
	int quantity(){
		return arr->length();
	}

};
class Commands{
	private: 
	string cmd; 
	string arg;
	MaxHeap * arr;

	// insere o valor no vetor
	void insert(){
		int j;
		string arg2 = this->arg;
		if(arg2 != " "){
			istringstream iss(arg2);
			while(iss >> j){
				arr->push(j);
			}
		}
	}
	
	// imprime pelo tipo, se for max vai imprimir o maior valor na arvore, se for all imprime a arvore	
	void printType(string type){
		if(type =="max"){
			int max = arr->get(0);
			cout << "Max= " << max << endl;
		}else if(type == "all"){
			cout << type << endl;
			arr->print();
		}
	}
	
	// exibe a dimensão do vetor, se for max mostra a quantidade maxima dentro do vetor, se for all mostra a quantidade atual
	void dim(string type){
		if(type == "max"){
			cout << arr->limits() << endl;
		}else if(type == "all"){
			cout << arr->quantity() << endl;
		}
	}
	
	// remove do vetor, se for all remove tudo, se for one vai remover o ultimo valor 
	void remove(string type){
		if(type ==  "all"){
			arr->reboot();
		}else if(type == "one"){
			arr->remove();
		}
	}
	
	// funcao heapifyup vai reiniciar a ordem no vetor
	void heapifyUp(){
		int h;
		if(this->arg !=" "){
			IntVector * temp = new IntVector();
			int count = 0;
			istringstream j(this->arg);
			while(j >> h){
				count++;
				
			}
		}
	}
	
	// redimensiona o vetor
	void redimMax(){
		
	}
	
	public:
	Commands(string command, string argument){
		this->cmd = command;
		this->arg = argument;
		this->arr = new MaxHeap();
	}
	

	// seta o argumento recebido
	void setArg(string arg){
		this->arg = arg;
	}

	// seta o commando recebido
	void setCmd(string cmd){
		this->cmd = cmd;
	}
	
	// pega o comendo pela key
	void getCommand(){
		string command = this->cmd;
		if(command == "insert"){
			 insert();
		}else if(command == "print_max"){
			printType("max");
		}else if(command == "print"){
			printType("all");
		}else if(command == "dim"){
			dim("all");
		}else if(command == "dim_max"){
			dim("max");
		}else if(command == "clear"){
			remove("all");
		}else if(command == "delete"){
			 remove("one");
		}else if(command == "heapify_up"){
			heapifyUp();
		}else if(command == "redim_max"){
			redimMax();
		}else{
			new CommonErrors("invalid_command_error");
		}
	}

};

int main()
{
	string entry;
	// inicializa o comando
	Commands *command = new Commands("", "");
	// enquanto tiver recebido um comando ira executar o restante
    while(getline(cin, entry)){
    	
    	// pelo facto do hackerrank ter strings alem dos comandos, e necessario colocar isto
        if(entry.substr(0,1) == "#" || entry == ""){
        	continue;
		}
		// encontra a primeira posição que tem um espaço
		int position = entry.find(" ");
		// pega o comando pela posição
		string cmd  = entry.substr(0, position);
		string arg = "";
		
		// verifica se a posição existe
		if(position != -1){
			// se existir é por que tem argumentos 
			arg = entry.substr(position, entry.size());
		}
		
		// seta o argumento no construtor 
		command->setArg(arg);
		// seta o comando no construtor 
		command->setCmd(cmd);
		// pega o comando
		command->getCommand();
		
    }

    return 0;
}

