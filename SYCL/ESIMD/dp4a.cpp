//==------------------ dp4a.cpp  - DPC++ ESIMD on-device test --------------==//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
// TODO enable on Windows
// REQUIRES: linux && gpu
// RUN: %clangxx -fsycl %s -o %t.out
// RUN: %GPU_RUN_PLACEHOLDER %t.out
// TODO : Enable test for new GPU device
// XFAIL: *

#include "esimd_test_utils.hpp"

#include <CL/sycl.hpp>
#include <CL/sycl/INTEL/esimd.hpp>
#include <iostream>

using namespace cl::sycl;

int main(void) {
  constexpr unsigned SIZE = 16;
  constexpr unsigned GROUPSIZE = 1;
  using DTYPE = unsigned int;

  queue q(esimd_test::ESIMDSelector{}, esimd_test::createExceptionHandler());

  auto dev = q.get_device();
  std::cout << "Running on " << dev.get_info<info::device::name>() << "\n";
  auto ctxt = q.get_context();

  DTYPE *S0 =
      static_cast<DTYPE *>(malloc_shared(SIZE * sizeof(DTYPE), dev, ctxt));
  DTYPE *S1 =
      static_cast<DTYPE *>(malloc_shared(SIZE * sizeof(DTYPE), dev, ctxt));
  DTYPE *S2 =
      static_cast<DTYPE *>(malloc_shared(SIZE * sizeof(DTYPE), dev, ctxt));

  DTYPE *RES =
      static_cast<DTYPE *>(malloc_shared(SIZE * sizeof(DTYPE), dev, ctxt));

  for (unsigned i = 0; i < SIZE; ++i) {
    S0[i] = 0x32;
    S1[i] = 0x0102037F;
    S2[i] = 0x0102037F;
    RES[i] = 0;
  }

  cl::sycl::range<1> GroupRange{1};

  cl::sycl::range<1> TaskRange{GROUPSIZE};
  cl::sycl::nd_range<1> Range(GroupRange, TaskRange);

  try {
    auto e = q.submit([&](handler &cgh) {
      cgh.parallel_for<class Test>(
          Range, [=](nd_item<1> ndi) SYCL_ESIMD_KERNEL {
            using namespace sycl::INTEL::gpu;

            simd<DTYPE, SIZE> src0(0);
            src0 = block_load<DTYPE, SIZE>(S0);

            simd<DTYPE, SIZE> src1(0);
            src1 = block_load<DTYPE, SIZE>(S1);

            simd<DTYPE, SIZE> src2(0);
            src2 = block_load<DTYPE, SIZE>(S2);

            auto res =
                esimd_dp4a<DTYPE, DTYPE, DTYPE, DTYPE, SIZE>(src0, src1, src2);
            block_store<DTYPE, SIZE>(RES, res);
          });
    });
    e.wait();
  } catch (cl::sycl::exception const &e) {
    std::cout << "SYCL exception caught: " << e.what() << '\n';
    return e.get_cl_code();
  }

  int err_cnt = 0;
  for (unsigned i = 0; i < SIZE; ++i) {
    if (RES[i] != 0x3F41) {
      if (++err_cnt < 10) {
        std::cout << "failed at index " << i << ", " << RES[i]
                  << " != " << 0x3F41 << "\n";
      }
    }
  }

  std::cout << (err_cnt > 0 ? "FAILED\n" : "Passed\n");
  return err_cnt > 0 ? 1 : 0;
}
