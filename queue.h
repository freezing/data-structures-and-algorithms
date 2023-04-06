template<typename T>
class Queue {
public:
  Queue(int capacity) : capacity_{capacity} {
    array_ = new T[capacity];
  }

  ~Queue() {
    delete array_;
  }

  void enqueue(const T& element) {
    if (size_ >= capacity_) {
      expand();
    }
    array_[tail_index_] = element;
    tail_index_ = (tail_index_ + 1) % capacity_;
    size_++;
  }

  void dequeue() {
    if (empty()) {
      throw std::runtime_error("Failed to dequeue the element because the queue is empty.");
    }
    size_--;
    head_index_ = (head_index_ + 1) % capacity_;
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

  const T& front() const {
    if (empty()) {
      throw std::runtime_error("Failed to get the front element because the queue is empty.");
    }
    return array_[head_index_];
  }

  T& front() {
    if (empty()) {
      throw std::runtime_error("Failed to get the front element because the queue is empty.");
    }
    return array_[head_index_];
  }

private:
  int capacity_;
  int size_{0};
  int head_index_{0};
  int tail_index_{0};
  T* array_;

  void expand() {
    change_array_capacity(capacity_ * 2);
  }

  void shrink() {
    change_array_capacity(capacity_ / 2);
  }

  void change_array_capacity(int new_capacity) {
    T* new_array = new T[new_capacity];
    if (head_index_ < tail_index_) {
      move(array_, head_index_, tail_index_, new_array, 0);
    } else {
      move(array_, head_index_, capacity_, new_array, 0);
      move(array_, 0, tail_index_, new_array, capacity_ - head_index_);
    }
    delete array_;

    array_ = new_array;
    capacity_ = new_capacity;
    head_index_ = 0;
    tail_index_ = size_;
  }

  void move(T* src, int start, int end, T* dst, int offset) {
    memcpy(dst + offset, src + start, (end - start) * sizeof(T));
  }
};