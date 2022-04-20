#include <iostream>
#include <cmath>

using namespace std;

template <typename T>
class Vector{
	private:
		T* storage;
		size_t sz;
		size_t cap;
		
		void resize(){
			T *ns = new T[cap + 1];
						
			for(size_t i = 0; i < cap; i++){
				ns[i] = storage[i];
			}
			
			delete [] storage;
			storage = ns;
			cap ++;
		}

		
		void ensure(size_t n){
			
			if( n > available() ){
				int newcap = n - available();
				
				T*ns = new T[cap + newcap];
				
				for(size_t i = 0; i < sz; i++){
					ns[i] = storage[i];
				}
				
				delete [] storage;
				storage = ns;
				
				
				cap += newcap;
			}
			
		}
		
		
	public:
		Vector(){
			storage = new T[2];
			sz = 0;
			cap = 2;	
		}
		
		Vector(size_t n){
			storage = new T[n];
			sz = 0;
			cap = n;	
		}
		
		~Vector(){
			delete [] storage;
		}
		
		size_t capacity(){
			return cap;
		}
		
		size_t size(){
			return sz;
		}
		
		size_t available(){
			return cap - sz;
		}
		
		void push_back(T elem){
			if(sz == cap){ resize(); }
			storage[sz] = elem;
			sz++;
			
		}
		
		void push_back(Vector <T> other){
			this -> ensure( other.size() );
			
			for(size_t i = 0; i < other.size(); i++ ){
				this -> push_back( other.getStorage(i) );
			}
		}
		
		void push_front(T elem){
			if(sz == cap){ resize(); }

			size_t i = size();
		
			while(i > 0){
				storage[i] = storage[i - 1];
				i--;
			}

			storage[0] = elem;
			sz++;
		}
		
		void push_front(Vector<T> other){
			this -> ensure( other.size() );
			
			size_t i = cap;
			
			while(i > (other.size() - 1) ) {
				storage[i] = storage[ i - other.size() ];
				i--;
			}
			
			i = 0;
			
			while(i < other.size() ){
				storage[i] = other.getStorage(i);
				i++;
			}
			
			sz+= other.size();
		} 
		
		void print(){
			cout << "Contenido del vector [ ";
			for(size_t i = 0; i < size(); i++ ){
				cout << storage[i] << " ";
			}
			cout << " ]";
			
		}
		
		void pop_back() {
			sz--;
		}
		
		void pop_front() {
			int i = 0;
		
			while(i < size()){
				storage[i] = storage[i + 1];
				i++;
			}
			
			sz--;
		}
		
		void insert(T elem, size_t pos) {
			if(sz == cap){ resize(); }

			int i = size();
		
			while(i > pos){
				storage[i] = storage[i - 1];
				i--;
			}

			storage[pos] = elem;
			sz++;
		}
		
		void remove(size_t pos) {
			int i = pos;
		
			while(i < size()){
				storage[i] = storage[i + 1];
				i++;
			}
			
			sz--;
		}
		
		T getStorage(size_t pos){
			return storage[pos];
		}
		
		void insert(Vector<T> other, size_t pos) {
			this -> ensure( other.size() + 1);
			
			int i = size() + other.size();
			
			// Mueve los elementos, para dejar los espacios libres
			while(i > pos){
				storage[i] = storage[i - other.size()];
				i--;
			}
			
			sz += other.size();

			//Agrega los elementos del vector other al principal
			int j = pos;
			i = 0;
			
			while( i < other.size() ) {
				
				storage[j] = other.getStorage(i);
				
				i++;
				j++;
			}

		}
		
		
//		Bubble Sort O( n^2 )
		void BubbleSort(){
			int temp = 0;
			for(size_t i = 0; i < size() - 1; i++){
				bool Swaped = false; 
				
				for(size_t j = 0; j < size() - i - 1; j++){
					if(storage[j] > storage[j + 1]){
						temp = storage[j];
						storage[j] = storage[j + 1];
						storage[j + 1] = temp;
						
						Swaped = true;		
					}
				}
	
				
				if(Swaped == false) break;
				

			}
			
		}
		
//		Heap Sort O ( n log n )
		void heapify(int n, int i)
		{
		    int largest = i; // Initialize largest as root
		    int l = 2 * i + 1; // left = 2*i + 1
		    int r = 2 * i + 2; // right = 2*i + 2
		 
		    // If left child is larger than root
		    if (l < n && storage[l] > storage[largest])
		        largest = l;
		 
		    // If right child is larger than largest so far
		    if (r < n && storage[r] > storage[largest])
		        largest = r;
		 
		    // If largest is not root
		    if (largest != i) {
		        swap(storage[i], storage[largest]);
		 
		        // Recursively heapify the affected sub-tree
		        heapify(n, largest);
		    }
		    
		}

		void HeapSort(){
			
			// Build heap (rearrange array)
		    for (int i = size() / 2 - 1; i >= 0; i--)
		        heapify(size(), i);
		 
		    // One by one extract an element from heap
		    for (int i = size() - 1; i > 0; i--) {
		        // Move current root to end
		        swap(storage[0], storage[i]);
		 
		        // call max heapify on the reduced heap
		        heapify(i, 0);
		    }  
			
		}		
		
//		Quick Sort
	void swap(T *a, T *b){
		T temp = *a;
		*a = *b;
		*b = temp; 
	}
	
	int particion(int inicio, int final){
	    int pivote = storage[inicio];
	    int i = inicio - 1;
    	for (int j = i; j < final; j++){
        	if(storage[j] < pivote){
            	swap(&storage[i], &storage[j]);
            	i++;
			} 
		}
	    swap(&storage[i + 1], &storage[final]);
	    return i + 1;
	}
    
    
	void quick(int inicio, int final){
	    if(inicio < final){
			int pivote = particion(inicio, final);

			quick(inicio, pivote-1);
			quick(pivote+1, final);
		}
	}

	void quicksort(){
		quick(0, size());
	} 
	
//	Binary search
	size_t binarysearch(size_t l, size_t r, T value){
		if(r >= 1){
			size_t mid = l + ( r - 1 ) / 2;
			
			if(storage[mid] == value)
				return mid;
				
			else if(storage[mid] < value) 
				return binarysearch(mid, r, value);
				
			else if(storage[mid] > value)
				return binarysearch(l, mid, value);
		}
		
		return -1;
	}
		
};

int main(){
	unsigned short int opt = 0;
	Vector<double> V; 
	Vector<double> O;
	
	for(double i = 0; i < 15; i++){
		V.push_back(80 - i);
	}
	
	V.print();
	V.quicksort();
	cout << endl;
	V.print();
	cout << V.binarysearch(0, V.size(), 80) << endl;
	
	
	return 0;
}


// Vectores dinamicos.

/*
	assign	Erases a vector and copies the specified elements to the empty vector.
	at	Returns a reference to the element at a specified location in the vector.
	back	Returns a reference to the last element of the vector.
	begin	Returns a random-access iterator to the first element in the vector.
	capacity	Returns the number of elements that the vector could contain without allocating more storage.
	cbegin	Returns a random-access const iterator to the first element in the vector.
	cend	Returns a random-access const iterator that points just beyond the end of the vector.
	crbegin	Returns a const iterator to the first element in a reversed vector.
	crend	Returns a const iterator to the end of a reversed vector.
	clear	Erases the elements of the vector.
	data	Returns a pointer to the first element in the vector.
	emplace	Inserts an element constructed in place into the vector at a specified position.
	emplace_back	Adds an element constructed in place to the end of the vector.
	empty	Tests if the vector container is empty.
	end	Returns a random-access iterator that points to the end of the vector.
	erase	Removes an element or a range of elements in a vector from specified positions.
	front	Returns a reference to the first element in a vector.
	get_allocator	Returns an object to the allocator class used by a vector.
	insert	Inserts an element or many elements into the vector at a specified position.
	max_size	Returns the maximum length of the vector.
	pop_back	Deletes the element at the end of the vector.
	push_back	Add an element to the end of the vector.
	rbegin	Returns an iterator to the first element in a reversed vector.
	rend	Returns an iterator to the end of a reversed vector.
	reserve	Reserves a minimum length of storage for a vector object.
	resize	Specifies a new size for a vector.
	shrink_to_fit	Discards excess capacity.
	size	Returns the number of elements in the vector.
	swap	Exchanges the elements of two vectors.
	
	link : https://docs.microsoft.com/en-us/cpp/standard-library/vector-class?view=msvc-170
	
	
*/
