#ifndef BRUTE__FORCE_H
#define BRUTE__FORCE_H

#include "object.h"
#include "index.h"
#include "helping.h"

class CBruteForce : public CIndex{
  // ==============================================================================================================
  bool overlap (const CBoundaries& b, const CPoint& p) {
    for (size_t k = 0; k < m_Dimension; ++k)
      if (b.m_BottomLeft.m_Coordinates[k] > p.m_Coordinates[k] || b.m_TopRight.m_Coordinates[k] < p.m_Coordinates[k])
        return false;
    return true;
  }
  // ==============================================================================================================
  std::vector<CRecord*> m_Vector;
public:
  CBruteForce(int dimension) : CIndex(dimension) {}
  // ==============================================================================================================
  ~CBruteForce() {for (size_t i = 0; i < m_Vector.size(); ++i) delete m_Vector[i];};
  // ==============================================================================================================
  size_t size (void) override {return m_Vector.size();}
  // ==============================================================================================================
  size_t insert (CRecord* record) override {
    assert(record->m_Position.m_Coordinates.size() == m_Dimension);
    m_Vector.push_back(record);
    return m_Vector.size();
  }
  // ==============================================================================================================  
  std::vector<CRecord*> find_in_range (const CBoundaries& boundaries, bool sorted = true) override{
    assert(boundaries.m_BottomLeft.m_Coordinates.size() == m_Dimension);
    assert(boundaries.m_TopRight.m_Coordinates.size() == m_Dimension);

    std::vector<CRecord*> result;

    for (size_t i = 0; i < m_Vector.size(); ++i)
      if (overlap(boundaries, m_Vector[i]->m_Position))
        result.push_back(m_Vector[i]);

    if (sorted) std::sort(result.begin(), result.end(), [](const CRecord* a, const CRecord* b) {return a->m_Id < b->m_Id;});;
    
    return result;
  }
  // ==============================================================================================================  
  std::vector<size_t> find_in_range_id_s (const CBoundaries& boundaries, bool sorted = true) override {
    assert(boundaries.m_BottomLeft.m_Coordinates.size() == m_Dimension);
    assert(boundaries.m_TopRight.m_Coordinates.size() == m_Dimension);
    
    std::vector<size_t> result;
    auto tmp = find_in_range(boundaries);
    
    for (const auto& it: tmp) result.push_back(it->m_Id);
    
    if (sorted) std::sort(result.begin(), result.end());

    return result;
  }
  // ============================================================================================================== 
  std::vector<CRecord*> knn (const CPoint& p, size_t k, bool sorted = true) override {
    assert(p.m_Coordinates.size() == m_Dimension);
    assert(k > 0);

    std::vector<std::pair<double, CRecord*>> distVec;
    for (const auto& it : m_Vector)
      distVec.emplace_back(euclideanDistance(p, it->m_Position), it);
  
    std::sort(distVec.begin(), distVec.end(), [](const auto& a, const auto& b) {return a.first < b.first;});
  
    std::vector<CRecord*> result;
    for (size_t i = 0; i < std::min(k, distVec.size()); ++i)
      result.push_back(distVec[i].second);
  
    if (sorted) std::sort(result.begin(), result.end(), [](const CRecord* a, const CRecord* b) {return a->m_Id < b->m_Id;});
  
    return result;
  }
  // ==============================================================================================================  
  std::vector<size_t> knn_id_s (const CPoint& p, size_t k, bool sorted = true) override {
    assert(p.m_Coordinates.size() == m_Dimension);
    assert(k > 0);

    std::vector<size_t> result;
    auto tmp = knn(p, k);
    
    for (const auto& it: tmp)
      result.push_back(it->m_Id);
  
    if (sorted) std::sort(result.begin(), result.end());

    return result;
  }
  // ==============================================================================================================  
  bool load (const std::string& filename) override {
    printf("Forbidden operation for CBruteForce (load).\n");
    return false;
  }
  // ==============================================================================================================  
  bool save (const std::string& filename) override {
    printf("Forbidden operation for CBruteForce (save).\n");
    return false;
  }
  // ==============================================================================================================  
  void render (CGraphics* graphics, const SDL_Color& colorNode, const SDL_Color& colorBox, int topBorder) override {
    auto size = graphics->getWindowSize();
    int W = size.first, H = size.second;
    for (const auto& it: m_Vector)
      graphics->renderCircle(it->m_Position.m_Coordinates[0] + W / 2, H - (it->m_Position.m_Coordinates[1] + (H - topBorder) / 2), 5, colorNode);
  }
  // ==============================================================================================================
};

#endif //BRUTE_FORCE_H