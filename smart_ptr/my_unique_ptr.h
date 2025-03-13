#pragma once
#include <utility>

namespace my {
  template<typename T>
  class unique_ptr {
    using value_type = T;
    template <typename U> friend class unique_ptr;
    public:
      explicit unique_ptr(value_type* ptr = nullptr) : ptr_(ptr) {}

      ~unique_ptr() {
        delete ptr_;
      }

      unique_ptr(const unique_ptr&) = delete;

      /* 移动复制构造函数 */
      template<typename U>
      unique_ptr(unique_ptr<U> &&rhs) {
        ptr_ = rhs.release();
      }

      /* 移动赋值运算符 */
      unique_ptr& operator=(unique_ptr &&rhs) {
        rhs.swap(*this);
        return *this;
      }

      value_type* get() const {
        return ptr_;
      }

      value_type* operator->() const {
        return ptr_;
      }

      value_type& operator*() const { 
        return *ptr_;
      }

      operator bool() const {
        return ptr_ != nullptr;
      }
    private:
      /* 交换两个 unique_ptr 的指针，仅仅在 move 语义下使用 */
      void swap(unique_ptr& rhs) noexcept {
        using std::swap;
        swap(ptr_, rhs.ptr_);
      }

      /* unique_ptr 不能被复制，因此 release() 函数用于获取被管理资源的指针，并将 ptr_ 置空 */
      value_type* release() {
        value_type* temp = ptr_;
        ptr_ = nullptr;
        return temp;
      }

      value_type* ptr_; // 指向被管理的资源
  }; // class unique_ptr
} // namespace my