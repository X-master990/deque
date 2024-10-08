// list standard header

#ifndef LIST
#define LIST

template< typename ValueType >
struct ListNode // list node
{
   ListNode *next;  // successor node, or first element if head
   ListNode *prev;  // predecessor node, or last element if head
   ValueType myVal; // the stored value, unused if head
};


// CLASS TEMPLATE ListVal
template< typename Ty >
class ListVal
{
public:
   using node = ListNode< Ty >;
   using nodePtr = node *;

   using value_type = Ty;
   using size_type = size_t;
   using difference_type = ptrdiff_t;
   using pointer = value_type *;
   using const_pointer = const value_type *;
   using reference = value_type &;
   using const_reference = const value_type &;

   ListVal() // initialize data
      : myHead(),
        mySize( 0 )
   {
   }

   nodePtr myHead; // pointer to head node
   size_type mySize; // number of elements
};


// CLASS TEMPLATE list
template< typename Ty >
class list // bidirectional linked list
{
   using node = ListNode< Ty >;
   using nodePtr = node *;
   using ScaryVal = ListVal< Ty >;

public:
   using value_type = Ty;
   using size_type = size_t;
   using difference_type = ptrdiff_t;
   using pointer = value_type *;
   using const_pointer = const value_type *;
   using reference = value_type &;
   using const_reference = const value_type &;

   using iterator = node *;
   using const_iterator = const node *;

   // empty container constructor (default constructor)
   // Constructs an empty container, with no elements.
   list()
      : myData()
   {
      myData.myHead = new node;
      myData.myHead->myVal = Ty();
      myData.myHead->prev = myData.myHead->next = myData.myHead;
   }

   // fill constructor
   // Constructs a container with "count" elements.
   // Each element is initialized as 0.
   list( size_type count ) // construct list from count * Ty()
      : myData()
   {
      myData.myHead = new node;
      myData.myHead->myVal = Ty();
      myData.myHead->prev = myData.myHead->next = myData.myHead;
      nodePtr t = myData.myHead;
      for (int i = 0; i < count; i++) {
          nodePtr tmp = new node;
          tmp->myVal = Ty();
          tmp->prev = t;
          t->next = tmp;
          tmp->next = myData.myHead;
          myData.myHead->prev = tmp;
          t=t->next;
      }
      myData.mySize = count;
   }

   // copy constructor
   // Constructs a container with a copy of each of the elements in "right",
   // in the same order.
   list( const list &right )
      : myData()
   {
       
       myData.myHead = new node;
       myData.myHead->myVal = Ty();
       myData.myHead->prev = myData.myHead->next = myData.myHead;
       nodePtr t = myData.myHead;
       nodePtr s = right.myData.myHead->next;
       for (int i = 0; i < right.myData.mySize; i++) {
           nodePtr tmp = new node;
           tmp->myVal = Ty();
           tmp->prev = t;
           t->next = tmp;
           tmp->next = myData.myHead;
           myData.myHead->prev = tmp;
           tmp->myVal = s->myVal;
           t = t->next;
           s = s->next;
       }
       myData.mySize = right.myData.mySize;
   }

   // List destructor
   // Destroys the container object.
   // Deallocates all the storage capacity allocated by the list container.
   ~list()
   {
      clear();
      delete myData.myHead;
   }

   // Assigns new contents to the container, replacing its current contents,
   // and modifying its size accordingly.
   // Copies all the elements from "right" into the container
   // (with "right" preserving its contents).
   list& operator=( const list &right )
   {
      if( this != &right )
      {
          
          if (right.myData.mySize == myData.mySize) {
              nodePtr x = myData.myHead->next;
              nodePtr y = right.myData.myHead->next;
              for (int i = 0; i < right.myData.mySize; i++) {
                  x->myVal = y->myVal;
                  x = x->next;
                  y = y->next;
              }
          }
          else if (right.myData.mySize > myData.mySize) {
              size_type count = right.myData.mySize - myData.mySize;
              nodePtr t = myData.myHead->prev;
              //expand the size 
              for (int i = 0; i < count; i++) {
                  nodePtr tmp = new node;
                  tmp->myVal = Ty();
                  tmp->prev = t;
                  t->next = tmp;
                  tmp->next = myData.myHead;
                  myData.myHead->prev = tmp;
                  t = t->next;
              }
              nodePtr x = myData.myHead->next;
              nodePtr y = right.myData.myHead->next;
              for (int i = 0; i < right.myData.mySize; i++) {
                  x->myVal = y->myVal;
                  x = x->next;
                  y = y->next;
              }
              myData.mySize = right.myData.mySize;
          }
          else {
              nodePtr x = myData.myHead->next;
              nodePtr y = right.myData.myHead->next;
              for (int i = 0; i < myData.mySize; i++) {
                  x->myVal = y->myVal;
                  x = x->next;
                  y = y->next;
              }
              nodePtr del = x->prev;
              myData.myHead->prev = x;
              del->next = myData.myHead;
            
              myData.mySize = right.myData.mySize;
          }
      }
      return *this;
   }

   // Returns an iterator pointing to the first element in the list container.
   // If the container is empty, the returned iterator value shall not be dereferenced.
   iterator begin()
   {
      return iterator( myData.myHead->next );
   }

   // Returns an iterator pointing to the first element in the list container.
   // If the container is empty, the returned iterator value shall not be dereferenced.
   const_iterator begin() const
   {
      return const_iterator( myData.myHead->next );
   }

   // Returns an iterator referring to the past-the-end element in the list container.
   // The past-the-end element is the theoretical element
   // that would follow the last element in the list container.
   // It does not point to any element, and thus shall not be dereferenced.
   // If the container is empty, this function returns the same as list::begin.
   iterator end()
   {
      return iterator( myData.myHead );
   }

   // Returns an iterator referring to the past-the-end element in the list container.
   // The past-the-end element is the theoretical element
   // that would follow the last element in the list container.
   // It does not point to any element, and thus shall not be dereferenced.
   // If the container is empty, this function returns the same as list::begin.
   const_iterator end() const
   {
      return const_iterator( myData.myHead );
   }

   // Returns the number of elements in the list container.
   size_type size() const
   {
      return myData.mySize;
   }

   // Returns whether the list container is empty (i.e. whether its size is 0).
   bool empty() const
   {
      return myData.mySize == 0;
   }

   // Returns a reference to the first element in the list container.
   // Calling this function on an empty container causes undefined behavior.
   reference front()
   {
      return myData.myHead->next->myVal;
   }

   // Returns a reference to the first element in the list container.
   // Calling this function on an empty container causes undefined behavior.
   const_reference front() const
   {
      return myData.myHead->next->myVal;
   }

   // Returns a reference to the last element in the list container.
   // Calling this function on an empty container causes undefined behavior.
   reference back()
   {
      return myData.myHead->prev->myVal;
   }

   // Returns a reference to the last element in the list container.
   // Calling this function on an empty container causes undefined behavior.
   const_reference back() const
   {
      return myData.myHead->prev->myVal;
   }

   // The container is extended by inserting a new element
   // before the element at the specified position.
   // This effectively increases the list size by the amount of elements inserted.
   // Returns an iterator that points to the newly inserted element.
   iterator insert( const_iterator where, const Ty &val ) // insert val at where
   {
       
       nodePtr n = new node;
       n->myVal = val;
       n->prev = n->next = n;
       nodePtr a = myData.myHead;
       while (a != where) {
           a = a->next;
       }
       nodePtr b = a->prev;
       a->prev = n;
       n->next = a;
       b->next = n;
       n->prev = b;
       myData.mySize++;
       return iterator(where);
   }

   // Removes from the list container the element at the specified position.
   // This effectively reduces the container size one, which is destroyed.
   // Returns an iterator pointing to the element that followed the element erased.
   // This is the container end if the operation erased the last element in the sequence.
   iterator erase( const_iterator where )
   {
       nodePtr x = myData.myHead;
       while (x != where) {
           x = x->next;
       }
       nodePtr f = x->next;
       nodePtr b = x->prev;
       b->next = f;
       f->prev = b;

       myData.mySize--;
       return iterator(where);
   }

   // Removes all elements from the list container (which are destroyed),
   // and leaving the container with a size of 0.
   void clear() // erase all
   {
      if( myData.mySize != 0 ) // the list is not empty
      {
          delete myData.myHead->next;
          myData.myHead->next = myData.myHead;
          myData.myHead->prev = myData.myHead;
          myData.mySize = 0;
      }
   }

private:
   ScaryVal myData;
};

// determine if two lists are equal and return true, otherwise return false
template< typename Ty >
bool operator==( const list< Ty > &left, const list< Ty > &right )
{
    if (left.size() == right.size()) {
        for (int i = 0; i < left.size(); i++) {
            if (left.front()!=right.front()) {
                return false;
            }
            left.begin() = left.begin()->next;
            right.begin() = right.begin()->next;
        }
        return true;
    }
    else {
        return false;
    }
}

template< typename Ty >
bool operator!=( const list< Ty > &left, const list< Ty > &right )
{
   return !( left == right );
}

#endif // LIST