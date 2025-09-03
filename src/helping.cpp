#include "helping.h"

bool inside(const SDL_Rect& rect, int x, int y) {
  return x >= rect.x && x <= rect.x + rect.w && y >= rect.y && y <= rect.y + rect.h;
}

CPoint parseCoordinates(int dimension, const std::string& str) {
  std::vector<double> coords;
  
  if (str.size() < 2 || str.front() != '(' || str.back() != ')') return {};
  
  std::string content = str.substr(1, str.size() - 2);
  std::stringstream ss(content);
  std::string token;
  
  while (std::getline(ss, token, ',')) {
    size_t start = token.find_first_not_of(" \t\n");
    size_t end = token.find_last_not_of(" \t\n");
    if (start == std::string::npos || end == std::string::npos) return {};

    std::string trimmed = token.substr(start, end - start + 1);

    try {
        coords.push_back(std::stod(trimmed));
    } catch (...) {
        return {};
    }
  }
  
  if ((int)coords.size() != dimension) return {};
  return coords;
}

double euclideanDistance(const CPoint& a, const CPoint& b) {
  assert(a.m_Coordinates.size() == b.m_Coordinates.size());
  double dist = 0;
  
  for (size_t i = 0; i < a.m_Coordinates.size(); ++i)
  dist += (a.m_Coordinates[i] - b.m_Coordinates[i]) * (a.m_Coordinates[i] - b.m_Coordinates[i]);
  
  return std::sqrt(dist);
}

double pointRectDist(const CPoint& p, const CBoundaries& boundaries) {
  assert(p.m_Coordinates.size() == boundaries.m_BottomLeft.m_Coordinates.size());
  assert(p.m_Coordinates.size() == boundaries.m_TopRight.m_Coordinates.size());

  std::vector<double> vec(p.m_Coordinates.size());
  for (size_t i = 0; i < p.m_Coordinates.size(); ++i) {
    vec[i] = std::max(std::max(boundaries.m_BottomLeft.m_Coordinates[i] - p.m_Coordinates[i], 0.), p.m_Coordinates[i] - boundaries.m_TopRight.m_Coordinates[i]);
    vec[i] *= vec[i];
  }

  return std::sqrt(std::reduce(vec.begin(), vec.end()));
}

std::string getCurrentTimeString() {
  auto now = std::chrono::system_clock::now();

  std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);

  std::tm local_tm = *std::localtime(&now_time_t);

  std::ostringstream oss;
  oss << std::put_time(&local_tm, "%Y-%m-%d_%H:%M:%S.bin");

  return oss.str();
}