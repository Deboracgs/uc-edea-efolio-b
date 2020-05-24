#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class CommonErrors {
	private:
		string error;
		
	public: 
	
	CommonErrors(string err){
		error = err;
		this->getCommonError();
	}
		
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
class IntVector {
	public:
		int limit;
		int quantity;
		int *arr;
		
	IntVector(){
		limit = 15;
		quantity = 0;
		arr = new int[limit];
	}
	
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
		
	int limits(){
		return this->limit;
	}
	
	int length(){
		return this->quantity;
	}
	
	int get(int i){
		if(i < this->limit && i >=0){
			return this->arr[i];
		}else {
			return -1;
		}
		
	}
	
	bool change(int v, int i){
		if(i >= 0 && this->quantity < i){
			this->arr[i] = v;
			return true;
		}else{
			return false;
		}
		
	}
	
	bool push(int n){
		if(this->quantity < this->limit){
			this->arr[this->quantity] = n;
			this->quantity = this->quantity + 1;
			return true;
		}
		
		return false;
	}
	
	void init(){
		for(int i = 0; i < this->limit; i++){
			change(-1, i);
		}
	}
	
};

class MaxHeap {

	public: 
	IntVector *arr;
	
	MaxHeap(){
		this->arr = new IntVector();
	}
		
	int getParent(int i){
		if(i >= 0){
			return (int((i+1)/2)/-1);
		}
		return -1;
	}
	
	int getLeft(int i){
		if(i >= 0 && i < arr->length()){
			return 2*i+1;
		}
		return -1;
	}
	
	int getRight(int i){
		if(i >= 0 && i < arr->length()){
			return 2*i+2;
		}
		return -1;
	}
	
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
	
	int getHeight(){
		int height = 1;
		int quantity = arr->length();
		while((quantity / 2) > 0){
			height = height + 1;
		}
		
		return height;
	}
	
	int getLevel(int i){
		int elements = 1;
		for(int j=0; j<i; j++){
			elements = elements * 2;
		}
		return elements;
	}
		
	void print(){
		int height = 0;
		int index = 0;
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
				
	bool push(int n){
		if(this->arr->push(n) != false){				
			return true;
		}else{
			return false;
		}
	}
	
	int getByPosition(int i){
		return 	arr->get(i);
	}
	
	void reboot(){
		if(arr->quantity > 0){
			arr->quantity = 0;
			arr->init();
		}
	}
	
	int get(int i){
		return arr->get(i);
	}
	
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
	
	int limits(){
		return arr->limits();
	}
	
	int quantity(){
		return arr->length();
	}

};
class Commands{
	private: 
	string cmd; 
	string arg;
	MaxHeap * arr;

	
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
	
	void printType(string type){
		if(type =="max"){
			int max = arr->get(0);
			cout << "Max= " << max << endl;
		}else if(type == "all"){
			arr->print();
		}
	}
	
	void dim(string type){
		if(type == "max"){
			cout << arr->limits() << endl;
		}else if(type == "all"){
			cout << arr->quantity() << endl;
		}
	}
	
	
	void remove(string type){
		if(type ==  "all"){
			arr->reboot();
		}else if(type == "one"){
			arr->remove();
		}
	}
	
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
	
	void redimMax(){
		
	}
	
	public:
	Commands(string command, string argument){
		this->cmd = command;
		this->arg = argument;
	}
	
	~Commands(){
		this->cmd = "";
		this->arg = "";
	}
	
	void setArg(string arg){
		this->arg = arg;
	}

	void setCmd(string cmd){
		this->cmd = cmd;
	}
	

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
	Commands *command = new Commands("", "");
    while(getline(cin, entry)){
        if(entry.substr(0,1) == "#" || entry == ""){
        	continue;
		}
		int position = entry.find(" ");
		string cmd  = entry.substr(0, position);
		string arg = "";
		
		if(position != -1){
			arg = entry.substr(position, entry.size());
		}
		
		command->setArg(arg);
		command->setCmd(cmd);
		command->getCommand();
		
    }

    system("pause");
    return 0;
}

