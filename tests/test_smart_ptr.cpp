#include "shape.h"
#include "my_unique_ptr.h"
#include "my_shared_ptr.h"
#include <cstdio>

int main() {
    /* 测试 unique_ptr 的基本功能 */
    my::unique_ptr<circle> uptr1(new circle(1.0));
    printf("use count of uptr1 is %lf\n", uptr1->radius_);
    my::unique_ptr<shape> uptr2;
    uptr2 = std::move(uptr1);
    if (uptr1) {
      puts("uptr1 is not empty");
    }
    printf("use count of uptr2 is now %lf\n", static_cast<circle*>(uptr2.get())->radius_);


    /* 测试 shared_ptr 的基本功能 */
    // using namespace my;
    // shared_ptr<circle> ptr1(new circle(2.0));
    // printf("use count of ptr1 is %ld\n", ptr1.use_count());
    // shared_ptr<shape> ptr2;
    // printf("use count of ptr2 was %ld\n", ptr2.use_count());
    // ptr2 = ptr1;
    // printf("use count of ptr2 is now %ld\n", ptr2.use_count());
    // if (ptr1) {
    //   puts("ptr1 is not empty");
    // }
    // printf("circle radius is %f\n", ptr1->radius_);

    return 0;
}

