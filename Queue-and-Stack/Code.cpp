/* moveNext()
 * moves the cursor forward by 1 element in the linked list
 * and returns the data of the element before the cursor.
 */
ListElement List::moveNext(){
    // if the current position is already at the end of the list, throw an error message
    if (position() > (length() - 1))
        throw std::range_error("moveNext() error");

    // if the element before the cursor is different from the element after the cursor, update the beforeCursor
    if (beforeCursor != afterCursor)
        beforeCursor = afterCursor;

    // update the element after the cursor to be the next element in the list or the backDummy if it is NULL
    afterCursor = afterCursor->next ? afterCursor->next : backDummy;

    pos_cursor++; // increment the position of the cursor
    return beforeCursor->data;
}

/* moveFront()
 * moves the cursor to the front of the list
 */
void List::moveFront(){
    beforeCursor = afterCursor; // set 'beforeCursor' to point to the same node as afterCursor
    afterCursor = frontDummy;   // set 'afterCursor' to point to the front dummy node
    pos_cursor = 0;             // reset the cursor position to 0
}

/* insertBefore(x)
 * inserts a new element 'x' before the current position in a linked list
 */
void List::insertBefore(ListElement x){
    // if the current position of the cursor is less than 0, throw an error message
    if (position() < 0)
        throw std::range_error("insertBefore() error");

    Node *N = new Node(x);              // create new Node
    if (length() == 0)                  // if the length of the list is 0
        beforeCursor = afterCursor = frontDummy = backDummy = N; // set all the pointer variables to point to the new Node

    else{                               // the length of the list is not 0
        // set the 'prev' & 'next' pointers of the new Node to point to the beforeCursor & afterCursor pointers respectively
        N->prev = beforeCursor;
        N->next = afterCursor;
        if (beforeCursor == backDummy){ // if the beforeCursor pointer is pointing to the backDummy node
            backDummy = N;              // set the backDummy pointer to point to the new Node
            N->next = nullptr;          // set the next pointer of the new Node to nullptr
        }
        else
            afterCursor->prev = N;      // set the prev pointer of the afterCursor node to point to the new Node

        if (!position()){               // check if the current position of the cursor is 0
            frontDummy = N;             // set frontDummy pointer to point to the new Node
            N->prev = nullptr;          // set the prev pointer of the new Node to nullptr
        }
        else
            beforeCursor->next = N;     // set the next pointer of the beforeCursor node to point to the new Node

        beforeCursor = N;               // inserting the new element into the list before the current position of the cursor
    }
    pos_cursor++;                       // increment the position of the cursor by 1
    num_elements++;                     // increment the number of elements by 1
}

/* shuffleCount(n)
 * shuffles a list of n elements
 * and counts the number of shuffles
 * needed to return the list to its original order.
 */
int shuffleCount(int n){
    int count = 0;
    List Deck, OG;

    // insert integers 0 through n-1 into Deck and OG
    for (int i = 0; i < n; i++){
        Deck.insertBefore(i);
        OG.insertBefore(i);
    }

    // shuffle the Deck until it is the same as the original order (OG)
    do{
        shuffle(Deck);
        count++;
    } while (!(Deck == OG));

    return count; // return the number of shuffles required to get back to the OG
}

/* shuffle(D)
 * shuffles the elements of a doubly linked list D
 * by performing a "perfect shuffle".
 */
void shuffle(List& D){
    int i;
    int len = D.length();
    int mid = D.length() / 2;
    List L, R;

    D.moveFront();              // move the cursor to the front of D
    for (i = 0; i < mid; i++)   // insert the first half of D's elements into L
        L.insertBefore(D.moveNext());

    for (i = mid; i < len; i++) // insert the second half of D's elements into R
        R.insertBefore(D.moveNext());

    // clear the contents of D and re-insert elements from L and R into D
    D.clear();
    L.moveFront();
    R.moveFront();
    for (i = mid; i < len; i++){
        D.insertBefore(R.moveNext());
        if (L.position() < L.length())
            D.insertBefore(L.moveNext());
    }
}