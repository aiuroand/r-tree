#ifndef OBJECT_H
#define OBJECT_H

#include <cstring>
#include <cassert>
#include <memory>
#include <algorithm>
#include <initializer_list>
#include <vector>

class CPoint {
public:
  CPoint() = default;
  ~CPoint() = default;
  CPoint(std::initializer_list<double> il) : m_Coordinates(il) {}
  CPoint(const std::vector<double>& il) : m_Coordinates(il) {}
  CPoint(const CPoint& point) {m_Coordinates = point.m_Coordinates;}
  CPoint(size_t dimension) : m_Coordinates(dimension, 0){}
  bool operator== (const CPoint& b) {
    assert(m_Coordinates.size() == b.m_Coordinates.size());
    for (size_t i = 0; i < m_Coordinates.size(); ++i)
      if (std::abs(m_Coordinates[i] - b.m_Coordinates[i]) > 1e-10)
        return false;

    return true;
  }  
  bool operator< (const CPoint& b) {
    assert(m_Coordinates.size() == b.m_Coordinates.size());

    for (size_t i = 0; i < m_Coordinates.size(); ++i)
      if (m_Coordinates[i] >= b.m_Coordinates[i])
        return false;

    return true;
  }  

  std::vector<double> m_Coordinates;  
};


class CRecord {
public:
  CRecord() = default;
  ~CRecord() = default;
  CRecord(size_t id, std::initializer_list<double> il) : m_Id(id), m_Position(il) {}
  CRecord(size_t id, const std::vector<double>& il) : m_Id(id), m_Position(il) {}
  CRecord(size_t id, const CPoint& p) : m_Id(id), m_Position(p) {}

  size_t m_Id;
  CPoint m_Position;
};


class CBoundaries {
public:
  CBoundaries() = default;
  CBoundaries(size_t dimension) : m_BottomLeft(dimension), m_TopRight(dimension) {}
  CBoundaries(const CPoint& p) : m_BottomLeft(p), m_TopRight(p) {}
  CBoundaries(const CPoint& bottom_left, const CPoint& top_right) : m_BottomLeft(bottom_left), m_TopRight(top_right) {}
  bool operator== (const CBoundaries& b) {
    return std::abs(m_BottomLeft.m_Coordinates == b.m_BottomLeft.m_Coordinates) && std::abs(m_TopRight.m_Coordinates == b.m_TopRight.m_Coordinates);
  }

  CPoint m_BottomLeft;
  CPoint m_TopRight;
};

#endif //OBJECT_H