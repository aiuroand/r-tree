#ifndef TEST_H
#define TEST_H

#include <cmath>
#include <cassert>
#include <random>
#include "rtree.h"
#include "loop.h"
#include "graphics.h"
#include "brute_force.h"
#include "helping.h"

bool compare_doubles (double a, double b) {
  return std::abs(a - b) < 1e-24; 
}

void test_parse (void) {
  assert(parseCoordinates(2, "(0,0)") == std::vector<double>({0., 0.}));
  assert(parseCoordinates(2, "(0.0,0.0)") == std::vector<double>({0., 0.}));
  assert(parseCoordinates(3, "(0,0,0.)") == std::vector<double>({0., 0., 0.}));
  assert(parseCoordinates(3, "(0,0,0.") == std::vector<double>({}));
  assert(parseCoordinates(3, "0,0,0.)") == std::vector<double>({}));
  assert(parseCoordinates(3, "(2,3, 0.)") == std::vector<double>({2., 3., 0.}));
  assert(parseCoordinates(5, "(2,  3, 0., 11, 1.2)") == std::vector<double>({2., 3., 0., 11., 1.2}));
  assert(parseCoordinates(2, "(2.)") == std::vector<double>({}));
  assert(parseCoordinates(2, "()") == std::vector<double>({}));
  assert(parseCoordinates(2, "(.0, 222.,)") == std::vector<double>({0., 222.}));
  assert(parseCoordinates(2, "(22.22, 2222222,,,)") == std::vector<double>({})); 
}

void test_calculate_growth (void) {
  // CRTree r1(2, 1, 2);
  // assert(compare_doubles(r1.calculate_growth(CBoundaries(CPoint({0., 0.}), CPoint({1., 1.})), CPoint({2., 2.})), 3.));
  // assert(compare_doubles(r1.calculate_growth(CBoundaries(CPoint({0., 0.}), CPoint({0., 1.})), CPoint({1., 1.})), 1.));

  // assert(compare_doubles(r1.calculate_growth(CBoundaries(CPoint({-1., -1.}), CPoint({1., 1.})), CPoint({2., 2.})), 5.));
  // assert(compare_doubles(r1.calculate_growth(CBoundaries(CPoint({-1., -1.}), CPoint({1., 1.})), CPoint({2., 1.})), 2.));
  // assert(compare_doubles(r1.calculate_growth(CBoundaries(CPoint({-1., -1.}), CPoint({1., 1.})), CPoint({2., 0.})), 2.));
  // assert(compare_doubles(r1.calculate_growth(CBoundaries(CPoint({-1., -1.}), CPoint({1., 1.})), CPoint({2., -1.})), 2.));
  // assert(compare_doubles(r1.calculate_growth(CBoundaries(CPoint({-1., -1.}), CPoint({1., 1.})), CPoint({2., -2.})), 5.));
  // assert(compare_doubles(r1.calculate_growth(CBoundaries(CPoint({-1., -1.}), CPoint({1., 1.})), CPoint({1., -2.})), 2.));
  // assert(compare_doubles(r1.calculate_growth(CBoundaries(CPoint({-1., -1.}), CPoint({1., 1.})), CPoint({0., -2.})), 2.));
  // assert(compare_doubles(r1.calculate_growth(CBoundaries(CPoint({-1., -1.}), CPoint({1., 1.})), CPoint({-1., -2.})), 2.));
  // assert(compare_doubles(r1.calculate_growth(CBoundaries(CPoint({-1., -1.}), CPoint({1., 1.})), CPoint({-2., -2.})), 5.));
  // assert(compare_doubles(r1.calculate_growth(CBoundaries(CPoint({-1., -1.}), CPoint({1., 1.})), CPoint({-2., -1.})), 2.));
  // assert(compare_doubles(r1.calculate_growth(CBoundaries(CPoint({-1., -1.}), CPoint({1., 1.})), CPoint({-2., 0.})), 2.));
  // assert(compare_doubles(r1.calculate_growth(CBoundaries(CPoint({-1., -1.}), CPoint({1., 1.})), CPoint({-2., 1.})), 2.));
  // assert(compare_doubles(r1.calculate_growth(CBoundaries(CPoint({-1., -1.}), CPoint({1., 1.})), CPoint({-2., 2.})), 5.));
  // assert(compare_doubles(r1.calculate_growth(CBoundaries(CPoint({-1., -1.}), CPoint({1., 1.})), CPoint({-1., 2.})), 2.));
  // assert(compare_doubles(r1.calculate_growth(CBoundaries(CPoint({-1., -1.}), CPoint({1., 1.})), CPoint({0., 2.})), 2.));
  // assert(compare_doubles(r1.calculate_growth(CBoundaries(CPoint({-1., -1.}), CPoint({1., 1.})), CPoint({1., 2.})), 2.));

  // assert(compare_doubles(r1.calculate_growth(CBoundaries(CPoint({0., 0.}), CPoint({1., 3.})), CPoint({-2., 6.})), 15.));
  // assert(compare_doubles(r1.calculate_growth(CBoundaries(CPoint({0., 0.}), CPoint({1., 3.})), CPoint({-2., -6.})), 24.));

  // assert(compare_doubles(r1.calculate_growth(CBoundaries(CPoint({0., 0.}), CPoint({1., 3.})), CPoint({1., 3.})), 0.));
  // assert(compare_doubles(r1.calculate_growth(CBoundaries(CPoint({0., 0.}), CPoint({1., 3.})), CPoint({0., 3.})), 0.));
  // assert(compare_doubles(r1.calculate_growth(CBoundaries(CPoint({0., 0.}), CPoint({1., 3.})), CPoint({0., 0.})), 0.));
  // assert(compare_doubles(r1.calculate_growth(CBoundaries(CPoint({0., 0.}), CPoint({1., 3.})), CPoint({0., 2.})), 0.));
}

void test_extend_boundaries (void) {
  // CRTree r1(2, 1, 2);
  // assert(r1.extend_boundaries(CBoundaries(CPoint({0, 0}), CPoint({1, 1})), CBoundaries(CPoint({0, 0}), CPoint({1, 1}))) == CBoundaries(CPoint({0, 0}), CPoint({1, 1})));
  // assert(r1.extend_boundaries(CBoundaries(CPoint({0, 0}), CPoint({1, 1})), CBoundaries(CPoint({0, 0}), CPoint({2, 2}))) == CBoundaries(CPoint({0, 0}), CPoint({2, 2})));
  // assert(r1.extend_boundaries(CBoundaries(CPoint({0, 0}), CPoint({1, 1})), CBoundaries(CPoint({1, 0}), CPoint({2, 1}))) == CBoundaries(CPoint({0, 0}), CPoint({2, 1})));
  // assert(r1.extend_boundaries(CBoundaries(CPoint({-1, -1}), CPoint({0, 0})), CBoundaries(CPoint({0, 0}), CPoint({1, 1}))) == CBoundaries(CPoint({-1, -1}), CPoint({1, 1})));
  // assert(r1.extend_boundaries(CBoundaries(CPoint({-1, -1}), CPoint({-1, 1})), CBoundaries(CPoint({1, -1}), CPoint({1, 0}))) == CBoundaries(CPoint({-1, -1}), CPoint({1, 1})));
}

void test_overlap (void) {
  // CRTree r1(2, 1, 2);
  // assert(r1.overlap(CBoundaries(CPoint({0, 0}), CPoint({1, 1})), CBoundaries(CPoint({0, 0}), CPoint({1, 1}))));
  // assert(!r1.overlap(CBoundaries(CPoint({0, 0}), CPoint({1, 1})), CBoundaries(CPoint({2, 2}), CPoint({3, 3}))));
  // assert(r1.overlap(CBoundaries(CPoint({0, 0}), CPoint({1, 1})), CBoundaries(CPoint({1, 1}), CPoint({2, 2}))));
  // assert(r1.overlap(CBoundaries(CPoint({0, 0}), CPoint({1.5, 1.5})), CBoundaries(CPoint({-2, -2}), CPoint({1, 1}))));
  // assert(r1.overlap(CBoundaries(CPoint({0, 0}), CPoint({10, 10})), CBoundaries(CPoint({1, -2}), CPoint({1, 10}))));
  // assert(!r1.overlap(CBoundaries(CPoint({0, 10}), CPoint({10, 10})), CBoundaries(CPoint({0, 9}), CPoint({10, 9}))));
  // assert(!r1.overlap(CBoundaries(CPoint({0, 10}), CPoint({10, 10})), CBoundaries(CPoint({0, 9.9}), CPoint({10, 9.9}))));
  // assert(!r1.overlap(CBoundaries(CPoint({0.1, 0.1}), CPoint({2, 2})), CBoundaries(CPoint({-2, -2}), CPoint({100, 0.05}))));
}

void test_point_rect_distance() {
  assert(std::abs(pointRectDist(CPoint({2, 2}), CBoundaries({CPoint({-1, -1}), CPoint({1, 1})})) -   std::sqrt(2)) < 1e-10);
  assert(std::abs(pointRectDist(CPoint({2, 1}), CBoundaries({CPoint({-1, -1}), CPoint({1, 1})})) -   std::sqrt(1)) < 1e-10);
  assert(std::abs(pointRectDist(CPoint({2, 0}), CBoundaries({CPoint({-1, -1}), CPoint({1, 1})})) -   std::sqrt(1)) < 1e-10);
  assert(std::abs(pointRectDist(CPoint({2, -1}), CBoundaries({CPoint({-1, -1}), CPoint({1, 1})})) -  std::sqrt(1)) < 1e-10);
  assert(std::abs(pointRectDist(CPoint({2, -2}), CBoundaries({CPoint({-1, -1}), CPoint({1, 1})})) -  std::sqrt(2)) < 1e-10);
  assert(std::abs(pointRectDist(CPoint({1, -2}), CBoundaries({CPoint({-1, -1}), CPoint({1, 1})})) -  std::sqrt(1)) < 1e-10);
  assert(std::abs(pointRectDist(CPoint({0, -2}), CBoundaries({CPoint({-1, -1}), CPoint({1, 1})})) -  std::sqrt(1)) < 1e-10);
  assert(std::abs(pointRectDist(CPoint({-1, -2}), CBoundaries({CPoint({-1, -1}), CPoint({1, 1})})) - std::sqrt(1)) < 1e-10);
  assert(std::abs(pointRectDist(CPoint({-2, -2}), CBoundaries({CPoint({-1, -1}), CPoint({1, 1})})) - std::sqrt(2)) < 1e-10);
  assert(std::abs(pointRectDist(CPoint({-2, -1}), CBoundaries({CPoint({-1, -1}), CPoint({1, 1})})) - std::sqrt(1)) < 1e-10);
  assert(std::abs(pointRectDist(CPoint({-2, 0}), CBoundaries({CPoint({-1, -1}), CPoint({1, 1})})) -  std::sqrt(1)) < 1e-10);
  assert(std::abs(pointRectDist(CPoint({-2, 1}), CBoundaries({CPoint({-1, -1}), CPoint({1, 1})})) -  std::sqrt(1)) < 1e-10);
  assert(std::abs(pointRectDist(CPoint({-2, 2}), CBoundaries({CPoint({-1, -1}), CPoint({1, 1})})) -  std::sqrt(2)) < 1e-10);
  assert(std::abs(pointRectDist(CPoint({-1, 2}), CBoundaries({CPoint({-1, -1}), CPoint({1, 1})})) -  std::sqrt(1)) < 1e-10);
  assert(std::abs(pointRectDist(CPoint({0, 2}), CBoundaries({CPoint({-1, -1}), CPoint({1, 1})})) -   std::sqrt(1)) < 1e-10);
  assert(std::abs(pointRectDist(CPoint({1, 2}), CBoundaries({CPoint({-1, -1}), CPoint({1, 1})})) -   std::sqrt(1)) < 1e-10);
}

void basic_insert(void) {
  CRTree r(2, 1, 3, true);
  assert(1 == r.insert(new CRecord(0, {1., 1.})));
  assert(r.size() == 1);
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({1, 1}))) == std::vector<size_t>{0});
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({0.9, 0.9}))) == std::vector<size_t>{});
  assert(r.find_in_range_id_s(CBoundaries(CPoint({-2, -2}), CPoint({2, 2}))) == std::vector<size_t>{0});
  assert(r.find_in_range_id_s(CBoundaries(CPoint({-2, -2}), CPoint({0, 0}))) == std::vector<size_t>{});
  assert(r.find_in_range_id_s(CBoundaries(CPoint({-2, 0}), CPoint({0, 2}))) == std::vector<size_t>{});
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, -2}), CPoint({2, -2}))) == std::vector<size_t>{});
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({2, 2}))) == std::vector<size_t>{0});

  assert(2 == r.insert(new CRecord(1, {2., -1.})));
  assert(r.size() == 2);
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({1, 1}))) == std::vector<size_t>({0}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({0.9, 0.9}))) == std::vector<size_t>({}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({-2, -2}), CPoint({2, 2}))) == std::vector<size_t>({0, 1}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({-2, -2}), CPoint({0, 0}))) == std::vector<size_t>({}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({-2, 0}), CPoint({0, 2}))) == std::vector<size_t>({}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, -2}), CPoint({2, 0}))) == std::vector<size_t>({1}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({2, 2}))) == std::vector<size_t>({0}));
  
  assert(3 == r.insert(new CRecord(2, {-1., -1.})));
  assert(r.size() == 3);
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({1, 1}))) == std::vector<size_t>({0}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({0.9, 0.9}))) == std::vector<size_t>({}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({-2, -2}), CPoint({2, 2}))) == std::vector<size_t>({0, 1, 2}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({-2, -2}), CPoint({0, 0}))) == std::vector<size_t>({2}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({-2, 0}), CPoint({0, 2}))) == std::vector<size_t>({}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, -2}), CPoint({2, 0}))) == std::vector<size_t>({1}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({2, 2}))) == std::vector<size_t>({0}));
  
  assert(4 == r.insert(new CRecord(3, {1., -2.})));
  assert(r.size() == 4);
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({1, 1}))) == std::vector<size_t>({0}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({0.9, 0.9}))) == std::vector<size_t>({}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({-2, -2}), CPoint({2, 2}))) == std::vector<size_t>({0, 1, 2, 3}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({-2, -2}), CPoint({0, 0}))) == std::vector<size_t>({2}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({-2, 0}), CPoint({0, 2}))) == std::vector<size_t>({}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, -2}), CPoint({2, 0}))) == std::vector<size_t>({1, 3}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({2, 2}))) == std::vector<size_t>({0}));

  assert(5 == r.insert(new CRecord(4, {3., 0.})));
  assert(r.size() == 5);
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({1, 1}))) == std::vector<size_t>({0}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({0.9, 0.9}))) == std::vector<size_t>({}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({-2, -2}), CPoint({2, 2}))) == std::vector<size_t>({0, 1, 2, 3}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({-2, -2}), CPoint({0, 0}))) == std::vector<size_t>({2}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({-2, 0}), CPoint({0, 2}))) == std::vector<size_t>({}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, -2}), CPoint({2, 0}))) == std::vector<size_t>({1, 3}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({2, 2}))) == std::vector<size_t>({0}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, -3}), CPoint({4, 3}))) == std::vector<size_t>({0, 1, 3, 4}));

  assert(6 == r.insert(new CRecord(5, {2., 0.})));
  assert(r.size() == 6);
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({1, 1}))) == std::vector<size_t>({0}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({0.9, 0.9}))) == std::vector<size_t>({}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({-2, -2}), CPoint({2, 2}))) == std::vector<size_t>({0, 1, 2, 3, 5}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({-2, -2}), CPoint({0, 0}))) == std::vector<size_t>({2}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({-2, 0}), CPoint({0, 2}))) == std::vector<size_t>({}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, -2}), CPoint({2, 0}))) == std::vector<size_t>({1, 3, 5}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({2, 2}))) == std::vector<size_t>({0, 5}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, -3}), CPoint({4, 3}))) == std::vector<size_t>({0, 1, 3, 4, 5}));

  assert(7 == r.insert(new CRecord(6, {2., 1.})));
  assert(r.size() == 7);
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({1, 1}))) == std::vector<size_t>({0}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({0.9, 0.9}))) == std::vector<size_t>({}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({-2, -2}), CPoint({2, 2}))) == std::vector<size_t>({0, 1, 2, 3, 5, 6}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({-2, -2}), CPoint({0, 0}))) == std::vector<size_t>({2}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({-2, 0}), CPoint({0, 2}))) == std::vector<size_t>({}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, -2}), CPoint({2, 0}))) == std::vector<size_t>({1, 3, 5}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({2, 2}))) == std::vector<size_t>({0, 5, 6}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, -3}), CPoint({4, 3}))) == std::vector<size_t>({0, 1, 3, 4, 5, 6}));
  
  assert(8 == r.insert(new CRecord(7, {3., 1.})));
  assert(r.size() == 8);
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({1, 1}))) == std::vector<size_t>({0}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({0.9, 0.9}))) == std::vector<size_t>({}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({-2, -2}), CPoint({2, 2}))) == std::vector<size_t>({0, 1, 2, 3, 5, 6}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({-2, -2}), CPoint({0, 0}))) == std::vector<size_t>({2}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({-2, 0}), CPoint({0, 2}))) == std::vector<size_t>({}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, -2}), CPoint({2, 0}))) == std::vector<size_t>({1, 3, 5}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({2, 2}))) == std::vector<size_t>({0, 5, 6}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, -3}), CPoint({4, 3}))) == std::vector<size_t>({0, 1, 3, 4, 5, 6, 7}));

  assert(9 == r.insert(new CRecord(8, {0., 0.5})));
  assert(r.size() == 9);
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({1, 1}))) == std::vector<size_t>({0, 8}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({0.9, 0.9}))) == std::vector<size_t>({8}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({-2, -2}), CPoint({2, 2}))) == std::vector<size_t>({0, 1, 2, 3, 5, 6, 8}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({-2, -2}), CPoint({0, 0}))) == std::vector<size_t>({2}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({-2, 0}), CPoint({0, 2}))) == std::vector<size_t>({8}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, -2}), CPoint({2, 0}))) == std::vector<size_t>({1, 3, 5}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({2, 2}))) == std::vector<size_t>({0, 5, 6, 8}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, -3}), CPoint({4, 3}))) == std::vector<size_t>({0, 1, 3, 4, 5, 6, 7, 8}));
  
  assert(10 == r.insert(new CRecord(9, {0., 0.5})));
  assert(r.size() == 10);
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({1, 1}))) == std::vector<size_t>({0, 8, 9}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({0.9, 0.9}))) == std::vector<size_t>({8, 9}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({-2, -2}), CPoint({2, 2}))) == std::vector<size_t>({0, 1, 2, 3, 5, 6, 8, 9}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({-2, -2}), CPoint({0, 0}))) == std::vector<size_t>({2}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({-2, 0}), CPoint({0, 2}))) == std::vector<size_t>({8, 9}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, -2}), CPoint({2, 0}))) == std::vector<size_t>({1, 3, 5}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({2, 2}))) == std::vector<size_t>({0, 5, 6, 8, 9}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, -3}), CPoint({4, 3}))) == std::vector<size_t>({0, 1, 3, 4, 5, 6, 7, 8, 9}));

  assert(11 == r.insert(new CRecord(10, {0., 0.})));
  assert(r.size() == 11);
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({1, 1}))) == std::vector<size_t>({0, 8, 9, 10}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({0.9, 0.9}))) == std::vector<size_t>({8, 9, 10}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({-2, -2}), CPoint({2, 2}))) == std::vector<size_t>({0, 1, 2, 3, 5, 6, 8, 9, 10}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({-2, -2}), CPoint({0, 0}))) == std::vector<size_t>({2, 10}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({-2, 0}), CPoint({0, 2}))) == std::vector<size_t>({8, 9, 10}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, -2}), CPoint({2, 0}))) == std::vector<size_t>({1, 3, 5, 10}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({2, 2}))) == std::vector<size_t>({0, 5, 6, 8, 9, 10}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, -3}), CPoint({4, 3}))) == std::vector<size_t>({0, 1, 3, 4, 5, 6, 7, 8, 9, 10}));

  assert(12 == r.insert(new CRecord(11, {-2., -2.})));
  assert(13 == r.insert(new CRecord(12, {2., 2.})));
  assert(14 == r.insert(new CRecord(13, {2., -2.})));
  assert(15 == r.insert(new CRecord(14, {-2., 2.})));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({1, 1}))) == std::vector<size_t>({0, 8, 9, 10}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({0.9, 0.9}))) == std::vector<size_t>({8, 9, 10}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({-2, -2}), CPoint({2, 2}))) == std::vector<size_t>({0, 1, 2, 3, 5, 6, 8, 9, 10, 11, 12, 13, 14}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({-2, -2}), CPoint({0, 0}))) == std::vector<size_t>({2, 10, 11}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({-2, 0}), CPoint({0, 2}))) == std::vector<size_t>({8, 9, 10, 14}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, -2}), CPoint({2, 0}))) == std::vector<size_t>({1, 3, 5, 10, 13}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({2, 2}))) == std::vector<size_t>({0, 5, 6, 8, 9, 10, 12}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, -3}), CPoint({4, 3}))) == std::vector<size_t>({0, 1, 3, 4, 5, 6, 7, 8, 9, 10, 12, 13}));
}

void basic_save(void) {
  CRTree r(2, 1, 3, true);
  CRTree r_cpy(1, 1, 2, true);

  assert(1 == r.insert(new CRecord(0, {1., 1.})));
  assert(r.save("saves/save"));
  assert(r_cpy.load("saves/save"));
  assert(r_cpy.size() == 1);
  assert(r_cpy.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({1, 1}))) == std::vector<size_t>{0});
  assert(r_cpy.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({0.9, 0.9}))) == std::vector<size_t>{});
  assert(r_cpy.find_in_range_id_s(CBoundaries(CPoint({-2, -2}), CPoint({2, 2}))) == std::vector<size_t>{0});
  assert(r_cpy.find_in_range_id_s(CBoundaries(CPoint({-2, -2}), CPoint({0, 0}))) == std::vector<size_t>{});
  assert(r_cpy.find_in_range_id_s(CBoundaries(CPoint({-2, 0}), CPoint({0, 2}))) == std::vector<size_t>{});
  assert(r_cpy.find_in_range_id_s(CBoundaries(CPoint({0, -2}), CPoint({2, -2}))) == std::vector<size_t>{});
  assert(r_cpy.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({2, 2}))) == std::vector<size_t>{0});

  assert(2 == r.insert(new CRecord(1, {2., -1.})));
  assert(r.save("saves/save"));
  assert(r_cpy.load("saves/save"));
  assert(r_cpy.size() == 2);
  assert(r_cpy.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({1, 1}))) == std::vector<size_t>({0}));
  assert(r_cpy.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({0.9, 0.9}))) == std::vector<size_t>({}));
  assert(r_cpy.find_in_range_id_s(CBoundaries(CPoint({-2, -2}), CPoint({2, 2}))) == std::vector<size_t>({0, 1}));
  assert(r_cpy.find_in_range_id_s(CBoundaries(CPoint({-2, -2}), CPoint({0, 0}))) == std::vector<size_t>({}));
  assert(r_cpy.find_in_range_id_s(CBoundaries(CPoint({-2, 0}), CPoint({0, 2}))) == std::vector<size_t>({}));
  assert(r_cpy.find_in_range_id_s(CBoundaries(CPoint({0, -2}), CPoint({2, 0}))) == std::vector<size_t>({1}));
  assert(r_cpy.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({2, 2}))) == std::vector<size_t>({0}));
  
  assert(3 == r.insert(new CRecord(2, {-1., -1.})));
  assert(r.size() == 3);
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({1, 1}))) == std::vector<size_t>({0}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({0.9, 0.9}))) == std::vector<size_t>({}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({-2, -2}), CPoint({2, 2}))) == std::vector<size_t>({0, 1, 2}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({-2, -2}), CPoint({0, 0}))) == std::vector<size_t>({2}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({-2, 0}), CPoint({0, 2}))) == std::vector<size_t>({}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, -2}), CPoint({2, 0}))) == std::vector<size_t>({1}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({2, 2}))) == std::vector<size_t>({0}));
  
  assert(4 == r.insert(new CRecord(3, {1., -2.})));
  assert(r.size() == 4);
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({1, 1}))) == std::vector<size_t>({0}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({0.9, 0.9}))) == std::vector<size_t>({}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({-2, -2}), CPoint({2, 2}))) == std::vector<size_t>({0, 1, 2, 3}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({-2, -2}), CPoint({0, 0}))) == std::vector<size_t>({2}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({-2, 0}), CPoint({0, 2}))) == std::vector<size_t>({}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, -2}), CPoint({2, 0}))) == std::vector<size_t>({1, 3}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({2, 2}))) == std::vector<size_t>({0}));

  assert(5 == r.insert(new CRecord(4, {3., 0.})));
  assert(r.size() == 5);
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({1, 1}))) == std::vector<size_t>({0}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({0.9, 0.9}))) == std::vector<size_t>({}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({-2, -2}), CPoint({2, 2}))) == std::vector<size_t>({0, 1, 2, 3}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({-2, -2}), CPoint({0, 0}))) == std::vector<size_t>({2}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({-2, 0}), CPoint({0, 2}))) == std::vector<size_t>({}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, -2}), CPoint({2, 0}))) == std::vector<size_t>({1, 3}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({2, 2}))) == std::vector<size_t>({0}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, -3}), CPoint({4, 3}))) == std::vector<size_t>({0, 1, 3, 4}));

  assert(6 == r.insert(new CRecord(5, {2., 0.})));
  assert(r.size() == 6);
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({1, 1}))) == std::vector<size_t>({0}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({0.9, 0.9}))) == std::vector<size_t>({}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({-2, -2}), CPoint({2, 2}))) == std::vector<size_t>({0, 1, 2, 3, 5}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({-2, -2}), CPoint({0, 0}))) == std::vector<size_t>({2}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({-2, 0}), CPoint({0, 2}))) == std::vector<size_t>({}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, -2}), CPoint({2, 0}))) == std::vector<size_t>({1, 3, 5}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({2, 2}))) == std::vector<size_t>({0, 5}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, -3}), CPoint({4, 3}))) == std::vector<size_t>({0, 1, 3, 4, 5}));

  assert(7 == r.insert(new CRecord(6, {2., 1.})));
  assert(r.size() == 7);
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({1, 1}))) == std::vector<size_t>({0}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({0.9, 0.9}))) == std::vector<size_t>({}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({-2, -2}), CPoint({2, 2}))) == std::vector<size_t>({0, 1, 2, 3, 5, 6}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({-2, -2}), CPoint({0, 0}))) == std::vector<size_t>({2}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({-2, 0}), CPoint({0, 2}))) == std::vector<size_t>({}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, -2}), CPoint({2, 0}))) == std::vector<size_t>({1, 3, 5}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({2, 2}))) == std::vector<size_t>({0, 5, 6}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, -3}), CPoint({4, 3}))) == std::vector<size_t>({0, 1, 3, 4, 5, 6}));
  
  assert(8 == r.insert(new CRecord(7, {3., 1.})));
  assert(r.size() == 8);
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({1, 1}))) == std::vector<size_t>({0}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({0.9, 0.9}))) == std::vector<size_t>({}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({-2, -2}), CPoint({2, 2}))) == std::vector<size_t>({0, 1, 2, 3, 5, 6}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({-2, -2}), CPoint({0, 0}))) == std::vector<size_t>({2}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({-2, 0}), CPoint({0, 2}))) == std::vector<size_t>({}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, -2}), CPoint({2, 0}))) == std::vector<size_t>({1, 3, 5}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({2, 2}))) == std::vector<size_t>({0, 5, 6}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, -3}), CPoint({4, 3}))) == std::vector<size_t>({0, 1, 3, 4, 5, 6, 7}));

  assert(9 == r.insert(new CRecord(8, {0., 0.5})));
  assert(r.size() == 9);
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({1, 1}))) == std::vector<size_t>({0, 8}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({0.9, 0.9}))) == std::vector<size_t>({8}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({-2, -2}), CPoint({2, 2}))) == std::vector<size_t>({0, 1, 2, 3, 5, 6, 8}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({-2, -2}), CPoint({0, 0}))) == std::vector<size_t>({2}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({-2, 0}), CPoint({0, 2}))) == std::vector<size_t>({8}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, -2}), CPoint({2, 0}))) == std::vector<size_t>({1, 3, 5}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({2, 2}))) == std::vector<size_t>({0, 5, 6, 8}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, -3}), CPoint({4, 3}))) == std::vector<size_t>({0, 1, 3, 4, 5, 6, 7, 8}));
  
  assert(10 == r.insert(new CRecord(9, {0., 0.5})));
  assert(r.size() == 10);
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({1, 1}))) == std::vector<size_t>({0, 8, 9}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({0.9, 0.9}))) == std::vector<size_t>({8, 9}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({-2, -2}), CPoint({2, 2}))) == std::vector<size_t>({0, 1, 2, 3, 5, 6, 8, 9}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({-2, -2}), CPoint({0, 0}))) == std::vector<size_t>({2}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({-2, 0}), CPoint({0, 2}))) == std::vector<size_t>({8, 9}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, -2}), CPoint({2, 0}))) == std::vector<size_t>({1, 3, 5}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({2, 2}))) == std::vector<size_t>({0, 5, 6, 8, 9}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, -3}), CPoint({4, 3}))) == std::vector<size_t>({0, 1, 3, 4, 5, 6, 7, 8, 9}));

  assert(11 == r.insert(new CRecord(10, {0., 0.})));
  assert(r.size() == 11);
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({1, 1}))) == std::vector<size_t>({0, 8, 9, 10}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({0.9, 0.9}))) == std::vector<size_t>({8, 9, 10}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({-2, -2}), CPoint({2, 2}))) == std::vector<size_t>({0, 1, 2, 3, 5, 6, 8, 9, 10}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({-2, -2}), CPoint({0, 0}))) == std::vector<size_t>({2, 10}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({-2, 0}), CPoint({0, 2}))) == std::vector<size_t>({8, 9, 10}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, -2}), CPoint({2, 0}))) == std::vector<size_t>({1, 3, 5, 10}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({2, 2}))) == std::vector<size_t>({0, 5, 6, 8, 9, 10}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, -3}), CPoint({4, 3}))) == std::vector<size_t>({0, 1, 3, 4, 5, 6, 7, 8, 9, 10}));

  assert(12 == r.insert(new CRecord(11, {-2., -2.})));
  assert(13 == r.insert(new CRecord(12, {2., 2.})));
  assert(14 == r.insert(new CRecord(13, {2., -2.})));
  assert(15 == r.insert(new CRecord(14, {-2., 2.})));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({1, 1}))) == std::vector<size_t>({0, 8, 9, 10}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({0.9, 0.9}))) == std::vector<size_t>({8, 9, 10}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({-2, -2}), CPoint({2, 2}))) == std::vector<size_t>({0, 1, 2, 3, 5, 6, 8, 9, 10, 11, 12, 13, 14}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({-2, -2}), CPoint({0, 0}))) == std::vector<size_t>({2, 10, 11}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({-2, 0}), CPoint({0, 2}))) == std::vector<size_t>({8, 9, 10, 14}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, -2}), CPoint({2, 0}))) == std::vector<size_t>({1, 3, 5, 10, 13}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({2, 2}))) == std::vector<size_t>({0, 5, 6, 8, 9, 10, 12}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, -3}), CPoint({4, 3}))) == std::vector<size_t>({0, 1, 3, 4, 5, 6, 7, 8, 9, 10, 12, 13}));
}

void big_insert(void) {
  double MAX = 30.;
  CRTree r(3, 5, 10, true);
  std::vector<size_t> all1;
  for (double i = 0.; i < MAX; ++i) {
    std::vector<size_t> all2;
    for (double j = 0.; j < MAX; ++j) {
      std::vector<size_t> all3;
      for (double k = 0.; k < MAX; ++k) {
        size_t id = static_cast<size_t>(i * MAX * MAX + j * MAX + k);
        all1.push_back(id);
        all2.push_back(id);
        all3.push_back(id);
        assert(id + 1 == r.insert(new CRecord(id, {i, j, k})));
        assert(r.size() == static_cast<size_t>(id + 1));
        assert(r.find_in_range_id_s(CBoundaries(CPoint({i - 0.5, j - 0.5, k - 0.5}), CPoint({i + 0.5, j + 0.5, k + 0.5}))) == std::vector<size_t>{id});
      }
      assert(r.find_in_range_id_s(CBoundaries(CPoint({i - 0.5, j - 0.5, 0 - 0.5}), CPoint({i + 0.5, j + 0.5, MAX + 0.5}))) == all3);
    }
    assert(r.find_in_range_id_s(CBoundaries(CPoint({i - 0.5, 0 - 0.5, 0 - 0.5}), CPoint({i + 0.5, MAX + 0.5, MAX + 0.5}))) == all2);
  }
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0 - 0.5, 0 - 0.5, 0 - 0.5}), CPoint({MAX + 0.5, MAX + 0.5, MAX + 0.5}))) == all1);
}

void basic_knn(void) {
  CRTree r(2, 1, 2, true);
  assert(1 == r.insert(new CRecord(0, {1., 1.})));
  assert(r.knn_id_s(CPoint({0, 0}), 1) == std::vector<size_t>({0}));
  assert(r.knn_id_s(CPoint({0, 0}), 2) == std::vector<size_t>({0}));
  assert(r.knn_id_s(CPoint({0, 0}), 3) == std::vector<size_t>({0}));

  assert(2 == r.insert(new CRecord(1, {2., -1.})));
  assert(r.knn_id_s(CPoint({0, 0}), 1) == std::vector<size_t>({0}));
  assert(r.knn_id_s(CPoint({0, 0}), 2) == std::vector<size_t>({0, 1}));
  assert(r.knn_id_s(CPoint({0, 0}), 3) == std::vector<size_t>({0, 1}));
  
  assert(3 == r.insert(new CRecord(2, {-1., -1.})));
  assert(r.knn_id_s(CPoint({0, 0}), 2) == std::vector<size_t>({0, 2}));
  assert(r.knn_id_s(CPoint({0, 0}), 3) == std::vector<size_t>({0, 1, 2}));
  assert(r.knn_id_s(CPoint({0, 0}), 4) == std::vector<size_t>({0, 1, 2}));
  
  assert(4 == r.insert(new CRecord(3, {1., -2.})));
  assert(r.knn_id_s(CPoint({0, 0}), 2) == std::vector<size_t>({0, 2}));
  assert(r.knn_id_s(CPoint({0, 0}), 4) == std::vector<size_t>({0, 1, 2, 3}));

  assert(5 == r.insert(new CRecord(4, {3., 0.})));
  assert(r.knn_id_s(CPoint({0, 0}), 2) == std::vector<size_t>({0, 2}));
  assert(r.knn_id_s(CPoint({0, 0}), 4) == std::vector<size_t>({0, 1, 2, 3}));
  assert(r.knn_id_s(CPoint({0, 0}), 5) == std::vector<size_t>({0, 1, 2, 3, 4}));
  assert(r.knn_id_s(CPoint({2, 0}), 2) == std::vector<size_t>({1, 4}));
  assert(r.knn_id_s(CPoint({2, 0}), 3) == std::vector<size_t>({0, 1, 4}));

  // assert(6 == r.insert(new CRecord(5, {2., 0.})));

  // assert(7 == r.insert(new CRecord(6, {2., 1.})));
  
  // assert(8 == r.insert(new CRecord(7, {3., 1.})));

  // assert(9 == r.insert(new CRecord(8, {0., 0.5})));
  
  // assert(10 == r.insert(new CRecord(9, {0., 0.5})));

  // assert(11 == r.insert(new CRecord(10, {0., 0.})));

  // assert(12 == r.insert(new CRecord(11, {-2., -2.})));
  // assert(13 == r.insert(new CRecord(12, {2., 2.})));
  // assert(14 == r.insert(new CRecord(13, {2., -2.})));
  // assert(15 == r.insert(new CRecord(14, {-2., 2.})));
}

void basic_insert_brute(void) {
  CBruteForce r(2);
  assert(1 == r.insert(new CRecord(0, {1., 1.})));
  assert(r.size() == 1);
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({1, 1}))) == std::vector<size_t>{0});
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({0.9, 0.9}))) == std::vector<size_t>{});
  assert(r.find_in_range_id_s(CBoundaries(CPoint({-2, -2}), CPoint({2, 2}))) == std::vector<size_t>{0});
  assert(r.find_in_range_id_s(CBoundaries(CPoint({-2, -2}), CPoint({0, 0}))) == std::vector<size_t>{});
  assert(r.find_in_range_id_s(CBoundaries(CPoint({-2, 0}), CPoint({0, 2}))) == std::vector<size_t>{});
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, -2}), CPoint({2, -2}))) == std::vector<size_t>{});
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({2, 2}))) == std::vector<size_t>{0});

  assert(2 == r.insert(new CRecord(1, {2., -1.})));
  assert(r.size() == 2);
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({1, 1}))) == std::vector<size_t>({0}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({0.9, 0.9}))) == std::vector<size_t>({}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({-2, -2}), CPoint({2, 2}))) == std::vector<size_t>({0, 1}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({-2, -2}), CPoint({0, 0}))) == std::vector<size_t>({}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({-2, 0}), CPoint({0, 2}))) == std::vector<size_t>({}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, -2}), CPoint({2, 0}))) == std::vector<size_t>({1}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({2, 2}))) == std::vector<size_t>({0}));
  
  assert(3 == r.insert(new CRecord(2, {-1., -1.})));
  assert(r.size() == 3);
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({1, 1}))) == std::vector<size_t>({0}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({0.9, 0.9}))) == std::vector<size_t>({}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({-2, -2}), CPoint({2, 2}))) == std::vector<size_t>({0, 1, 2}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({-2, -2}), CPoint({0, 0}))) == std::vector<size_t>({2}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({-2, 0}), CPoint({0, 2}))) == std::vector<size_t>({}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, -2}), CPoint({2, 0}))) == std::vector<size_t>({1}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({2, 2}))) == std::vector<size_t>({0}));
  
  assert(4 == r.insert(new CRecord(3, {1., -2.})));
  assert(r.size() == 4);
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({1, 1}))) == std::vector<size_t>({0}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({0.9, 0.9}))) == std::vector<size_t>({}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({-2, -2}), CPoint({2, 2}))) == std::vector<size_t>({0, 1, 2, 3}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({-2, -2}), CPoint({0, 0}))) == std::vector<size_t>({2}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({-2, 0}), CPoint({0, 2}))) == std::vector<size_t>({}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, -2}), CPoint({2, 0}))) == std::vector<size_t>({1, 3}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({2, 2}))) == std::vector<size_t>({0}));

  assert(5 == r.insert(new CRecord(4, {3., 0.})));
  assert(r.size() == 5);
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({1, 1}))) == std::vector<size_t>({0}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({0.9, 0.9}))) == std::vector<size_t>({}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({-2, -2}), CPoint({2, 2}))) == std::vector<size_t>({0, 1, 2, 3}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({-2, -2}), CPoint({0, 0}))) == std::vector<size_t>({2}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({-2, 0}), CPoint({0, 2}))) == std::vector<size_t>({}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, -2}), CPoint({2, 0}))) == std::vector<size_t>({1, 3}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({2, 2}))) == std::vector<size_t>({0}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, -3}), CPoint({4, 3}))) == std::vector<size_t>({0, 1, 3, 4}));

  assert(6 == r.insert(new CRecord(5, {2., 0.})));
  assert(r.size() == 6);
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({1, 1}))) == std::vector<size_t>({0}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({0.9, 0.9}))) == std::vector<size_t>({}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({-2, -2}), CPoint({2, 2}))) == std::vector<size_t>({0, 1, 2, 3, 5}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({-2, -2}), CPoint({0, 0}))) == std::vector<size_t>({2}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({-2, 0}), CPoint({0, 2}))) == std::vector<size_t>({}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, -2}), CPoint({2, 0}))) == std::vector<size_t>({1, 3, 5}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({2, 2}))) == std::vector<size_t>({0, 5}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, -3}), CPoint({4, 3}))) == std::vector<size_t>({0, 1, 3, 4, 5}));

  assert(7 == r.insert(new CRecord(6, {2., 1.})));
  assert(r.size() == 7);
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({1, 1}))) == std::vector<size_t>({0}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({0.9, 0.9}))) == std::vector<size_t>({}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({-2, -2}), CPoint({2, 2}))) == std::vector<size_t>({0, 1, 2, 3, 5, 6}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({-2, -2}), CPoint({0, 0}))) == std::vector<size_t>({2}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({-2, 0}), CPoint({0, 2}))) == std::vector<size_t>({}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, -2}), CPoint({2, 0}))) == std::vector<size_t>({1, 3, 5}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({2, 2}))) == std::vector<size_t>({0, 5, 6}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, -3}), CPoint({4, 3}))) == std::vector<size_t>({0, 1, 3, 4, 5, 6}));
  
  assert(8 == r.insert(new CRecord(7, {3., 1.})));
  assert(r.size() == 8);
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({1, 1}))) == std::vector<size_t>({0}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({0.9, 0.9}))) == std::vector<size_t>({}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({-2, -2}), CPoint({2, 2}))) == std::vector<size_t>({0, 1, 2, 3, 5, 6}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({-2, -2}), CPoint({0, 0}))) == std::vector<size_t>({2}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({-2, 0}), CPoint({0, 2}))) == std::vector<size_t>({}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, -2}), CPoint({2, 0}))) == std::vector<size_t>({1, 3, 5}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({2, 2}))) == std::vector<size_t>({0, 5, 6}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, -3}), CPoint({4, 3}))) == std::vector<size_t>({0, 1, 3, 4, 5, 6, 7}));

  assert(9 == r.insert(new CRecord(8, {0., 0.5})));
  assert(r.size() == 9);
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({1, 1}))) == std::vector<size_t>({0, 8}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({0.9, 0.9}))) == std::vector<size_t>({8}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({-2, -2}), CPoint({2, 2}))) == std::vector<size_t>({0, 1, 2, 3, 5, 6, 8}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({-2, -2}), CPoint({0, 0}))) == std::vector<size_t>({2}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({-2, 0}), CPoint({0, 2}))) == std::vector<size_t>({8}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, -2}), CPoint({2, 0}))) == std::vector<size_t>({1, 3, 5}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({2, 2}))) == std::vector<size_t>({0, 5, 6, 8}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, -3}), CPoint({4, 3}))) == std::vector<size_t>({0, 1, 3, 4, 5, 6, 7, 8}));
  
  assert(10 == r.insert(new CRecord(9, {0., 0.5})));
  assert(r.size() == 10);
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({1, 1}))) == std::vector<size_t>({0, 8, 9}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({0.9, 0.9}))) == std::vector<size_t>({8, 9}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({-2, -2}), CPoint({2, 2}))) == std::vector<size_t>({0, 1, 2, 3, 5, 6, 8, 9}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({-2, -2}), CPoint({0, 0}))) == std::vector<size_t>({2}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({-2, 0}), CPoint({0, 2}))) == std::vector<size_t>({8, 9}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, -2}), CPoint({2, 0}))) == std::vector<size_t>({1, 3, 5}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({2, 2}))) == std::vector<size_t>({0, 5, 6, 8, 9}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, -3}), CPoint({4, 3}))) == std::vector<size_t>({0, 1, 3, 4, 5, 6, 7, 8, 9}));

  assert(11 == r.insert(new CRecord(10, {0., 0.})));
  assert(r.size() == 11);
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({1, 1}))) == std::vector<size_t>({0, 8, 9, 10}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({0.9, 0.9}))) == std::vector<size_t>({8, 9, 10}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({-2, -2}), CPoint({2, 2}))) == std::vector<size_t>({0, 1, 2, 3, 5, 6, 8, 9, 10}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({-2, -2}), CPoint({0, 0}))) == std::vector<size_t>({2, 10}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({-2, 0}), CPoint({0, 2}))) == std::vector<size_t>({8, 9, 10}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, -2}), CPoint({2, 0}))) == std::vector<size_t>({1, 3, 5, 10}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({2, 2}))) == std::vector<size_t>({0, 5, 6, 8, 9, 10}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, -3}), CPoint({4, 3}))) == std::vector<size_t>({0, 1, 3, 4, 5, 6, 7, 8, 9, 10}));

  assert(12 == r.insert(new CRecord(11, {-2., -2.})));
  assert(13 == r.insert(new CRecord(12, {2., 2.})));
  assert(14 == r.insert(new CRecord(13, {2., -2.})));
  assert(15 == r.insert(new CRecord(14, {-2., 2.})));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({1, 1}))) == std::vector<size_t>({0, 8, 9, 10}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({0.9, 0.9}))) == std::vector<size_t>({8, 9, 10}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({-2, -2}), CPoint({2, 2}))) == std::vector<size_t>({0, 1, 2, 3, 5, 6, 8, 9, 10, 11, 12, 13, 14}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({-2, -2}), CPoint({0, 0}))) == std::vector<size_t>({2, 10, 11}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({-2, 0}), CPoint({0, 2}))) == std::vector<size_t>({8, 9, 10, 14}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, -2}), CPoint({2, 0}))) == std::vector<size_t>({1, 3, 5, 10, 13}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, 0}), CPoint({2, 2}))) == std::vector<size_t>({0, 5, 6, 8, 9, 10, 12}));
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0, -3}), CPoint({4, 3}))) == std::vector<size_t>({0, 1, 3, 4, 5, 6, 7, 8, 9, 10, 12, 13}));
}

void big_insert_brute(void) {
  double MAX = 30.;
  CBruteForce r(3);
  std::vector<size_t> all1;
  for (double i = 0.; i < MAX; ++i) {
    std::vector<size_t> all2;
    for (double j = 0.; j < MAX; ++j) {
      std::vector<size_t> all3;
      for (double k = 0.; k < MAX; ++k) {
        size_t id = static_cast<size_t>(i * MAX * MAX + j * MAX + k);
        all1.push_back(id);
        all2.push_back(id);
        all3.push_back(id);
        assert(id + 1 == r.insert(new CRecord(id, {i, j, k})));
        assert(r.size() == static_cast<size_t>(id + 1));
        assert(r.find_in_range_id_s(CBoundaries(CPoint({i - 0.5, j - 0.5, k - 0.5}), CPoint({i + 0.5, j + 0.5, k + 0.5}))) == std::vector<size_t>{id});
      }
      assert(r.find_in_range_id_s(CBoundaries(CPoint({i - 0.5, j - 0.5, 0 - 0.5}), CPoint({i + 0.5, j + 0.5, MAX + 0.5}))) == all3);
    }
    assert(r.find_in_range_id_s(CBoundaries(CPoint({i - 0.5, 0 - 0.5, 0 - 0.5}), CPoint({i + 0.5, MAX + 0.5, MAX + 0.5}))) == all2);
  }
  assert(r.find_in_range_id_s(CBoundaries(CPoint({0 - 0.5, 0 - 0.5, 0 - 0.5}), CPoint({MAX + 0.5, MAX + 0.5, MAX + 0.5}))) == all1);
}

void basic_knn_brute(void) {
  CBruteForce r(2);
  assert(1 == r.insert(new CRecord(0, {1., 1.})));
  assert(r.knn_id_s(CPoint({0, 0}), 1) == std::vector<size_t>({0}));
  assert(r.knn_id_s(CPoint({0, 0}), 2) == std::vector<size_t>({0}));
  assert(r.knn_id_s(CPoint({0, 0}), 3) == std::vector<size_t>({0}));

  assert(2 == r.insert(new CRecord(1, {2., -1.})));
  assert(r.knn_id_s(CPoint({0, 0}), 1) == std::vector<size_t>({0}));
  assert(r.knn_id_s(CPoint({0, 0}), 2) == std::vector<size_t>({0, 1}));
  assert(r.knn_id_s(CPoint({0, 0}), 3) == std::vector<size_t>({0, 1}));
  
  assert(3 == r.insert(new CRecord(2, {-1., -1.})));
  assert(r.knn_id_s(CPoint({0, 0}), 2) == std::vector<size_t>({0, 2}));
  assert(r.knn_id_s(CPoint({0, 0}), 3) == std::vector<size_t>({0, 1, 2}));
  assert(r.knn_id_s(CPoint({0, 0}), 4) == std::vector<size_t>({0, 1, 2}));
  
  assert(4 == r.insert(new CRecord(3, {1., -2.})));
  assert(r.knn_id_s(CPoint({0, 0}), 2) == std::vector<size_t>({0, 2}));
  assert(r.knn_id_s(CPoint({0, 0}), 4) == std::vector<size_t>({0, 1, 2, 3}));

  assert(5 == r.insert(new CRecord(4, {3., 0.})));
  assert(r.knn_id_s(CPoint({0, 0}), 2) == std::vector<size_t>({0, 2}));
  assert(r.knn_id_s(CPoint({0, 0}), 4) == std::vector<size_t>({0, 1, 2, 3}));
  assert(r.knn_id_s(CPoint({0, 0}), 5) == std::vector<size_t>({0, 1, 2, 3, 4}));
  assert(r.knn_id_s(CPoint({2, 0}), 2) == std::vector<size_t>({1, 4}));
  assert(r.knn_id_s(CPoint({2, 0}), 3) == std::vector<size_t>({0, 1, 4}));

  // assert(6 == r.insert(new CRecord(5, {2., 0.})));

  // assert(7 == r.insert(new CRecord(6, {2., 1.})));
  
  // assert(8 == r.insert(new CRecord(7, {3., 1.})));

  // assert(9 == r.insert(new CRecord(8, {0., 0.5})));
  
  // assert(10 == r.insert(new CRecord(9, {0., 0.5})));

  // assert(11 == r.insert(new CRecord(10, {0., 0.})));

  // assert(12 == r.insert(new CRecord(11, {-2., -2.})));
  // assert(13 == r.insert(new CRecord(12, {2., 2.})));
  // assert(14 == r.insert(new CRecord(13, {2., -2.})));
  // assert(15 == r.insert(new CRecord(14, {-2., 2.})));
}

void random_insert(void) {
  CBruteForce brute(4);
  CRTree rtree(4, 5, 10, true);

  std::random_device                    rand_dev{};
  std::mt19937                          gen(rand_dev());
  std::uniform_real_distribution<double> d1(-10000, 10000);
  std::uniform_real_distribution<double> d2(-11000, 11000);

  for (size_t i = 0; i < 100; ++i) {
    double a = d1(gen);
    double b = d1(gen);
    double c = d1(gen);
    double d = d1(gen);

    brute.insert(new CRecord(i, {a, b, c, d}));
    rtree.insert(new CRecord(i, {a, b, c, d}));

    for (size_t i = 0; i < 1000; ++i) {
      double l1 = d2(gen), r1 = l1 + d2(gen);
      double l2 = d2(gen), r2 = l2 + d2(gen);
      double l3 = d2(gen), r3 = l3 + d2(gen);
      double l4 = d2(gen), r4 = l4 + d2(gen);

      auto first =  brute.find_in_range_id_s(CBoundaries(CPoint({l1, l2, l3, l4}), CPoint({r1, r2, r3, r4})));
      auto second = rtree.find_in_range_id_s(CBoundaries(CPoint({l1, l2, l3, l4}), CPoint({r1, r2, r3, r4})));

      std::sort(first.begin(), first.end());
      std::sort(second.begin(), second.end());

      assert(first == second);
    }
  }
}

void random_knn(void) {
  CBruteForce brute(4);
  CRTree rtree(4, 5, 10, true);

  std::random_device                    rand_dev{};
  std::mt19937                          gen(rand_dev());
  std::uniform_real_distribution<double> d1(-10000, 10000);
  std::uniform_int_distribution<size_t> d2(1, 50);

  for (size_t i = 0; i < 100; ++i) {
    double a = d1(gen);
    double b = d1(gen);
    double c = d1(gen);
    double d = d1(gen);

    brute.insert(new CRecord(i, {a, b, c, d}));
    rtree.insert(new CRecord(i, {a, b, c, d}));

    for (size_t i = 0; i < 1000; ++i) {
      double p1 = d1(gen);
      double p2 = d1(gen);
      double p3 = d1(gen);
      double p4 = d1(gen);
      double k = d2(gen);

      auto first =  brute.knn_id_s(CPoint({p1, p2, p3, p4}), k);
      auto second = rtree.knn_id_s(CPoint({p1, p2, p3, p4}), k);

      std::sort(first.begin(), first.end());
      std::sort(second.begin(), second.end());

      assert(first == second);
    }

  }
}

void random_save(void) {
  CRTree rtree(4, 5, 10, true);
  CRTree rtree_cpy(1, 1, 2, true);

  std::random_device                    rand_dev{};
  std::mt19937                          gen(rand_dev());
  std::uniform_real_distribution<double> d1(-10000, 10000);
  std::uniform_real_distribution<double> d2(-11000, 11000);

  for (size_t i = 0; i < 100; ++i) {
    double a = d1(gen);
    double b = d1(gen);
    double c = d1(gen);
    double d = d1(gen);

    rtree.insert(new CRecord(i, {a, b, c, d}));
    assert(rtree.save("saves/save"));
    assert(rtree_cpy.load("saves/save"));

    for (size_t i = 0; i < 1000; ++i) {
      double l1 = d2(gen), r1 = l1 + d2(gen);
      double l2 = d2(gen), r2 = l2 + d2(gen);
      double l3 = d2(gen), r3 = l3 + d2(gen);
      double l4 = d2(gen), r4 = l4 + d2(gen);

      auto first = rtree_cpy.find_in_range_id_s(CBoundaries(CPoint({l1, l2, l3, l4}), CPoint({r1, r2, r3, r4})));
      auto second = rtree.find_in_range_id_s(CBoundaries(CPoint({l1, l2, l3, l4}), CPoint({r1, r2, r3, r4})));

      std::sort(first.begin(), first.end());
      std::sort(second.begin(), second.end());

      assert(first == second);
    }
  }
}

void random_qudaratic_linear(void) {
  CRTree rtree_qudratic(4, 5, 10, true);
  CRTree rtree_linear(4, 5, 10, false);

  std::random_device                    rand_dev{};
  std::mt19937                          gen(rand_dev());
  std::uniform_real_distribution<double> d1(-10000, 10000);
  std::uniform_real_distribution<double> d2(-11000, 11000);

  for (size_t i = 0; i < 100; ++i) {
    double a = d1(gen);
    double b = d1(gen);
    double c = d1(gen);
    double d = d1(gen);

    rtree_qudratic.insert(new CRecord(i, {a, b, c, d}));
    rtree_linear.insert(new CRecord(i, {a, b, c, d}));

    for (size_t i = 0; i < 1000; ++i) {
      double l1 = d2(gen), r1 = l1 + d2(gen);
      double l2 = d2(gen), r2 = l2 + d2(gen);
      double l3 = d2(gen), r3 = l3 + d2(gen);
      double l4 = d2(gen), r4 = l4 + d2(gen);

      auto first =  rtree_linear.find_in_range_id_s(CBoundaries(CPoint({l1, l2, l3, l4}), CPoint({r1, r2, r3, r4})));
      auto second = rtree_qudratic.find_in_range_id_s(CBoundaries(CPoint({l1, l2, l3, l4}), CPoint({r1, r2, r3, r4})));

      std::sort(first.begin(), first.end());
      std::sort(second.begin(), second.end());

      assert(first == second);
    }

  }
}

void run_tests (void) {
  test_calculate_growth();
  test_extend_boundaries();
  test_overlap();
  test_parse();
  test_point_rect_distance();

  basic_insert_brute();
  basic_knn_brute();
  basic_save();
  // big_insert_brute();
  
  basic_insert();
  basic_knn();

  // big_insert();

  random_insert();
  random_qudaratic_linear();
  random_knn();
  random_save();
}

#endif //TEST_H