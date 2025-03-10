#include "shape.h"
#include "my_shared_ptr.h"
#include <cstdio>

int main() {

    using namespace my;
    shared_ptr<circle> ptr1(new circle(2.0));
    printf("use count of ptr1 is %ld\n", ptr1.use_count());
    shared_ptr<shape> ptr2;
    printf("use count of ptr2 was %ld\n", ptr2.use_count());
    ptr2 = ptr1;
    printf("use count of ptr2 is now %ld\n", ptr2.use_count());
    if (ptr1) {
      puts("ptr1 is not empty");
    }
    printf("circle radius is %f\n", ptr1->radius_);

    return 0;
}

