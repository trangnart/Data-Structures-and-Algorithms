/* inOrderString(s,R)
 * recursively generates an in-order traversal string
 * of the binary search tree rooted at R.
 */
void Dictionary::inOrderString(std::string& s, Node* R) const {
    // base case: if the node is NULL, return
    if (R == NULL)
        return;

    // recursively call inOrderString() on the left subtree
    inOrderString(s, R->left);

    // append the node's key and value to the string with a newline character
    s += R->key + " : "
                + std::to_string(R->val)
                + "\n";
    // recursively call inOrderString() on the right subtree
    inOrderString(s, R->right);
}

/* preOrderString(s,R)
 * recursively generates an pre-order traversal string
 * of the binary search tree rooted at R.
 */
void Dictionary::preOrderString(std::string& s, Node* R) const {
    // base case: if the node is NULL, return
    if (R == NULL){
        return;
    }
    // append the node's key R to the string with a newline character
    s += R->key + "\n";

    // recursively call preOrderString() on the left & right subtree, respectively
    preOrderString(s, R->left);
    preOrderString(s, R->right);
}

/* to_string()
 * returns a string representation of the binary search tree
 * by recursively constructing a string in in-order traversal order.
 */
std::string Dictionary::to_string() const{
    std::string str;
    inOrderString(str, root);
    return str;
}

/* pre_string()
 * returns a string representation of the binary search tree
 * by recursively constructing a string in pre-order traversal order.
 */
std::string Dictionary::pre_string() const{
    std::string str;
    preOrderString(str, root);
    return str;
}

/* setValue(k,v)
 * sets the value of a given key in a dictionary
 */
void Dictionary::setValue(keyType k, valType v){
    // create pointers to two nodes
    Node *cur;
    Node *r;

    // if the root node is NULL, create a new node and set it as the root node
    if (root == NULL)
        root = new Node(k, v);

    else{ // if the root node is not NULL, traverse through the tree
        cur = root;
        r = new Node(k, v);
        while (cur != NULL){
            // if the key is greater than the current node's key, go to the right child
            if (k > cur->key){
                if (cur->right == NULL){
                    // if the right child is NULL, set the new node as the right child
                    r->parent = cur;
                    cur->right = r;
                    cur = NULL;
                }
                else{
                    // if the right child is not NULL, continue traversing through the tree
                    cur = cur->right;
                }
            }
            // if the key is less than the current node's key, go to the left child
            else if (k < cur->key){
                if (cur->left == NULL){
                    // if the left child is NULL, set the new node as the left child
                    r->parent = cur;
                    cur->left = r;
                    cur = NULL;
                }
                else{
                    // if the left child is not NULL, continue traversing through the tree
                    cur = cur->left;
                }
            }
            // if the key is equal to the current node's key, update the value of the current node
            else{
                cur->val = v;
                delete r;
                cur = NULL;
                num_pairs--;
            }
        }
    }
    num_pairs++; // increment the number of key-value pairs in the dictionary
}

Dictionary D;
string line;
int count = 0;

// Read each line from the input file and add it as a value
// to a binary search tree with the line number as its key
while(getline(fin, line)){
    count++;
    D.setValue(line, count);
}
fout << D.to_string() << endl << endl;
fout << D.pre_string() << endl << endl;