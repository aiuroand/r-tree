#ifndef EXPERIMENTS_H
#define EXPERIMENTS_H

#include <random>
#include <chrono>
#include "rtree.h"
#include "brute_force.h"

double experiment_insert(size_t dimension, size_t iter, bool brute = false, bool quadratic = true) {
  CIndex* index = nullptr;
  if(brute)
    index = new CBruteForce(dimension);
  else
    index = new CRTree (dimension, 5, 10, quadratic);

  std::random_device                    rand_dev{};
  std::mt19937                          gen(rand_dev());
  std::uniform_real_distribution<double> d1(-1000, 1000);
  std::uniform_real_distribution<double> d2(-1100, 1100);

  auto begin = std::chrono::steady_clock::now();
  for (size_t i = 0; i < iter; ++i) {
    std::vector<double> vec (dimension);

    for (size_t j = 0; j < vec.size(); ++j)
      vec[j] = d1(gen);

    index->insert(new CRecord(i, vec));
  }
  auto end = std::chrono::steady_clock::now();
  delete index;
  return std::chrono::duration<double, std::milli>(end - begin).count();
}

void experiment_insert() {
  printf("Bruteforce insert:\n");
  for (size_t i = 100; i < 1000000; i *= 10)
    printf("%lf ", experiment_insert(50, i, true, true));
  printf("\n\n");

  printf("RTree quadratic insert:\n");
  for (size_t i = 100; i < 1000000; i *= 10)
    printf("%lf ", experiment_insert(50, i, false, true));
  printf("\n\n");

  printf("RTree linear insert:\n");
  for (size_t i = 100; i < 1000000; i *= 10)
    printf("%lf ", experiment_insert(50, i, false, false));
  printf("\n\n");
}

double experiment_range(size_t dimension, size_t iter, size_t searches, bool brute = false, bool quadratic = true) {
    CIndex* index = nullptr;
    if(brute)
      index = new CBruteForce(dimension);
    else
      index = new CRTree (dimension, 5, 10, quadratic);
  
    std::random_device                    rand_dev{};
    std::mt19937                          gen(rand_dev());
    std::uniform_real_distribution<double> d1(-1000, 1000);
    std::uniform_real_distribution<double> d2(-1100, 1100);
  

    for (size_t i = 0; i < iter; ++i) {
      std::vector<double> vec (dimension);

      for (size_t j = 0; j < vec.size(); ++j)
        vec[j] = d1(gen);
      index->insert(new CRecord(i, vec));
    }
    
    auto begin = std::chrono::steady_clock::now();
    for (size_t i = 0; i < searches; ++i) {
      std::vector<double> l (dimension);
      std::vector<double> r (dimension);

      for (size_t j = 0; j < l.size(); ++j) {
        l[j] = d2(gen);
        r[j] = l[j] + d2(gen);
      }

      index->find_in_range_id_s(CBoundaries(l, r));
    }

    auto end = std::chrono::steady_clock::now();
    delete index;
    return std::chrono::duration<double, std::milli>(end - begin).count();
  }

void experiment_range() {
  size_t dim = 50;
  size_t iter = 10000;

  printf("Bruteforce range:\n");
  for (size_t i = 100; i < 1000000; i *= 10) 
    printf("%lf ", experiment_range(dim, iter, i, true, true));
  printf("\n\n");

  printf("RTree quadratic range:\n");
  for (size_t i = 100; i < 1000000; i *= 10)
      printf("%lf ", experiment_range(dim, iter, i, false, true));
  printf("\n\n");

  printf("RTree linear range:\n");
  for (size_t i = 100; i < 1000000; i *= 10)
      printf("%lf ", experiment_range(dim, iter, i, false, false));
  printf("\n\n");
}

double experiment_knn(size_t dimension, size_t iter, size_t searches, bool brute = false, bool quadratic = true) {
    CIndex* index = nullptr;
    if(brute)
      index = new CBruteForce(dimension);
    else
      index = new CRTree (dimension, 5, 10, quadratic);
  
    std::random_device                    rand_dev{};
    std::mt19937                          gen(rand_dev());
    std::uniform_real_distribution<double> d1(-1000, 1000);
    std::uniform_real_distribution<double> d2(-1100, 1100);
  

    for (size_t i = 0; i < iter; ++i) {
      std::vector<double> vec (dimension);

      for (size_t j = 0; j < vec.size(); ++j)
        vec[j] = d1(gen);
      index->insert(new CRecord(i, vec));
    }
    
    auto begin = std::chrono::steady_clock::now();
    for (size_t i = 0; i < searches; ++i) {
      std::vector<double> l (dimension);

      for (size_t j = 0; j < l.size(); ++j)
        l[j] = d1(gen);


      index->knn(CPoint(l), 10);
    }
    auto end = std::chrono::steady_clock::now();
    delete index;
    return std::chrono::duration<double, std::milli>(end - begin).count();
  }

void experiment_knn() {
  size_t dim = 50;
  size_t iter = 10000;

  printf("Bruteforce knn:\n");
  for (size_t i = 100; i < 1000000; i *= 10) 
    printf("%lf ", experiment_range(dim, iter, i, true, true));
  printf("\n\n");

  printf("RTree quadratic knn:\n");
  for (size_t i = 100; i < 1000000; i *= 10)
      printf("%lf ", experiment_range(dim, iter, i, false, true));
  printf("\n\n");

  printf("RTree linear knn:\n");
  for (size_t i = 100; i < 1000000; i *= 10)
      printf("%lf ", experiment_range(dim, iter, i, false, false));
  printf("\n\n");
}


void run_experiments(void) {
//   experiment_insert();
//   experiment_range();
  experiment_knn();
}

#endif //EXPERIMENTS_H