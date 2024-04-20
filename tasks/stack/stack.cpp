#include "stack.h"

Node::Node(int32_t value, Node* previous) : value(value), previous(previous) {
}

Stack::Stack() : head_(nullptr), size_(0){};

Stack::~Stack() {
    Clear();
}

void Stack::Push(int32_t value) {
    head_ = new Node(value, head_);
    size_++;
}
void Stack::Pop() {
    if (head_ == nullptr) {
        return;
    }
    Node* temp = head_;
    head_ = head_->previous;
    delete temp;
    size_--;
}

int32_t Stack::Top() const {
    if (head_ == nullptr) {
        return 0;
    }
    return head_->value;
}

int32_t Stack::Size() const {
    return size_;
}

void Stack::Clear() {
    while (head_ != nullptr) {
        Node* temp = head_;
        head_ = head_->previous;
        delete temp;
    }
    size_ = 0;
}

bool Stack::Empty() const {
    return size_ == 0;
}
