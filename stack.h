template<typename T>
class Stack {
public:
  Stack(int capacity) : capacity_{capacity} {
    array_ = new T[capacity];
  }

  ~Stack() {
    delete array_;
  }

  void push(const T& element) {
    if (size_ >= capacity_) {
      expand();
    }
    array_[size_++] = element;
  }

  void pop() {
    if (empty()) {
      throw std::runtime_error("Failed to pop the element because the queue is empty.");
    }
    size_--;
    if (size_ < capacity_ / 3) {
      shrink();
    }
  }

  int size() const {
    return size_;
  }

  bool empty() const {
    return size_ == 0;
  }

  const T& top() const {
    if (empty()) {
      throw std::runtime_error("Failed to get the front element because the queue is empty.");
    }
    return array_[size_ - 1];
  }

  T& top() {
    if (empty()) {
      throw std::runtime_error("Failed to get the front element because the queue is empty.");
    }
    return array_[size_ - 1];
  }

private:
  int capacity_;
  int size_{0};
  T* array_;

  void expand() {
    change_array_capacity(capacity_ * 2);
  }

  void shrink() {
    change_array_capacity(capacity_ / 2);
  }

  void change_array_capacity(int new_capacity) {
    T* new_array = new T[new_capacity];
    move(array_, size_, new_array);

    delete array_;
    array_ = new_array;
    capacity_ = new_capacity;
  }

  void move(T* src, int count, T* dst) {
    memcpy(dst, src, count * sizeof(T));
  }
};