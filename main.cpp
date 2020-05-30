// Подсоединяем хедер файл, включающий в себя все бенчмарк-тесты
#include "benchmark_tests.h"
#include "validation_tests.h"
#include "test_manager.h"
#include "profile_test.h"

void AddBenchmarkTest(int argc, char** argv) {
  auto manager = TestManager(argc, argv);
  manager.AddBenchmarkSetTest(benchmark::basic_test::CreateTestSet());
  manager.AddBenchmarkSetTest(benchmark::test_gauss_legendre::CreateTestSet());
  manager.AddBenchmarkSetTest(benchmark::test_matrix_frobenius_norm::CreateTestSet());
  manager.AddBenchmarkSetTest(benchmark::test_matrix_l1_norm::CreateTestSet());
  manager.AddBenchmarkSetTest(benchmark::test_matrix_lu_decomposition::CreateTestSet());
  manager.AddBenchmarkSetTest(benchmark::test_matrix_mult::CreateTestSet());
  manager.AddBenchmarkSetTest(benchmark::test_matrix_normalize::CreateTestSet());
  manager.AddBenchmarkSetTest(benchmark::test_matrix_qr_decomposition::CreateTestSet());
  manager.AddBenchmarkSetTest(benchmark::test_matrix_sum_sub::CreateTestSet());
  manager.AddBenchmarkSetTest(benchmark::test_sigmoid::CreateTestSet());
  manager.AddBenchmarkSetTest(benchmark::test_sigmoid_fast::CreateTestSet());
  manager.AddBenchmarkSetTest(benchmark::test_matrix_moore_penrose_pseudoinverse::CreateTestSet());
  manager.AddBenchmarkSetTest(benchmark::test_matrix_determinant::CreateTestSet());
  manager.Run();
}

void AddValidationTest(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  int result = RUN_ALL_TESTS();
  if (result) {
    std::cerr << "Some test goes wrong" << std::endl;
    exit(1);
  }
  else {
    std::cerr << "All is good" << std::endl;
  }
}

void AddProfileTest() {
  using namespace profile;
  ProfileBasicTest();
  std::cout << "Profile Gauss" << std::endl;
  ProfileGaussLegendre();
  std::cout << "Profile Determinant" << std::endl;
  ProfileMatrixDeterminant();
  std::cout << "Profile Frobenius" << std::endl;
  ProfileFrobeniusNorm(); 
  std::cout << "Profile L1" << std::endl;
  ProfileL1Norm();
  std::cout << "Profile LU" << std::endl;
  ProfileLUDecomp();
  std::cout << "Profile Moore Penrouse" << std::endl;
  ProfileMoorePenrose();
  std::cout << "Profile Mult" << std::endl;
  ProfileMult();
  std::cout << "Profile Normalize" << std::endl;
  ProfileNormalize();
  std::cout << "Profile QR" << std::endl;
  ProfileQR();
  std::cout << "Profile Sum" << std::endl;
  ProfileSum();
  std::cout << "Profile Sub" << std::endl;
  ProfileSub();
  std::cout << "Profile Transpose" << std::endl;
  ProfileTranspose();
  std::cout << "Profile Sigmoid" << std::endl;
  ProfileSigmoid();
  std::cout << "Profile Sigmoid fast" << std::endl;
  ProfileSigmoidFast();
}

int main(int argc, char** argv) {
  //AddValidationTest(argc, argv);
  AddBenchmarkTest(argc, argv);
  return 0;
}
