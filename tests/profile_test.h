#pragma once

#include "benchmark_tests.h"

namespace profile {

void ProfileBasicTest() {
  benchmark::basic_test::InvokeSumTest();
  benchmark::basic_test::InvokeSubTest();
  benchmark::basic_test::InvokeMulTest();
  benchmark::basic_test::InvokeDivTest();
}

void ProfileGaussLegendre() {
  benchmark::test_gauss_legendre::InvokeGaussLegendreTest(1000000);
}

void ProfileMatrixDeterminant() {
  benchmark::test_matrix_determinant::InvokeMatrixDeterminantTest(12);
}

void ProfileFrobeniusNorm() {
  benchmark::test_matrix_frobenius_norm::InvokeMatrixFrobeniusNormTest(500);
}

void ProfileL1Norm() {
  benchmark::test_matrix_l1_norm::InvokeMatrixL1NormTest(500);
}

void ProfileLUDecomp() {
  benchmark::test_matrix_lu_decomposition::InvokeMatrixLUDecompositionTest(500);
}

void ProfileMoorePenrose() {
  benchmark::test_matrix_moore_penrose_pseudoinverse::InvokeMatrixMoorePenrosePseudoinverseTest(7);
}

void ProfileMult() {
  benchmark::test_matrix_mult::InvokeMatrixMulTest(1000, 1000);
}

void ProfileNormalize() {
  benchmark::test_matrix_normalize::InvokeMatrixSquareNormalizeTest(1000, 1000);
}

void ProfileQR() {
  benchmark::test_matrix_qr_decomposition::InvokeMatrixQRDecompositionTest(100);
}

void ProfileSum() {
  benchmark::test_matrix_sum_sub::InvokeMatrixSumSubTest(1000, true);
}

void ProfileSub() {
  benchmark::test_matrix_sum_sub::InvokeMatrixSumSubTest(1000, false);
}

void ProfileTranspose() {
  benchmark::test_matrix_transpose::InvokeMatrixTransposeTest(500);
}

void ProfileSigmoid() {
  benchmark::test_sigmoid::InvokeSigmoidTest(100000000);
}

void ProfileSigmoidFast() {
  benchmark::test_sigmoid_fast::InvokeSigmoidFastTest(100000000);
}

}

