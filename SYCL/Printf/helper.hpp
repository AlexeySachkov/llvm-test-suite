#ifdef __SYCL_DEVICE_ONLY__
// On device side, we have to put format string into a constant address space
// FIXME: remove this header completly once we improve the toolchain to support
// format strings in a non-constant address spaces
#define FORMAT_STRING(X) static const __attribute__((opencl_constant)) char X[]
#else
#define FORMAT_STRING(X) static const char X[]
#endif
