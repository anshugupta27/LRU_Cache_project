#include<iostream>
#include<map>
using namespace std ; 

struct Node {
	int data ; 
	Node * left , * right ; 
	Node ( int data )
	{
		this -> data = data ; 
		left = right = NULL ;
	}
};

class LRUCache {
	private :
	int capacity ; 
	int currentsize ; 
	Node * head , *last ; 
	map<int , Node*> mp ;  // map is key, Node 

    public : // the constructor should be public 
	LRUCache ( int capacity )
	{
		this -> capacity = capacity ; 
		currentsize = 0 ; 
		head = last = NULL ; 
	}

    public : // making this function public so that from outside we can get to know whether this key exists in the map or not 
	string get ( int key )  // if the get does not exists in the map then return -1 otherwise make the key node as the head 
	{
		if ( mp.find(key) == mp.end() or mp[key] -> data == -1 ) return "Not found" ; // return -1 if the key does not exist in the map 


        // if the key exist in the map 
		Node * temp = mp[key] ; // point to that key in the map 
		update ( key , temp -> data ) ; // update the key node as the head node as it is the recently used application
		string s = "found the key = " + to_string ( key ) + " with value = " + to_string ( mp[key] -> data ) ;
		return s ;  // return the recent used application ie. head of the linked list 
	}

   private :  // making this as private because the put and get function can access it internally and outside user does not need it 
	void update ( int key , int value )
	{
		// updating the linked list by putting the node ( key as the map index ) in the front as it is the recently used application
		Node * temp = mp[key] ;
		temp -> data = value ; 
		if ( temp == head ) return ; 
		if ( temp == last ) last = last -> left ; 
		if ( temp -> right ) temp -> right -> left = temp -> left ; 
		if ( temp -> left ) temp -> left -> right =temp -> right ; 
		head -> left = temp ; 
		temp -> right = head ; 
		head = temp ; 
	}

    private :   // delete should be priavte as the put function will automatically detect whether delete is needed or not 
	void Delete () {
		// deleting the least recently used application ie. the last node of the linked list 
		Node * temp = last ; 
		temp -> data = -1 ; 
		last = last -> left ; 
		if ( last == NULL ) head = NULL ; 
		if ( last ) last -> right = NULL ; 
	}

    public : // making this as public as we want to insert applications in the cache hence this function should be accessible outside 
	void put ( int key , int value ) // putting a new application in the cache
	{
		// if the key exists in the map 
		if ( mp.find( key ) != mp.end() and mp[key] -> data != -1 )
		{
           update ( key , value ) ; // update this key as the head or receently used application
           return ; 
		}
     
        // if there is no space to store the current application then delete the last node ( least recently used application )
		if ( currentsize == capacity )
		{
			Delete() ; 
			currentsize-- ; 
		}
		// creating new node 
		currentsize++ ; 
		Node * ptr = new Node ( value ) ;
		mp[key] = ptr ;

		if ( !head ) // if no head then make ptr as the new head 
		{
			head = ptr ; 
			last = ptr ; 
		}
		else  // if head already exists then push the ptr in front of the nead and make ptr as new head as it is the recently used application
		{
			head -> left = ptr ; 
			ptr -> right = head ; 
			head = ptr ; 
		}

	}

	void printCache ()
	{
		Node * temp = head ; 
		while ( temp )
		{
          cout << temp -> data << " -> " ;
          temp = temp -> right ; 
		}
		cout << "NULL" ;
	}



};

int main ()
{
	// only get and put functions are available from main 

	LRUCache lru(6) ;   // initializing the size of cache as 6  

	// ***** inserting some applications in the cache ***** 
	lru.put ( 1 , 10 ) ;
	lru.put ( 2 , 20 ) ;
	lru.put ( 3 , 30 ) ;
	lru.put ( 4 , 40 ) ; 
	lru.put ( 5 , 50 ) ;
	lru.put ( 6 , 60 ) ;  // most recently used 

	// above this the size of the cache is filled to 6 hence adding one more application then the least recently used application will get deleted from cache ie.10 and the 70 will get added as the head ie. the recently used application
	lru.put ( 7 , 70 ) ; 
	cout << "\n" ;
	lru.printCache() ;
    cout << "\n\n" ;

    // as the key 2 already exists in the cache hence make it as the head e. recently used application 
	cout << "searching for the key = 2 \n" ;
	cout << lru.get ( 2 ) << "\n" ;
	lru.printCache() ;
    cout << "\n\n" ;
    cout << "searching for the key = 1 \n" ;
	cout << lru.get( 1 ) << "\n" ;
	lru.printCache() ;


}
