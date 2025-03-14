#include <utility>

namespace my {
class shared_count {
public:
  shared_count() noexcept : count_(1) {}
  void add_count() noexcept { ++count_; }
  long reduce_count() noexcept { return --count_; }
  long get_count() const noexcept { return count_; }

private:
  long count_;
};

template <typename T> class shared_ptr {
  using value_type = T;

public:
  template <typename U> friend class shared_ptr;

  explicit shared_ptr(T *ptr = nullptr) : ptr_(ptr) {
    if (ptr) {
      shared_count_ = new shared_count();
    }
  }
  ~shared_ptr() {
    if (ptr_ && !shared_count_->reduce_count()) {
      delete ptr_;
      delete shared_count_;
    }
  }

  // 拷贝构造函数
  shared_ptr(const shared_ptr &other) {
    ptr_ = other.ptr_;
    if (ptr_) {
      other.shared_count_->add_count();
      shared_count_ = other.shared_count_;
    }
  }

  // 类型转换构造函数
  template <typename U> shared_ptr(const shared_ptr<U> &other) noexcept {
    ptr_ = other.ptr_;
    if (ptr_) {
      other.shared_count_->add_count();
      shared_count_ = other.shared_count_;
    }
  }

  // 移动构造函数
  template <typename U> shared_ptr(shared_ptr<U> &&other) noexcept {
    ptr_ = other.ptr_;
    if (ptr_) {
      shared_count_ = other.shared_count_;
      other.ptr_ = nullptr;
    }
  }

  // 赋值运算符
  template <typename U> shared_ptr(const shared_ptr<U> &other, T *ptr) noexcept {
    ptr_ = ptr;
    if (ptr_) {
      other.shared_count_->add_count();
      shared_count_ = other.shared_count_;
    }
  }

  // 类型转换赋值运算符
  shared_ptr &operator=(shared_ptr rhs) noexcept {
    rhs.swap(*this);
    return *this;
  }

  T *get() const noexcept { return ptr_; }
  long use_count() const noexcept {
    if (ptr_) {
      return shared_count_->get_count();
    } else {
      return 0;
    }
  }
  void swap(shared_ptr &rhs) noexcept {
    using std::swap;
    swap(ptr_, rhs.ptr_);
    swap(shared_count_, rhs.shared_count_);
  }

  T &operator*() const noexcept { return *ptr_; }
  T *operator->() const noexcept { return ptr_; }
  operator bool() const noexcept { return ptr_; }

private:
  T *ptr_;
  shared_count *shared_count_;
};

template <typename T> void swap(shared_ptr<T> &lhs, shared_ptr<T> &rhs) noexcept {
  lhs.swap(rhs);
}

template <typename T, typename U>
shared_ptr<T> static_pointer_cast(const shared_ptr<U> &other) noexcept {
  T *ptr = static_cast<T *>(other.get());
  return shared_ptr<T>(other, ptr);
}

template <typename T, typename U>
shared_ptr<T> reinterpret_pointer_cast(const shared_ptr<U> &other) noexcept {
  T *ptr = reinterpret_cast<T *>(other.get());
  return shared_ptr<T>(other, ptr);
}

template <typename T, typename U>
shared_ptr<T> const_pointer_cast(const shared_ptr<U> &other) noexcept {
  T *ptr = const_cast<T *>(other.get());
  return shared_ptr<T>(other, ptr);
}

template <typename T, typename U>
shared_ptr<T> dynamic_pointer_cast(const shared_ptr<U> &other) noexcept {
  T *ptr = dynamic_cast<T *>(other.get());
  return shared_ptr<T>(other, ptr);
}
} // namespace my