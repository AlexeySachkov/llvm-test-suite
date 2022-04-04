// There was an issue with dead argument elminitaion optimization, which lead
// to runtime errors when setting kernel arguments if the app was compiled with
// optimizations, but linked without them.
//
// The test checks that the scenario works correctly.
//
// RUN: %clangxx -fsycl -fsycl-targets=%sycl_triple %s -O2 -c -o %t.o
// RUN: %clangxx -fsycl -fsycl-targets=%sycl_triple %s -O0 -o %t.out
// RUN: %CPU_RUN_PLACEHOLDER %t.out %CPU_CHECK_PLACEHOLDER
// RUN: %GPU_RUN_PLACEHOLDER %t.out %GPU_CHECK_PLACEHOLDER
// RUN: %ACC_RUN_PLACEHOLDER %t.out %ACC_CHECK_PLACEHOLDER

#include <iostream>
#include <CL/sycl.hpp>

int main() {
  constexpr int THE_ANSWER = 42;

  sycl::queue q;

  int storage;
  sycl::buffer buf(&storage, sycl::range<1>(1));
  int storage2;
  sycl::buffer buf2(&storage2, sycl::range<1>(1));

  q.submit([&](sycl::handler &h) {
    auto acc = buf.get_access(h);
    auto acc2 = buf2.get_access(h);
    h.single_task([=]() {
      (void)acc; // unused
      acc2[0] = THE_ANSWER;
    });
  });

  return storage2 != THE_ANSWER;
}
