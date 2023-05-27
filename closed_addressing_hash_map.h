#include <list>
#include <optional>
#include <vector>

/// This is an example implementation of a closed addressing hash map.
/// Please note that this implementation is not meant for production use and it doesn't follow C++ standards with the
/// idea that people unfamiliar with C++ can also understand it.
/// There are existing libraries that offer more efficient solutions.
/// I intentionally incorporated some low-level concepts to align with the content of the associated YouTube video.
/// Raw arrays are utilized to store the buckets, and lists are employed for the buckets themselves.
/// Even if you were to implement this on your own, it is advisable not to use raw arrays.
/// Instead, you could opt for more convenient options like vectors. However, this implementation has been designed
/// for educational purposes.

/// An implementation of djb2 hashing algorithm.
/// See: http://www.cse.yorku.ca/~oz/hash.html
template<typename K>
unsigned long hash(const K &key);

/// Provide implementation for ints.
/// In practice, we'd want to provide a hash function that takes [int] instead of [const int&] but it's not relevant
/// for this purpose.
template<>
unsigned long hash<int>(const int &key) {
  return 5381 + key;
}

/// Provide implementation for strings.
template<>
unsigned long hash<std::string>(const std::string &key) {
  unsigned long hash = 5381;

  for (int c : key) {
	// hash = hash * 33 + c
	hash = ((hash << 5) + hash) + c;
  }
  return hash;
}

template<typename K, typename V>
class ClosedAddressingHashMap {
public:
  struct Entry {
	K key;
	V value;
  };

  ClosedAddressingHashMap(int capacity)
	  : capacity_{capacity} {
	buckets_ = new std::list<Entry>[capacity];
  }

  ~ClosedAddressingHashMap() {
	delete[] buckets_;
  }

  void insert(const K &key, const V &value) {
	int bucket_index = hash(key) % capacity_;
	auto &bucket = buckets_[bucket_index];
	auto it = find(bucket, key);
	if (it != bucket.end()) {
	  // Key is found, replace the existing value.
	  it->value = value;
	} else {
	  // Key is not found, insert a new one.
	  bucket.emplace_back(key, value);
	  incr_count_and_maybe_rehash();
	}
  }

  void remove(const K &key) {
	int bucket_index = hash(key) % capacity_;
	auto &bucket = buckets_[bucket_index];
	auto it = find(bucket, key);
	if (it != bucket.end()) {
	  // Only delete if the key exists.
	  bucket.erase(it);
	  decr_count_and_maybe_rehash();
	}
  }

  bool contains(const K &key) const {
	int bucket_index = hash(key) % capacity_;
	const auto &bucket = buckets_[bucket_index];
	return find(bucket, key) != bucket.end();
  }

  V &get(const K &key) {
	int bucket_index = hash(key) % capacity_;
	auto &bucket = buckets_[bucket_index];
	auto it = find(bucket, key);
	if (it != bucket.end()) {
	  return it->value;
	}
	throw std::out_of_range("Key not found");
  }

  int size() const {
	return count_;
  }

  bool empty() const {
	return size() == 0;
  }

private:
  int count_{0};
  int capacity_;
  std::list<Entry> *buckets_;

  // Linear search through the bucket to find the matching key.
  typename std::list<Entry>::iterator find(std::list<Entry> &bucket, const K &key) {
	for (auto it = bucket.begin(); it != bucket.end(); it++) {
	  if (it->key == key) {
		// We found the element that matches the key.
		return it;
	  }
	}
	// No entry that matches the key was found.
	return bucket.end();
  }

  // Provide a const override.
  // Linear search through the bucket to find the matching key.
  typename std::list<Entry>::const_iterator find(const std::list<Entry> &bucket, const K &key) const {
	for (auto it = bucket.begin(); it != bucket.end(); it++) {
	  if (it->key == key) {
		// We found the element that matches the key.
		return it;
	  }
	}
	// No entry that matches the key was found.
	return bucket.end();
  }

  void incr_count_and_maybe_rehash() {
	count_++;
	maybe_grow();
  }

  void decr_count_and_maybe_rehash() {
	count_--;
	maybe_shrink();
  }

  void maybe_grow() {
	int load_factor = 100 * count_ / capacity_;
	if (load_factor > 75) {
	  // Double the size. We could also increase it by e.g. 50%. There are multiple options here, but the idea is the
	  // same.
	  int new_capacity = capacity_ * 2;
	  rehash(new_capacity);
	}
  }

  void maybe_shrink() {
	int load_factor = 100 * count_ / capacity_;
	// Half the size, but never go below some arbitrary number.
	if (load_factor < 25 && capacity_ > 8) {
	  int new_capacity = std::min(4, capacity_ / 2);
	  rehash(new_capacity);
	}
  }

  void rehash(int new_capacity) {
	std::list<Entry> *old_buckets = buckets_;
	int old_capacity = capacity_;

	buckets_ = new std::list<Entry>[new_capacity];
	count_ = 0;
	capacity_ = new_capacity;

	// Insert all elements from the old hash map to the new one.
	for (int i = 0; i < old_capacity; i++) {
	  auto &bucket = old_buckets[i];
	  for (auto &entry : bucket) {
		insert(entry.key, entry.value);
	  }
	}

	delete[] old_buckets;
  }
};