#include <utility>

namespace my {
template <typename T> class unique_ptr {
  using value_type = T;

public:
  unique_ptr() = default;
  explicit unique_ptr(value_type *ptr) : ptr_(ptr){};
  ~unique_ptr() { delete this->ptr_; }

  /* 拷贝构造函数 */
  template <typename U> unique_ptr(const unique_ptr<U> &rhs) = delete;

  /* 移动构造函数 */
  template <typename U> unique_ptr(unique_ptr<U> &&rhs) {
    this->ptr_ = rhs.release();
  }

  /* 赋值函数 */
  template <typename U> unique_ptr &operator=(unique_ptr<U> &&rhs) {
    rhs.swap(*this);
    return *this;
  }

  /* 公共函数 */
  value_type *get() const { return ptr_; }
  value_type &operator*() const { return *ptr_; }
  value_type *operator->() const { return ptr_; }
  operator bool() const { return ptr_ != nullptr; }

private:
  /* 资源对象的所有权释放，对象内部的操作，不应该对外暴露 */
  value_type *release() {
    value_type *p = this->ptr_;
    this->ptr_ = nullptr;
    return p;
  }

  void swap(unique_ptr &rhs) { std::swap(this->ptr_, rhs.ptr_); }
  value_type *ptr_ = nullptr; // 指向资源对象的指针
};
} // namespace my