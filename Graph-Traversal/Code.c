/* moveFront(L)
 * moves the cursor to the front of the list.
 */
void moveFront(List L){
    if(L == NULL){        // check if the list is exist
        printf("List Error: calling moveFront() on an empty List\n");
        exit(EXIT_FAILURE);
    }
    L->index = 0;         // set the index of the list to 0
    L->cursor = L->front; // set the cursor of the list to the front
}

/* moveNext(L)
 * moves the cursor of a doubly linked list
 * to the next element in the list.
 */
void moveNext(List L){
    if (L == NULL){                      // check if the list is exist
        printf("List Error: calling moveNext() on an empty List\n");
        exit(EXIT_FAILURE);
    }
    if (L->cursor){                      // check if the cursor is currently pointing to an element in the list
        if (L->cursor == L->back)        // check if the current cursor is pointing to the last element in the list
            L->cursor = NULL;            // set cursor to NULL
        else                             // the current cursor is not pointing to the last element in the list
            L->cursor = L->cursor->next; // the cursor is updated to point to the next following node
        L->index++;                      // increment the index of the list by 1
    }
}

/* deleteFront(L)
 * deletes the node at the front
 * of a doubly linked list L.
 */
void deleteFront(List L){
    if(L == NULL){ // check if the list is exist
        printf("List Error: calling deleteFront() on an empty List\n");
        exit(EXIT_FAILURE);
    }

    Node N = L->front;  // create node N and initialize it to the front of L
    if (length(L) > 1){ // if the list has more than one node
        L->front = L->front->next; // update front to point to the next node
        L->front->prev = NULL; // set the previous pointer of the new front to NULL
        if (L->cursor != NULL)
            L->index--; // decrement the index if the cursor is defined
    }
    else{ // if L has only one node
        L->front = L->back = L->cursor = NULL; // set all pointers to NULL
        L->index = -1; // set the index to -1
    }
    L->length--; // decrement the length of L
    freeNode(&N); // free the memory occupied by N
}

/* append(L,x)
 * inserts a new integer element 'x'
 * to the end of a doubly linked list.
 */
void append(List L, int x){
    if (L == NULL){             // check if the list is exist
        printf("List Error: calling append() on an empty List\n");
        exit(EXIT_FAILURE);
    }

    Node N = newNode(x);        // create new node
    if (L->back == NULL){       // check if the list is empty
        L->front = L->back = N; // the new node N become both the front & back of the list
        L->cursor = L->back;    // the cursor is set to the back of the list
    }
    else{                       // the list is not empty
        L->back->next = N;      // the back node's next pointer is point to new node N
        N->prev = L->back;      // N's previous pointer is point to the back node
        L->back = N;            // N becomes the new back node of the list
        N->next = NULL;         // N next pointer is set to NULL
    }
    L->length++;                // increment the length of the list by 1
}

/* BFS(G,s)
 * performs a Breadth-First Search
 * on a given Graph 'G' starting
 * from a given vertex 's'
 */
void BFS(Graph G, int s){
    // initialize all vertices to default values of color, distance, and parent
    for (int x = 1; x <= getOrder(G); x++){
        G->color[x] = WHITE;
        G->distance[x] = INF;
        G->parent[x] = NIL;
    }
    // set the source vertex and its properties
    G->source = s;
    G->color[s] = GRAY;
    G->distance[s] = 0;
    G->parent[s] = NIL;

    List L = newList(); // create a new List L
    append(L, s); // append the source vertex

    // traverse the Graph in a BFS algorithm
    while(L != NULL){        // loop while the queue L is not empty
        // dequeue the front vertex from the list
        int x = front(L);
        deleteFront(L);
        // get the adjacency list of the current vertex
        List N = G->neighbors[x];
        moveFront(N);
        // traverse the adjacency list of the current vertex
        while (index(N) != -1){
            int y = get(N);
            // if the neighbor is not visited
            if (G->color[y] == WHITE){
                // set the neighbor as visited and update its distance and parent
                G->color[y] = GRAY;
                G->distance[y] = G->distance[x] + 1;
                G->parent[y] = x;
                // enqueue the neighbor to the queue
                append(L, y);
            }
            moveNext(N);     // move to the next neighbor in the adjacency list
        }
        G->color[x] = BLACK; // set the current vertex as processed
    }
    freeList(&L);            // free the memory of the list
}