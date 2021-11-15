// This test is written with an aim to check that experimental::printf behaves
// in the same way as printf from C99/C11
//
// The test is written using conversion specifiers table from cppreference [1]
// [1]: https://en.cppreference.com/w/cpp/io/c/fprintf
//
// RUN: %clangxx -fsycl %s -o %t.out
// RUN: %CPU_RUN_PLACEHOLDER %t.out %CPU_CHECK_PLACEHOLDER
// RUN: %GPU_RUN_PLACEHOLDER %t.out %GPU_CHECK_PLACEHOLDER
// RUN: %ACC_RUN_PLACEHOLDER %t.out %ACC_CHECK_PLACEHOLDER

#include <CL/sycl.hpp>

#include "helper.hpp"

using namespace sycl;

void do_d_i_test() { // %d, %i signed integer, decimal representation
  // Some reference values
  constexpr char CHAR_VALUE = 0x7B;     // 123
  constexpr short SHORT_VALUE = 0x3039; // 12345
  constexpr int INT_VALUE = 0x499602D3; // 1234567891
  constexpr long LONG_VALUE = INT_VALUE;
  constexpr long long LONG_LONG_VALUE =
      0x112210F4B2D230A2; // 1234567891011121314

  signed char hhd = CHAR_VALUE;
  short hd = SHORT_VALUE;
  int d = INT_VALUE;
  long ld = LONG_VALUE;
  long long lld = LONG_LONG_VALUE;
  intmax_t jd = LONG_LONG_VALUE;
  size_t zd = LONG_LONG_VALUE;
  ptrdiff_t td = LONG_LONG_VALUE;

  FORMAT_STRING(fmt1) = "%%d positive values:\n"
                        "\t%%hhd=%hhd\n"
                        "\t%%hd=%hd\n"
                        "\t%%d=%d\n"
                        "\t%%ld=%ld\n"
                        "\t%%lld=%lld\n"
                        "\t%%jd=%jd\n"
                        "\t%%zd=%zd\n"
                        "\t%%t=%td\n";
  ext::oneapi::experimental::printf(fmt1, hhd, hd, d, ld, lld, jd, zd, td);
  // CHECK: %d positive values:
  // CHECK-NEXT: %hhd=123
  // CHECK-NEXT: %hd=12345
  // CHECK-NEXT: %d=1234567891
  // CHECK-NEXT: %ld=1234567891
  // CHECK-NEXT: %lld=1234567891011121314
  // CHECK-NEXT: %jd=1234567891011121314
  // CHECK-NEXT: %zd=1234567891011121314
  // CHECK-NEXT: %t=1234567891011121314

  FORMAT_STRING(fmt2) = "%%i positive values:\n"
                        "\t%%hhi=%hhi\n"
                        "\t%%hi=%hi\n"
                        "\t%%i=%i\n"
                        "\t%%li=%li\n"
                        "\t%%lli=%lli\n"
                        "\t%%ji=%ji\n"
                        "\t%%zi=%zi\n"
                        "\t%%ti=%ti\n";
  ext::oneapi::experimental::printf(fmt2, hhd, hd, d, ld, lld, jd, zd, td);
  // CHECK: %i positive values:
  // CHECK-NEXT: %hhi=123
  // CHECK-NEXT: %hi=12345
  // CHECK-NEXT: %i=1234567891
  // CHECK-NEXT: %li=1234567891
  // CHECK-NEXT: %lli=1234567891011121314
  // CHECK-NEXT: %ji=1234567891011121314
  // CHECK-NEXT: %zi=1234567891011121314
  // CHECK-NEXT: %ti=1234567891011121314

  hhd = -hhd;
  hd = -hd;
  d = -d;
  ld = -ld;
  lld = -lld;
  jd = -jd;
  zd = -zd;
  td = -td;

  FORMAT_STRING(fmt3) = "%%d negative values:\n"
                        "\t%%hhd=%hhd\n"
                        "\t%%hd=%hd\n"
                        "\t%%d=%d\n"
                        "\t%%ld=%ld\n"
                        "\t%%lld=%lld\n"
                        "\t%%jd=%jd\n"
                        "\t%%zd=%zd\n"
                        "\t%%t=%td\n";
  ext::oneapi::experimental::printf(fmt3, hhd, hd, d, ld, lld, jd, zd, td);
  // CHECK: %d negative values:
  // CHECK-NEXT: %hhd=-123
  // CHECK-NEXT: %hd=-12345
  // CHECK-NEXT: %d=-1234567891
  // CHECK-NEXT: %ld=-1234567891
  // CHECK-NEXT: %lld=-1234567891011121314
  // CHECK-NEXT: %jd=-1234567891011121314
  // CHECK-NEXT: %zd=-1234567891011121314
  // CHECK-NEXT: %t=-1234567891011121314

  FORMAT_STRING(fmt4) = "%%i negative values:\n"
                        "\t%%hhi=%hhi\n"
                        "\t%%hi=%hi\n"
                        "\t%%i=%i\n"
                        "\t%%li=%li\n"
                        "\t%%lli=%lli\n"
                        "\t%%ji=%ji\n"
                        "\t%%zi=%zi\n"
                        "\t%%ti=%ti\n";
  ext::oneapi::experimental::printf(fmt4, hhd, hd, d, ld, lld, jd, zd, td);
  // CHECK: %i negative values:
  // CHECK-NEXT: %hhi=-123
  // CHECK-NEXT: %hi=-12345
  // CHECK-NEXT: %i=-1234567891
  // CHECK-NEXT: %li=-1234567891
  // CHECK-NEXT: %lli=-1234567891011121314
  // CHECK-NEXT: %ji=-1234567891011121314
  // CHECK-NEXT: %zi=-1234567891011121314
  // CHECK-NEXT: %ti=-1234567891011121314
}

void do_o_test() { // %o unsigned integer, octal representation
  // Some reference values
  constexpr unsigned char CHAR_VALUE = 0123;
  constexpr unsigned short SHORT_VALUE = 0123456;
  constexpr unsigned int INT_VALUE = 012345670123;
  constexpr unsigned long LONG_VALUE = INT_VALUE;
  constexpr unsigned long long LONG_LONG_VALUE = 01234567012345670123456;

  unsigned char hho = CHAR_VALUE;
  unsigned short ho = SHORT_VALUE;
  unsigned int o = INT_VALUE;
  unsigned long lo = LONG_VALUE;
  unsigned long long llo = LONG_LONG_VALUE;
  uintmax_t jo = LONG_LONG_VALUE;
  size_t zo = LONG_LONG_VALUE;
  ptrdiff_t to = LONG_LONG_VALUE;

  FORMAT_STRING(fmt1) = "%%o:\n"
                        "\t%%hho=%hho\n"
                        "\t%%ho=%ho\n"
                        "\t%%o=%o\n"
                        "\t%%lo=%lo\n"
                        "\t%%llo=%llo\n"
                        "\t%%jo=%jo\n"
                        "\t%%zo=%zo\n"
                        "\t%%to=%to\n";
  ext::oneapi::experimental::printf(fmt1, hho, ho, o, lo, llo, jo, zo, to);
  // CHECK: %o:
  // CHECK-NEXT: %hho=123
  // CHECK-NEXT: %ho=123456
  // CHECK-NEXT: %o=12345670123
  // CHECK-NEXT: %lo=12345670123
  // CHECK-NEXT: %llo=1234567012345670123456
  // CHECK-NEXT: %jo=1234567012345670123456
  // CHECK-NEXT: %zo=1234567012345670123456
  // CHECK-NEXT: %to=1234567012345670123456
}

void do_x_test() { // %x, %X unsigned integer, hexadecimal representation
  // Some reference values
  constexpr unsigned char CHAR_VALUE = 0x12;
  constexpr unsigned short SHORT_VALUE = 0x1234;
  constexpr unsigned int INT_VALUE = 0x12345678;
  constexpr unsigned long LONG_VALUE = INT_VALUE;
  constexpr unsigned long long LONG_LONG_VALUE = 0x123456789ABCDEF0;

  unsigned char hhx = CHAR_VALUE;
  unsigned short hx = SHORT_VALUE;
  unsigned int x = INT_VALUE;
  unsigned long lx = LONG_VALUE;
  unsigned long long llx = LONG_LONG_VALUE;
  uintmax_t jx = LONG_LONG_VALUE;
  size_t zx = LONG_LONG_VALUE;
  ptrdiff_t tx = LONG_LONG_VALUE;

  FORMAT_STRING(fmt1) = "%%x:\n"
                        "\t%%hhx=%hhx\n"
                        "\t%%hx=%hx\n"
                        "\t%%x=%x\n"
                        "\t%%lx=%lx\n"
                        "\t%%llx=%llx\n"
                        "\t%%jx=%jx\n"
                        "\t%%zx=%zx\n"
                        "\t%%tx=%tx\n";
  ext::oneapi::experimental::printf(fmt1, hhx, hx, x, lx, llx, jx, zx, tx);
  // CHECK: %x:
  // CHECK-NEXT: %hhx=12
  // CHECK-NEXT: %hx=1234
  // CHECK-NEXT: %x=12345678
  // CHECK-NEXT: %lx=12345678
  // CHECK-NEXT: %llx=123456789abcdef0
  // CHECK-NEXT: %jx=123456789abcdef0
  // CHECK-NEXT: %zx=123456789abcdef0
  // CHECK-NEXT: %tx=123456789abcdef0

  FORMAT_STRING(fmt2) = "%%X:\n"
                        "\t%%hhX=%hhX\n"
                        "\t%%hX=%hX\n"
                        "\t%%X=%X\n"
                        "\t%%lX=%lX\n"
                        "\t%%llX=%llX\n"
                        "\t%%jX=%jX\n"
                        "\t%%zX=%zX\n"
                        "\t%%tX=%tX\n";
  ext::oneapi::experimental::printf(fmt2, hhx, hx, x, lx, llx, jx, zx, tx);
  // CHECK: %X:
  // CHECK-NEXT: %hhX=12
  // CHECK-NEXT: %hX=1234
  // CHECK-NEXT: %X=12345678
  // CHECK-NEXT: %lX=12345678
  // CHECK-NEXT: %llX=123456789ABCDEF0
  // CHECK-NEXT: %jX=123456789ABCDEF0
  // CHECK-NEXT: %zX=123456789ABCDEF0
  // CHECK-NEXT: %tX=123456789ABCDEF0
}

void do_u_test() { // %u unsigned integer, decimal representation
  // Some reference values
  constexpr char CHAR_VALUE = 0x7B;     // 123
  constexpr short SHORT_VALUE = 0x3039; // 12345
  constexpr int INT_VALUE = 0x499602D3; // 1234567891
  constexpr long LONG_VALUE = INT_VALUE;
  constexpr long long LONG_LONG_VALUE =
      0x112210F4B2D230A2; // 1234567891011121314

  unsigned char hhu = CHAR_VALUE;
  unsigned short hu = SHORT_VALUE;
  unsigned int u = INT_VALUE;
  unsigned long lu = LONG_VALUE;
  unsigned long long llu = LONG_LONG_VALUE;
  uintmax_t ju = LONG_LONG_VALUE;
  size_t zu = LONG_LONG_VALUE;
  ptrdiff_t tu = LONG_LONG_VALUE;

  FORMAT_STRING(fmt1) = "%%u:\n"
                        "\t%%hhu=%hhu\n"
                        "\t%%hu=%hu\n"
                        "\t%%u=%u\n"
                        "\t%%lu=%lu\n"
                        "\t%%llu=%llu\n"
                        "\t%%ju=%ju\n"
                        "\t%%zu=%zu\n"
                        "\t%%tu=%tu\n";
  ext::oneapi::experimental::printf(fmt1, hhu, hu, u, lu, llu, ju, zu, tu);
  // CHECK: %u:
  // CHECK-NEXT: %hhu=123
  // CHECK-NEXT: %hu=12345
  // CHECK-NEXT: %u=1234567891
  // CHECK-NEXT: %lu=1234567891
  // CHECK-NEXT: %llu=1234567891011121314
  // CHECK-NEXT: %ju=1234567891011121314
  // CHECK-NEXT: %zu=1234567891011121314
  // CHECK-NEXT: %tu=1234567891011121314
}

class IntTest;

int main() {
  queue q;

  q.submit([](handler &cgh) {
    cgh.single_task<IntTest>([]() {
      do_d_i_test();
      do_o_test();
      do_x_test();
      do_u_test();
    });
  });
  q.wait();

  return 0;
}
