// some body function of List

/* append()
 * inserts a new integer element 'x'
 * to the end of a doubly linked list.
 */
void append(List L, int x){
    if (L == NULL){            // check if the list is exist
        printf("List Error: calling append() on an empty List\n");
        exit(EXIT_FAILURE);
    }

    Node N = newNode(x);        // create new node
    if (L->back == NULL){       // check if the list is empty
        L->front = L->back = N; // the new node N become both the 'front' & 'back' of the list
        L->cursor = L->back;    // the cursor is set to the back of the list
    }
    else{                       // the list is not empty
        L->back->next = N;      // the 'back' node's 'next' pointer is point to new node N
        N->prev = L->back;      // N's 'prev' pointer is point to the 'back' node
        L->back = N;            // N becomes the new 'back' node of the list
        N->next = NULL;         // N 'next' pointer is set to NULL
    }
    L->length++;                // increment the 'length' of the list by 1
}

/* prepend()
 * inserts a new integer element 'x'
 * to the beginning of a doubly linked list.
 */
void prepend(List L, int x){
    if(L == NULL){              // check if the list is exist
        printf("List Error: calling prepend() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    Node N = newNode(x);        // create new node

    if (L->front == NULL){      // check if the list is empty
        L->front = L->back = N; // the new node N become both the 'front' & 'back' of the list
        L->cursor = L->front;   // the 'cursor' is set to the 'front' of the list
    }
    else{                       // the list is not empty
        L->front->prev = N;     // the 'previous' node of the current 'front' node is set to point to N
        N->next = L->front;     // the 'next' node of N is set to point to the current 'front' node
        L->front = N;           // the 'front' of the list is updated to point to N
        L->index++;             // increment the 'index' of the list by 1
    }
    L->length++;                // increment the 'length' of the list by 1
}

/* moveFront()
 * moves the cursor to the front of the list.
 */
void moveFront(List L){
    if(L == NULL){        // check if the list is exist
        printf("List Error: calling moveFront() on an empty List\n");
        exit(EXIT_FAILURE);
    }
    L->index = 0;         // set the 'index' of the list to 0
    L->cursor = L->front; // set the 'cursor' of the list to the front
}

/* moveNext()
 * moves the cursor of a doubly linked list
 * to the next element in the list.
 */
void moveNext(List L){
    if (L == NULL){                     // check if the list is exist
        printf("List Error: calling moveNext() on an empty List\n");
        exit(EXIT_FAILURE);
    }
    if (L->cursor){                      // check if the 'cursor' is currently pointing to an element in the list
        if (L->cursor == L->back)        // check if the current 'cursor' is pointing to the last element in the list
            L->cursor = NULL;            // set 'cursor' to NULL
        else                             // the current 'cursor' is NOT pointing to the last element in the list
            L->cursor = L->cursor->next; // the 'cursor' is updated to point to the next following node
        L->index++;                      // increment the 'index' of the list by 1
    }
}

/* insertBefore()
 * inserts a new integer element 'x'
 * in front of the node pointed to
 * by the cursor of the doubly linked list.
 */
void insertBefore(List L, int x){
    if(L == NULL){                 // check if the list is exist
        printf("List Error: calling insertBefore() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->cursor == L->front)     // check if the 'cursor' is pointing to the first element of the list
        prepend(L, x);             // call 'prepend()' to insert the new node at the beginning of the list
    else{                          // the 'cursor' is not pointing to the first element of the list
        Node N = newNode(x);       // create a new node with value 'x'
        N->prev = L->cursor->prev; // set the 'previous' pointer of a new node N to point to the node that precedes the current 'cursor' position
        N->next = L->cursor;       // set the 'next' pointer of a new node N to point to the current 'cursor' position
        L->cursor->prev->next = N; // set the 'next' pointer of the node that precedes the current 'cursor' position to point to a new node N
        L->cursor->prev = N;       // set the 'previous' pointer of the current 'cursor' to point to a new node N
        L->index++;                // increment the 'index' of the list by 1
        L->length++;               // increment the 'length' of the list by 1
   }
}

// the code below is print out the contents of a file
List sorted = newList();                  // create a new empty linked list

// insertion sort algorithm
for (idx = 0; idx < lines; idx++){        // iterate over the input array
    if (isEmpty(sorted))                  // called isEmpty() func to check if the list is empty
        append(sorted, idx);              // append the current index
    else{
        moveFront(sorted);                // move the cursor to the front of the list

        while (index(sorted) >= 0){       // iterate over the elements in the list
            int cmp = strcmp(array[idx], array[get(sorted)]); // compare the current string with the string at the current index

            if (cmp < 0){                 // if the current string is less than the string at the current index
               insertBefore(sorted, idx); // insert the current index before the current index
               break;
            }
            moveNext(sorted);             // move the cursor to the next element in the list

            if (index(sorted) == -1){     // if the end of the list is reached
               append(sorted, idx);       // append the current index to the list
               break;
            }
        }
    }
}

moveFront(sorted);                          // move the cursor of the list to the front
while (index(sorted) >= 0){                 // iterate over the elements in the list
    fprintf(out, "%s", array[get(sorted)]); // write the current string to the output file
    moveNext(sorted);                       // move the cursor to the next element in the list
    if (index(sorted) >= 0)                 // if there are more elements in the list
        fprintf(out, "\n");                 // write a newline character to the output file
}