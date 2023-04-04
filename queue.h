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
      throw std::runtime_error("Failed to enqueue an element because the queue is full.");
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
};