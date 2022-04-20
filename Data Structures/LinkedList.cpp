#include <iostream>

using namespace std;

template<typename T>
class List {
private:
    class Node {
	    private:
	        T data;
	        Node* next;

	    public:
	        Node() : data(), next(nullptr){ }
	        
	        Node(T d) : next(nullptr) {
	            data = d;
	        }
	        
	        void setNext(Node* n) {
	            next = n;
	        }
	        
	        Node* getNext(){
	        	return next;
			}
	        
	        T getData(){
	        	return data;
			}
			
			void setData(T n){
				data = n;
			}
        
    };
    
    Node* head;
    Node* tail;
	size_t sz;
    
public:
	// ANCHOR Constructors
    List() : head(nullptr), tail(nullptr), sz() { }
    
    List(T m, T n){
    	Node* nh = new Node(m);
    	Node* nt = new Node(n);
    	head = nh;
    	tail = nt;

    	tail->setNext(nullptr);
    	head->setNext(tail);
    	sz=2;
	}
	
	// ANCHOR Destructors
//	~List(){
//		Node* n = head;
//		
//		while(head != nullptr){
//			n = head;
//			head = head->getNext();
//			delete n;	
//		}
//		
//		head = nullptr;
//		tail = nullptr;
//	}

	// ANCHOR Insert elements methods
    void push_back(T elem){
        Node *x = new Node(elem);
        
        if(tail != nullptr) { tail->setNext(x); } 

        tail = x;
        
        if(head == nullptr) { head = tail; }
		sz++;
    }
    
    void push_back(List<T>* c){
		Node *copy = c->head;
		
		while(copy != nullptr){
			this -> push_back( copy->getData() );
			copy = copy->getNext();	
		}
    }

	void push_back(Node* elem){
		elem->setNext(nullptr);
		if( !notEmpty() ){
			head = elem;
			tail = elem;
		}
		else{
			tail->setNext(elem);
			tail = elem;
		}
		sz++;
	}
    
    void push_front(T elem){
    	Node *x = new Node(elem);
    	
		if(head != nullptr){ x->setNext(head); }		
		
		head = x;
		
		if(tail == nullptr) { tail = head; }
		sz++;
    }
	
	void push_front(List<T>* c){
		Node *copy = c->tail;
		
		while(c->tail != nullptr){	
			this -> push_front( copy->getData() );
			c->pop_back();			
			copy = c->tail;
		}
    }

	void push_front(Node* elem){
		Node * x = head;
		elem->setNext(x);
		if(!notEmpty()){
			head = elem;
			tail = elem;
		}
		else{
			head = elem;
		}
		sz++;
	}

	void insert(T n, size_t pos){
		
		if(notEmpty() && (pos > 0) && (pos < getSize()) ){
			Node* in = new Node(n);
			Node* pre = getIndexDir(pos - 1);
			Node* nx = pre->getNext();
			
			in->setNext(nx);
			pre->setNext(in);
			sz++;		
		}

	}

	// ANCHOR Remove elements methods
	void pop_back(){
		if(tail == head){
			tail = nullptr;
			head = nullptr;
			sz = 0;

		}else if(notEmpty()){
			
			// Obtiene el penultimo nodo, se resta dos por la posicion 0 y la del ultimo
			Node* pre = getIndexDir(getSize() - 2);
			
			// Obtiene el ultimo nodo
			Node* nx = pre->getNext();
			
			tail = pre;
			
			delete nx;
			sz--;
		}
	} 

	void pop_front(){
		if(tail == head){
			tail = nullptr;
			head = nullptr;
			sz = 0;

		}else if(notEmpty()){
			Node* nx = head->getNext();
			
			delete head;
			
			head = nx;
			sz--;
		}
	}
	
	void remove(size_t pos){
		if(notEmpty() && (pos == 0)){
			this -> pop_front();
			
		}else if(notEmpty() && (pos == (getSize() - 1)) ){
			this -> pop_back();
		
		}else if(notEmpty() && (pos > 0 && pos < getSize())){
			Node* pre = getIndexDir(pos - 1);
			Node* nx = pre->getNext();
			Node* nxt = nx->getNext();
			
			pre->setNext(nxt);
			delete nx;
			sz--;
		}

	}

	// ANCHOR Get elements methods
    T getTail(){
    	return (tail) ? tail->getData() : T();
	}
	
	T getHead(){
    	return (head) ? head->getData() : T();
	}
	
	T getByIndex(size_t index){
		Node* print = head;
		for(size_t i = 0; i < index; i++ ){
			print = print->getNext();
		}
		
		return print->getData();	
	}
	
	size_t getSize(){
	 	return sz;
	}

	bool notEmpty(){
		return ((tail != nullptr) && (head != nullptr));
	}

	void print(){
		if( notEmpty() ){
			Node* print = head;
		
			cout << "[ ";
			for(size_t i = 1; i <= getSize(); i++){
				cout << print->getData();
				if( print != tail) cout << " -> ";
				
				print = print->getNext();
			}
			cout << " ]";
		}		
	}
	
	Node* getIndexDir(size_t index){
		if(index == 0){
			return head;
			
		}else if(index == this -> getSize() - 1 ){
			return tail;
			
		}else if(notEmpty() && (index < this -> getSize()) ){
			Node* print = head;
			for(size_t i = 0; i < index; i++ ){
				print = print->getNext();
			}	
			return print;
		}	
		return nullptr;
	}

	// ANCHOR Merge Sort
	void split(List<T> *A, List<T> *B){
		size_t i = 0;
		Node* x = head;

		while(head != nullptr){
			x = head;
			head = head->getNext();
			 
			if(i % 2 == 0){
				A -> push_back(x);
			}else{
				B -> push_back(x);
			}
			
			i++;
		}

		head == nullptr;
		tail == nullptr;
		sz = 0;

	}

	void merge(List<T> *A, List<T> *B){
		Node * xa = A -> head;
		Node * xb = B -> head;

		while(xa != nullptr && xb != nullptr){
			if( xa -> getData() < xb -> getData() ){
				Node *n = xa;
				xa = xa -> getNext();
				this -> push_back(n);
			}else{
				Node *n = xb;
				xb = xb -> getNext();
				this -> push_back(n);
			}
		}

		while(xa != nullptr){
			Node *n = xa;
			xa = xa -> getNext();
			this -> push_back(n);
		}

		while(xb != nullptr){
			Node *n = xb;
			xb = xb -> getNext();
			this -> push_back(n); 
		}	

	}

	void mergesort(){
		if(sz > 1){
			List<T> A;
			List<T> B;

			this -> split(&A, &B);
			
			A.mergesort();
			B.mergesort();
		

			this -> merge(&A, &B);
		}
	}
	
//	Binary Search
	Node* mid_node(Node* start, Node* end){
		if(start == nullptr)
			return nullptr;
		
		Node *fast = start->getNext();
		Node *slow = start;
		
		while(fast != end){
			fast = fast->getNext();
			if(fast != end){
				fast = fast->getNext();
				slow = slow->getNext();
			}
		}
		
		return slow;
	}
	
	Node* binarysearch(T value){
		Node *start = head;
		Node *end = nullptr;
		
		do{
			Node* mid = mid_node(start, end);
			
			if(mid == nullptr)
				return nullptr;
				
			else if(mid->getData() == value)
				return mid;
				
			else if(mid->getData() < value)
				start = mid->getNext();
				
			else if(mid->getData() > value)
				end = mid;
				
		}while(end != nullptr || end != start);
		
		
		return nullptr;
	}
	
};

// ANCHOR Main
int main() {
    List<int> *a = new List<int>;
    
	int Omega = 0, Alpha = 0;
	for(size_t i = 0; i < 15; i++){
		a->push_front(i * 5);
	}
	
// NOTE	Agregar una lista a otra.
 	List<int> *b = new List<int>;
	for(size_t i = 0; i < 30; i++){
		b->push_back(i + 15);
	}
	
	a->push_front(b);
	
	unsigned short int opt = 0;

	while(opt != 11){
		system("CLS");

		cout << "1. Print list" << endl;
		cout << "2. Push back" << endl;
		cout << "3. Push front" << endl;
		cout << "4. Insert" << endl;
		cout << "5. Pop back" << endl;
		cout << "6. Pop front" << endl;
		cout << "7. Delete" << endl;
		cout << "8. MergeSort " << endl;
		cout << "9. Binary search " << endl;
		cout << "Ingrese una opcion del menu : ";
		cin >> opt;

		switch (opt)
		{
			case 1:
				system("CLS");	
				cout << "Tamano : " << a->getSize() << endl;
				cout << "Lista : " << endl;
				a->print();
	
				cout << endl;
				system("PAUSE");
				break;
	
			case 2:
				system("CLS");	
				cout << "Ingresa el dato a ingresar : ";
	
				cin >> Omega;
	
				a->push_back(Omega);
				break;
	
			case 3:
				system("CLS");	
				cout << "Ingresa el dato a ingresar : ";
	
				cin >> Omega;
	
				a->push_front(Omega);
				break;
			
			case 4:
				system("CLS");	
				cout << "Nota : El dato puede no ser ingresado si escribes una posicion erronea." << endl;
				cout << "Ingresa el dato a ingresar : ";
				cin >> Omega;
	
				cout << "Ingresa la posicion : ";
				cin >> Alpha;
	
				a->insert(Omega, Alpha);
				break;
	
			case 5:
				system("CLS");	
				cout << "Se elimino el ultimo dato de tu lista. " << endl;
	
				a->pop_back();
	
				system("PAUSE");	
				break;
	
			case 6:
				system("CLS");	
				cout << "Se elimino el primer dato de tu lista. " << endl;
	
				a->pop_front();
	
				system("PAUSE");	
				break;
	
			case 7:
				system("CLS");	
				cout << "Ingresa la posicion a borrar : ";
				cin >> Omega;
	
				a->remove(Omega);
		
				break;
				
			case 8:
				system("CLS");	
				cout << "Se realizo merge sort en tu lista. " << endl;
				
				
				a->mergesort();
	
				system("PAUSE");	
				break;

			case 9:
				system("CLS");
				cout << "Inserte el valor a buscar : "; 
				cin >> Omega;
				
				cout << "Se encontro " << Omega << " en la direccion " << a->binarysearch(Omega) << "["  << a->binarysearch(Omega)->getData() <<  "]"<< endl;
				
				system("PAUSE");
				
			default:
				break;
		}
	}



	return 0;
	
}

