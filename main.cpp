#include <iostream>
#include <string>

using namespace std;

class CommonErrors {
	private:
		string error;
		
	public: 
	
	CommonErrors(string err){
		error = err;
		this->getCommonError();
	}
		
	getCommonError(){
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
	private:
		int limit;
		int quantity;
		int *arr;
		
	IntVector(){
		limit = 15;
		quantity = 0;
		arr = new int[limit];
	}
	
	push(int value, int position){
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
	
	remove(int position){
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
	
};

class MaxHeap {
	private:
		IntVector *arr;
		
	getParent(int i){
		if(i >= 0){
			return (int((i+1)/2)/-1);
		}
		return -1;
	}
	
	getLeft(int i){
		if(i >= 0 && i < arr->quantity()){
			return 2*i+1;
		}
		return -1;
	}
	
	getRight(int i){
		if(i >= 0 && i < arr->quantity()){
			return 2*i+2;
		}
		return -1;
	}
	
	int getBiggerThanPosition(int i){
		int bigger = i;
		int left = getLeft(i);
		int right = getRight(i);
		
		if(left < arr->quantity() && left >= 0){
			if(arr->get(bigger) < arr->get(left)){
				bigger = left;
			}
		}
		
		if(right < arr->quantity() && right >= 0){
			if(arr->get(bigger) < arr->get(right)){
				bigger = right;
			}
		}
		
		return bigger;
	}
	
	int getHeight(){
		int height = 1;
		int quantity = arr->quantity();
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
		
	public:
		MaxHeap(){
			this->arr = new IntVector();
		}
		
		string print(){
			int height = 0;
			int index = 0;
			for(int i=0; i < height; i++){
				cout << "" << endl;
				for(int j = 0; e < level(i); e++){
					if(index < arr->quantity()){
						arr->get(index);
						index = index + 1;
						if(j < level(i) - 1){
							cout << " " << endl;
						}
					}
				}
			}
		}
};
class Commands{
	private: 
	string cmd; 
	string arg;
	* arr;
	
	Commands(){
		cmd = "";
		arg = "";
	}
	
	void insert(){
		int j;
		if(this->arg != " "){
			while(this->arg >> j){
				arr->insert(j)
			}
		}
	}
	
	void printType(string type){
		if(type =="max"){
			int max = arr->getMax();
			cout << "Max= " << max << endl;
		}else if(type == "all"){
			arr->print();
		}
	}
	
	void dim(){
		
	}
	
	void dimMax(){
		
	}
	
	void removeAll(){
	}
	
	void remove(){
		
	}
	
	void heapifyUp(){
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
			dim();
		}else if(command == "dim_max"){
			dimMax();
		}else if(command == "clear"){
			removeAll();
		}else if(command == "delete"){
			 remove();
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

