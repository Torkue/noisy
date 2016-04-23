// dsa.cpp
//
// Implementation details for diamond-square algorithm

float** dsa (float exponent, float roughness) {
  std::mt19937 gen;
  auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
  std::uniform_real_distribution<float> dist(-1.0f,1.0f);
  gen.seed(seed);

  // seed and create a distribution range for floating point rng
  float** field;                // 2D height field, to be calloc'd as 2D array
  int exp = 0;                  // grid size exponent
  float avg = 0;                // value average
  int half;                     // half of iterations, used for stepping
  float roughness = 0.0f;       // roughness
  std::string filename = "bitmap.bmp";

}
