#pragma once
#include <atomic>
#include <memory>

class Object {
public:
  std::atomic<int> ref_count{0};
  virtual ~Object() = default;
};

template <typename T> class ObjectPtr {
public:
  T *ptr;

  ObjectPtr() : ptr(nullptr) {}
  explicit ObjectPtr(T *p) : ptr(p) { retain(); }

  ObjectPtr(const ObjectPtr &other) : ptr(other.ptr) { retain(); }
  ObjectPtr &operator=(const ObjectPtr &other) {
    if (this != &other) {
      release();
      ptr = other.ptr;
      retain();
    }
    return *this;
  }

  ~ObjectPtr() { release(); }

  T *operator->() const { return ptr; }
  T &operator*() const { return *ptr; }

private:
  void retain() {
    if (ptr)
      ptr->ref_count.fetch_add(1, std::memory_order_relaxed);
  }

  void release() {
    if (ptr && ptr->ref_count.fetch_sub(1) == 1) {
      delete ptr;
    }
  }
};

template <typename T> class ObjectRef {
public:
  ObjectPtr<T> data;

  ObjectRef() = default;
  explicit ObjectRef(T *node) : data(node) {}
  T *operator->() const { return data.ptr; }
};
