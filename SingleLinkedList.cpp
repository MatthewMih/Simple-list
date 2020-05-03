#include <iostream>

template<typename T>
struct Node{
  T value;
  Node<T>* next;
  Node<T>(T value): value(value), next(nullptr) {}
};

template<typename T>
class MyList{
public:
  Node<T>* head;
    
  MyList<T>(): head(nullptr) {}
  
  MyList<T>(T value){
    head = new Node<T>(value);
  }
  
  void DeleteAllNodes(){
    Node<T>* current_node = head;
    while (current_node != nullptr){
      Node<T>* temp = current_node->next;
      delete current_node;
      current_node = temp;
    }
    head = nullptr;
  }

  ~MyList<T>(){
    DeleteAllNodes();
  }
  
  void AddHeadElem(T value){
    Node<T>* new_node = new Node<T>(value);
    new_node->next = head;
    head = new_node;
  }
  
  void AddAtPosition(T value, std::size_t position = 0){ //position = 0 (head), 1, 2, 3, ...
    if (position  == 0)                             
      AddHeadElem(value);
    else{
      std::size_t k = 0; 
      Node<T>* current_node = head;
      while ((k < position - 1) && (current_node != nullptr)){
        k++;
        current_node = current_node->next;
      }
      Node<T>* temp = current_node->next;
      current_node->next = new Node<T>(value);
      current_node->next->next = temp;
    }
  }

  void RemoveHeadElement(){
    if (head != nullptr){
      Node<T>* temp = head->next;
      delete head;
      head = temp;
    }
  }

  void RemoveAtPosition(std::size_t position = 0){ //position = 0, 1, 2, ...
    if (position == 0)
      RemoveHeadElement();
    else{
      std::size_t k =0;
      Node<T>* current_node = head;
      while ((k < position - 1) && (current_node != nullptr)){
        k++;
        current_node = current_node->next;
      }
      if (current_node != nullptr){
        if (current_node->next != nullptr){
          Node<T>* temp = current_node->next->next;
          delete current_node->next;
          current_node->next = temp;
        }
        else{
          delete current_node->next;
          current_node->next = nullptr; 
        }
      }
    }
  }

  MyList<T>& operator=(const MyList<T>& other){
    DeleteAllNodes();    
    if (other.head != nullptr){
      head = new Node<T>(other.head->value);
      Node<T>* current_node1 = head;
      Node<T>* current_node2 = other.head;
      while (current_node2->next != nullptr){
        current_node1->next = new Node<T>(current_node2->next->value);
        current_node1 = current_node1->next;
        current_node2 = current_node2->next;
      }
    }
  }
  
  MyList<T>(const MyList<T> &other){
    head = nullptr;
    this->operator=(other);
  }
};

void print(MyList<int> list){ // furction for printing int-lists
  Node<int>* current = list.head;
  while (current != nullptr){
    std::cout << current->value << std::endl;
    current = current->next;
  }
}
int main(void){
  MyList<int> list(5); //list now: (5)
  list.AddHeadElem(10); //list now: (10, 5)
  list.AddAtPosition(100, 0); //(100, 10, 5)
  list.AddAtPosition(128, 3); //(100, 10, 5, 128)
  list.RemoveHeadElement(); //(10, 5 , 128)
  list.RemoveAtPosition(1); //(10, 128)
  
  MyList<int> new_list;
  new_list = list; //new_list now: (10, 128)
  list.DeleteAllNodes(); //korrektno rabotaet: ne izmenyaet new_list:
  print(new_list); //vidno, chto pri udalenii list'a new_list ne izmenilsya -- operator = rabotayet korrektno
  return 0;
}
