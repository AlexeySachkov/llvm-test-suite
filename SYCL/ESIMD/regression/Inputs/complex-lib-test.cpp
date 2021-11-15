#include <CL/sycl.hpp>
#include <cstdio>

sycl::event iota(size_t n, sycl::buffer<int, 1> &d, sycl::queue &Q);

const char *name = "with eSIMD";

int main(int argc, char *argv[]) {
  try {
    size_t i;
    size_t N = 1024;
    sycl::device D(sycl::default_selector{});
    sycl::context C(D);
    sycl::queue Q(C, D);

    int *y = new int[N];
    {
      sycl::buffer<int, 1> buf_y(y, N);
      iota(N, buf_y, Q);
    }
    bool pass = true;
    for (i = 0; i < 10; ++i) {
      pass = pass && (y[i] == i);
    }
    delete[] y;
    fprintf(stdout, "%s: %s\n", argv[0], pass ? "PASS" : "FAIL");
  } catch (sycl::exception const &se) {
    fprintf(stderr, "%s failed with %s (%d)\n", argv[0], se.what(),
            se.code().value());

    return 1;
  } catch (std::exception const &e) {
    fprintf(stderr, "failed with %s\n", e.what());
    return 2;
  } catch (...) {
    fprintf(stderr, "failed\n");
    return -1;
  }
  return 0;
}

