namespace s21 {
    
template<typename key_type, typename mapped_type,typename Comp>
Iterator<key_type, mapped_type,Comp>::Iterator(Node<key_type, mapped_type>* node) : current_node(node) {
    key_type temp_k = current_node->key;
    mapped_type temp_v = current_node->value;
     pairIter = std::make_pair<key_type,mapped_type>(std::move(temp_k), std::move(temp_v));
}

template<typename key_type, typename mapped_type,typename Comp>
Iterator<key_type, mapped_type,Comp>& Iterator<key_type, mapped_type,Comp>::operator++() {
if (current_node == nullptr) {
    return *this;
}

if (current_node->right->right != nullptr) {
    current_node = findMin(current_node->right);
} else {
    Node<key_type, mapped_type>* parent = current_node->parent;
    while (parent != nullptr && current_node == parent->right) {
        current_node = parent;
        parent = parent->parent;
    }
    current_node = parent;
}

if (current_node) pairIter = std::make_pair(get_key(),get_value());
    
return *this;
}

template<typename key_type, typename mapped_type,typename Comp>
Iterator<key_type, mapped_type,Comp>& Iterator<key_type, mapped_type,Comp>::operator--() {
    if (current_node == nullptr) {
        return *this;
    }
    
    if (current_node->left->left != nullptr) {
        current_node = findMax(current_node->left);
    } else {
        Node<key_type, mapped_type>* parent = current_node->parent;
        while (parent != nullptr && current_node == parent->left) {
            current_node = parent;
            parent = parent->parent;
        }
        current_node = parent;
    }
if (current_node)    pairIter = std::make_pair(get_key(),get_value());
    return *this;
}

template<typename key_type, typename mapped_type,typename Comp>
std::pair<key_type,mapped_type> Iterator<key_type, mapped_type,Comp>::operator*() {
    return std::make_pair(get_key(),get_value());
}

template<typename key_type, typename mapped_type,typename Comp>
std::pair<key_type,mapped_type>* Iterator<key_type, mapped_type,Comp>::operator->() {
    return &(pairIter);
}

template<typename key_type, typename mapped_type,typename Comp>
bool Iterator<key_type, mapped_type,Comp>::operator<=(Iterator<key_type, mapped_type,Comp> node) const {
    if (current_node && node.current_node) return ((Comp{} (current_node->key,node.current_node->key)) || (current_node->key == node.current_node->key));
    return 0;
}

template<typename key_type, typename mapped_type,typename Comp>
ConstIterator<key_type, mapped_type,Comp>::ConstIterator(const Node<key_type, mapped_type>* node) : current_node(node){}


template<typename key_type, typename mapped_type,typename Comp>
ConstIterator<key_type, mapped_type,Comp>& ConstIterator<key_type, mapped_type,Comp>::operator++() {
if (current_node == nullptr) {
    return *this;
}

if (current_node->right->right != nullptr) {
    current_node = findMin(current_node->right);
} else {
    Node<key_type, mapped_type>* parent = current_node->parent;
    while (parent != nullptr && current_node == parent->right) {
        current_node = parent;
        parent = parent->parent;
    }
    current_node = parent;
}
return *this;
}

template<typename key_type, typename mapped_type,typename Comp>
ConstIterator<key_type, mapped_type,Comp>& ConstIterator<key_type, mapped_type,Comp>::operator--() {
if (current_node == nullptr) {
    return *this;
}

if (current_node->left->left != nullptr) {
    current_node = findMax(current_node->left);
} else {
    Node<key_type, mapped_type>* parent = current_node->parent;
    while (parent != nullptr && current_node == parent->left) {
        current_node = parent;
        parent = parent->parent;
    }
    current_node = parent;
}
return *this;
}

template<typename key_type, typename mapped_type,typename Comp>
bool ConstIterator<key_type, mapped_type,Comp>::operator<=(ConstIterator<key_type, mapped_type,Comp> node) const {
    if (current_node && node.current_node) return ((Comp{} (current_node->key,node.current_node->key)) || (current_node->key == node.current_node->key));
    return 0;
}

template<typename key_type, typename mapped_type>
Node<key_type, mapped_type>* findMin(Node<key_type, mapped_type>* node) noexcept {
    while (node->left->left != nullptr) {
        node = node->left;
    }
    return node;
}

template<typename key_type, typename mapped_type>
Node<key_type, mapped_type>* findMax(Node<key_type, mapped_type>* node) noexcept {
    while (node->right->right != nullptr) {
        node = node->right;
    }
    return node;
}
    
}