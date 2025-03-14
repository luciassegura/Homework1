#include <iostream>
#include <memory>

using namespace std;

struct node {
    void* value;
    shared_ptr<node> next;
};

struct list {
    shared_ptr<node> head;
    weak_ptr<node> tail;
    size_t size = 0; 
};

shared_ptr<node> create_node(void* value){
    auto new_node = make_shared<node>();
    new_node -> value = value;
    return new_node;
}

void push_front(shared_ptr<list> list, void* value){
    auto new_node = create_node(value);
    new_node -> next = list -> head;

    if (!(list -> head)){                   // si no hay elementos en la lista, el nuevo nodo también pasa a ser tail.
        list -> tail = new_node;
    }

    list -> head = new_node;
    list -> size++;
}

void push_back(shared_ptr<list> list, void* value) {
    auto new_node = create_node(value);
    
    auto tail_shared = list -> tail.lock(); // convertir weak_ptr a shared_ptr

    if (!tail_shared) {  // si la lista está vacía
        list -> head = new_node;
        list -> tail = new_node;  // tail sigue siendo weak_ptr, pero ahora apunta a new_node
    } else {
        tail_shared -> next = new_node;
        list -> tail = new_node;  
    }

    list -> size++;
}

void insert(shared_ptr<list> list, void* value, int position){     
    auto new_node = create_node(value);

    if(position >= int(list -> size)){
        push_back(list, value); 
        return;
    } 
    if(position == 0){
        push_front(list,value);
        return;
    }

    auto current = list -> head;

    for (int i = 0; i < position - 1 && current; i++) {
        current = current -> next;
    }
    
    auto next_node = current -> next;
    current -> next = new_node;
    new_node -> next = next_node;

    if (!next_node) {
    list -> tail = new_node;
    }

    list -> size++;
}
void erase(std::shared_ptr<list> list, int position) {
    if (!list || list->size == 0) return;  

    if (position >= int(list -> size)) {  
        position = list -> size - 1;
    }

    auto current = list -> head;
    if (position == 0) {  
        list -> head = list -> head-> next;
    } else {
        for (int i = 0; i < position - 1 && current->next; i++) {
            current = current -> next;
        }
        auto node_to_delete = current -> next;
        current -> next = node_to_delete -> next;

        if (!current -> next) { 
            list -> tail = current;
        }
    }

    list -> size--;
}


void print_list(shared_ptr<list> list){
    shared_ptr<node> current = list -> head;
    while (current) {                       
        cout << *(static_cast<int*>(current -> value)) << " -> ";         // desreferenciar el puntero para poder imprimir
        current = current -> next;
    }
    cout << "Final\n";
}

// Ejemplos para verificwr que funcionen
int main(){
    auto my_list = make_shared<list>(); // inicializar la lista

    int a = 10, b = 20, c = 100, d = 200, e = 300, f = 30, g = 0;
    
    cout << "Insertando al frente:\n";
    push_front(my_list, &a);
    print_list(my_list);
    push_front(my_list, &b);
    print_list(my_list);

    cout << "\nInsertando al final:\n";
    push_back(my_list, &c);
    print_list(my_list);
    push_back(my_list, &d);
    print_list(my_list);

    cout << "\nInsertando en la posición indicada:\n";
    insert(my_list, &e, 10);        // la posición es mayor al largo de la lista, entonces se inserta al final 
    print_list(my_list);
    insert(my_list, &f, 0);         // la posición es la primera, entonces se inserta al principio
    print_list(my_list);
    insert(my_list, &g, 3);
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

// Para compilar y ejecutar
// g++ -std=c++17 -Wall -Wextra -o "Ejercicio 3/ej3" "Ejercicio 3/ej3.cpp"
// cd "Ejercicio 3"
// g++ -std=c++17 -Wall -Wextra -o ej1 ej3.cpp
// ./ej3