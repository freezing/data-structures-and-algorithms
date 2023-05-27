#include <list>
#include <optional>
#include <vector>

/// This is an example implementation of an open addressing hash map.
/// Please note that this implementation is not meant for production use and it doesn't follow C++ standards with the
/// idea that people unfamiliar with C++ can also understand it.
/// There are existing libraries that offer more efficient solutions. This implementation has been designed
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

/// Define probing functions.
template<typename K>
struct LinearProbing {
  int operator()(const K &key, int attempt, int capacity) const {
	return (hash(key) + attempt) % capacity;
  }
};

template<typename T>
std::string to_debug(const T &value);

template<>
std::string to_debug(const std::string &value) {
  return value;
}

template<>
std::string to_debug(const int &value) {
  return std::to_string(value);
}

template<typename K, typename V, typename ProbingFn = LinearProbing<K>>
class OpenAddressingHashMap {
public:
  struct Entry {
	K key;
	V value;
	bool is_deleted;
  };

  OpenAddressingHashMap(int capacity)
	  : capacity_{capacity} {
	slots_ = new Entry[capacity];
	// Ensure all slots are deleted.
	clear();
  }

  ~OpenAddressingHashMap() {
	delete[] slots_;
  }

  void insert(const K &key, const V &value) {
	auto index = find_index(key, /* return_deleted_slot */ true);
	if (!index) {
	  throw std::runtime_error("not enough space in the hash map");
	}
	auto &entry = slots_[*index];

	// If this is an update (not inserting a new key), then just update the value.
	if (!entry.is_deleted && entry.key == key) {
	  entry.value = value;
	} else {
	  assert(entry.is_deleted);
	  entry.key = key;
	  entry.value = value;
	  entry.is_deleted = false;
	  incr_count_and_maybe_rehash();
	}
  }

  void remove(const K &key) {
	auto index = find_index(key, /* return_deleted_slot */ false);
	// There's nothing to do if the key doesn't exist.
	if (index) {
	  auto &entry = slots_[*index];
	  assert(!entry.is_deleted);
	  entry.is_deleted = true;
	  decr_count_and_maybe_rehash();
	}
  }

  bool contains(const K &key) const {
	auto index = find_index(key, /* return_deleted_slot */ false);
	if (!index) {
	  return false;
	}
	auto &entry = slots_[*index];
	assert(!entry.is_deleted);
	return entry.key == key;
  }

  V &get(const K &key) {
	auto index = find_index(key, /* return_deleted_slot */ false);

	if (index) {
	  auto &entry = slots_[*index];

	  if (!entry.is_deleted) {
		assert(entry.key == key);
		return entry.value;
	  }
	}
	throw std::out_of_range("Key " + to_debug(key) + " not found");
  }

  int size() const {
	return count_;
  }

  bool empty() const {
	return size() == 0;
  }

  void clear() {
	count_ = 0;
	for (int i = 0; i < capacity_; i++) {
	  slots_[i].is_deleted = true;
	}
  }

private:
  int count_{0};
  int capacity_;
  Entry *slots_;

  /// Returns an index of an empty slot or the slot that contains the key.
  std::optional<int> find_index(const K &key, bool return_deleted_slot) const {
	for (int attempt = 0; attempt < capacity_; attempt++) {
	  int slot_index = ProbingFn{}(key, attempt, capacity_);
	  auto &slot = slots_[slot_index];

	  if (!slot.is_deleted && slot.key == key) {
		return slot_index;
	  }

	  if (return_deleted_slot && slot.is_deleted) {
		return {slot_index};
	  }
	}
	return std::nullopt;
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
	Entry *old_slots = slots_;
	int old_capacity = capacity_;

	slots_ = new Entry[new_capacity];
	capacity_ = new_capacity;
	clear();

	// Insert all elements from the old hash map to the new one.
	for (int i = 0; i < old_capacity; i++) {
	  auto &entry = old_slots[i];
	  if (!entry.is_deleted) {
		insert(entry.key, entry.value);
	  }
	}

	delete[] old_slots;
  }
};