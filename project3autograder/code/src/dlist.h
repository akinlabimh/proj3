#ifndef __DLIST_H__
#define __DLIST_H__


/**********************************************************
 * INSTRUCTOR NOTE: Do not modify the class declarations! *
 * The class Dlist is a class template.                   *
 *********************************************************/
class emptyList {
  // OVERVIEW: an exception class
};

template <typename T>
class Dlist {
  // OVERVIEW: contains a double-ended list of Objects

 public:
  // Operational methods

  // EFFECTS: returns true if list is empty, false otherwise
  bool IsEmpty() const;

  // MODIFIES: this
  // EFFECTS: inserts o at the front of the list
  void InsertFront(const T &o);

  // MODIFIES: this
  // EFFECTS: inserts o at the back of the list
  void InsertBack(const T &o);

  // MODIFIES: this
  // EFFECTS: removes and returns last object from non-empty list
  //          throws an instance of emptyList if empty
  T RemoveFront();

  // MODIFIES: this
  // EFFECTS: removes and returns last object from non-empty list
  //          throws an instance of emptyList if empty
  T RemoveBack();

  // Maintenance methods

  Dlist();                                // constructor
  Dlist(const Dlist &l);                  // copy constructor
  Dlist &operator=(const Dlist &l);       // assignment
  ~Dlist();                               // destructor

 private:
  // A private type

  struct node {
    node   *next;
    node   *prev;
    T      o;
  };

  // Private member variables 

  node   *first; // The pointer to the first node (nullptr if none)
  node   *last;  // The pointer to the last node (nullptr if none)

  // Private utility methods

  // EFFECTS: called by constructors to establish empty list invariant
  void MakeEmpty();

  // EFFECTS: called by copy constructor/operator= to copy nodes
  //          from a source instance l to this instance
  void CopyAll(const Dlist &l);
    
  // EFFECTS: called by destructor and operator= to remove and destroy
  //          all list nodes
  void RemoveAll();
};

// Constructor
template <typename T>
Dlist<T>::Dlist() {
  MakeEmpty();
}

// Copy constructor
template <typename T>
Dlist<T>::Dlist(const Dlist &l) {
  MakeEmpty();
  CopyAll(l);
}

// Assignment operator
template <typename T>
Dlist<T>& Dlist<T>::operator=(const Dlist<T> &l) {
  if (this != &l) {
    RemoveAll();
    CopyAll(l);
  }
  return *this;
}

// Destructor 
template <typename T>
Dlist<T>::~Dlist() {
  RemoveAll();
}

/**** INSTRUCTOR NOTE: DO NOT MODIFY ABOVE THIS LINE ****/

/**********************************************************
 * INSTRUCTOR NOTE: Implement the member functions below. *
 * These member functions are all function templates.     * 
 *********************************************************/

// EFFECTS: returns true if list is empty, false otherwise
template <typename T>
bool Dlist<T>::IsEmpty() const {
  return first == nullptr && last == nullptr;
}

// MODIFIES: this
// EFFECTS: inserts o at the front of the list
template <typename T>
void Dlist<T>::InsertFront(const T& o) {
  node* np = new node;
  if (IsEmpty()) {
    last = np;
  } else {
    first->prev = np;   
  }
  np->o = o;
  np->next = first;
  np->prev = nullptr;
  first = np;
}

// MODIFIES: this
// EFFECTS: inserts o at the back of the list
template <typename T>
void Dlist<T>::InsertBack(const T& o) {
  node* np = new node;
  if (IsEmpty()) {
    first = np;
  } else {
    last->next = np;
  }
  np->o = o;
  np->prev = last;
  np->next = nullptr;
  last = np;
}

// MODIFIES: this
// EFFECTS: removes and returns last object from non-empty list
//          throws an instance of emptyList if empty
template <typename T>
T Dlist<T>::RemoveFront() {
  if (IsEmpty()) {
    throw emptyList();
  }
  node* second_np = first->next;
  if (second_np == nullptr) {
    last = nullptr;
  } else {
    second_np->prev = nullptr;
  }
  T o = first->o;
  delete first;
  first = second_np;
  return o;
}

// MODIFIES: this
// EFFECTS: removes and returns last object from non-empty list
//          throws an instance of emptyList if empty
template <typename T>
T Dlist<T>::RemoveBack() {
  if (IsEmpty()) {
    throw emptyList();
  }
  node* second_np = last->prev;
  if (second_np == nullptr) {
    first = nullptr;
  } else {
    second_np->next = nullptr;
  }
  T o = last->o;
  delete last;
  last = second_np;
  return o;
}

// EFFECTS: called by constructors to establish empty list invariant
template <typename T>
void Dlist<T>::MakeEmpty() {
  first = nullptr;
  last = nullptr;
}

// EFFECTS: called by copy constructor/operator= to copy nodes
//          from a source instance l to this instance
template <typename T>
void Dlist<T>::CopyAll(const Dlist &l) {
  for (node *np = l.first; np != nullptr; np = np->next) {
    T o = np->o;
    InsertBack(o);
  }
}

// EFFECTS: called by destructor and operator= to remove and destroy
//          all list nodes
template <typename T>
void Dlist<T>::RemoveAll() {
  while (!IsEmpty()) {
    RemoveFront();
  }
}

/**** INSTRUCTOR NOTE: DO NOT DELETE #endif FROM END OF FILE. ****/
#endif /* __DLIST_H__ */
