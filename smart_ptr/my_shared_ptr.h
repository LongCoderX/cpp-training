#include <utility>

namespace my {
class shared_count {
public:
  shared_count() : count_(1) {}
  void add_count() { ++count_; }

  long reduce_count() {
    --count_;
    return count_;
  }

  long get_count() const { return count_; }

private:
  long count_;
};

template <typename T> class shared_ptr {
  using value_type = T;
  template <typename U> friend class shared_ptr;

public:
  shared_ptr() : shared_count_(nullptr){};
  explicit shared_ptr(value_type *ptr) : ptr_(ptr) {
    if (ptr_) {
      shared_count_ = new shared_count();
    }
  }
  ~shared_ptr() {
    if (ptr_ && !shared_count_->reduce_count()) {
      delete ptr_;
      delete shared_count_;
    }
  }

  shared_ptr(const shared_ptr &other) {
    ptr_ = other.ptr_;
    if (ptr_) {
      other.shared_count_->add_count();
      shared_count_ = other.shared_count_;
    }
  }

  /* 拷贝构造函数*/
  template <typename U> shared_ptr(const shared_ptr<U> &other) {
    ptr_ = other.ptr_;
    if (ptr_) {
      other.shared_count_->add_count();
      shared_count_ = other.shared_count_;
    }
  }

  template <typename U> shared_ptr(shared_ptr<U> &&other) {
    swap(other);
  }

  long use_count() const {
    if (ptr_) {
      return shared_count_->get_count();
    } else {
      return 0;
    }
  }

  /* 公共函数 */
  value_type *get() const { return ptr_; }
  value_type &operator*() const { return *ptr_; }
  value_type *operator->() const { return ptr_; }
  operator bool() const { return ptr_ != nullptr; }

private:
  void swap(shared_ptr &rhs) {
    std::swap(ptr_, rhs.ptr_);
    std::swap(shared_count_, rhs.shared_count_);
  }

  value_type *ptr_ = nullptr;            // 指向被管理的资源
  shared_count *shared_count_ = nullptr; // 引用计数器
}; // end of class shared_ptr
} // namespace my