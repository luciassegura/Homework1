#include <iostream>
#include <memory>

using namespace std;

struct node {                   // define la estructura del nodo que tiene un valor y un puntero a next
    int value;
    shared_ptr<node> next;
};

struct list {                       // define la estructura de la lista que tiene un size, un puntero a head y otro a tail
    shared_ptr<node> head;
    weak_ptr<node> tail;
    size_t size = 0; 
};

shared_ptr<node> create_node(int value){              // crea el nodo y le asigna el valor correspondiente
    auto new_node = make_shared<node>();
    new_node -> value = value;
    return new_node;
}

void push_front(shared_ptr<list> list, int value){   // inserta un elemento al principio
    auto new_node = create_node(value);                // crea el nodo
    new_node -> next = list -> head;                // asigna el next de new_node 

    if (list -> head == nullptr){                   // si no hay elementos en la lista, el new_node también pasa a ser tail.
        list -> tail = new_node;
    }

    list -> head = new_node;
    list -> size++;
}

void push_back(shared_ptr<list> list, int value){        // inserta un elemento al final
    auto new_node = create_node(value);                    // crea el nodo
    
    auto tail_shared = list -> tail.lock(); // convertir weak_ptr a shared_ptr (con .lock) mientras todavía exista 

    if (tail_shared == nullptr) {  // si la lista está vacía
        list -> head = new_node;   // new_node es head
        list -> tail = new_node;  // y tail que sigue siendo weak_ptr,
    } else {
        tail_shared -> next = new_node;         // si no está vacía se agrega new_node
        list -> tail = new_node;  
    }

    list -> size++;
}

void insert(shared_ptr<list> list, int value, int position){     // inserta un elemento en la posición indicada
    auto new_node = create_node(value);                           // crea el nodo

    if(position >= int(list -> size)){              // si la posición es mayor al largo de la lista, lo inserta al final
        push_back(list, value); 
        return;
    } 
    if(position == 0){                              // si la posición es 0, lo inserta al principio
        push_front(list,value);
        return;
    }

    auto current = list -> head;

    for (int i = 0; i < position - 1 && current; i++){      // recorre la lista hasta llegar a la posición -1
        current = current -> next;
    }
                                                 // cuando está en posición -1 
    auto next_node = current -> next;           // guardo el próximo 
    current -> next = new_node;                 // el próximo es el nuevo
    new_node -> next = next_node;               // actualiza el próximo del nuevo

    if (next_node == nullptr) {
    list -> tail = new_node;
    }

    list -> size++;
}

void erase(shared_ptr<list> list, int position) {           // borra el elemento de la posición indicada
    if (list == nullptr || list -> size == 0) return;       // si la lista está vacía no hace nada

    if (position >= int(list -> size)) {        // si la posición es mayor que el largo de la lista
        position = list -> size - 1;            // actualizo la posición a la última de la lista
    }

    auto current = list -> head;                
    if (position == 0) {  
        list -> head = list -> head-> next;
    } else {
        for (int i = 0; i < position - 1 && current -> next; i++) {
            current = current -> next;
        }
        auto node_to_delete = current -> next;
        current -> next = node_to_delete -> next;

        if (current -> next == nullptr) { 
            list -> tail = current;
        }
    }

    list -> size--;
}

void print_list(shared_ptr<list> list){                 // imprime los valores de la lista
    shared_ptr<node> current = list -> head;
    while (current) {                       
        cout << current -> value<< " -> ";         // desreferenciar el puntero para poder imprimir
        current = current -> next;
    }
    cout << "Final\n";
}

// Ejemplos para verificar 
int main(){
    auto my_list = make_shared<list>(); // inicializar la lista

    int a = 10, b = 20, c = 100, d = 200, e = 300, f = 30, g = 0;
    
    cout << "Insertando al principio:\n";
    push_front(my_list, a);
    print_list(my_list);
    push_front(my_list, b);
    print_list(my_list);

    cout << "\nInsertando al final:\n";
    push_back(my_list, c);
    print_list(my_list);
    push_back(my_list, d);
    print_list(my_list);

    cout << "\nInsertando en la posición indicada:\n";
    insert(my_list, e, 10);        // la posición es mayor al largo de la lista, entonces se inserta al final 
    print_list(my_list);
    insert(my_list, f, 0);         // la posición es la primera, entonces se inserta al principio
    print_list(my_list);
    insert(my_list, g, 3);
    print_list(my_list);

    cout << "\nEliminando en la posición indicada:\n";
    erase(my_list, 10);        // la posición es mayor al largo de la lista, entonces se elimina al final
    print_list(my_list);
    erase(my_list, 0);         // la posición es la primera, entonces se elimina al principio
    print_list(my_list);
    erase(my_list, 2);
    print_list(my_list);    

    return 0;
}