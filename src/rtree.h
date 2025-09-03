#ifndef R_TREE_H
#define R_TREE_H

#include <cstring>
#include <set>
#include <memory>
#include <climits>
#include <SDL2/SDL.h>
#include <cassert>
#include <queue>
#include <chrono>
#include <fstream>
#include <iostream>
#include "object.h"
#include "graphics.h"
#include "index.h"
#include "helping.h"

class CRTree : public CIndex{
// public:
  struct CNode {
    CRecord* m_Record;
    CBoundaries m_Boundaries;
    
    size_t m_Size;
    CNode* m_Parent;
    CNode** m_Next;
    // ==============================================================================================================
    CNode() = default;
    // ==============================================================================================================
    CNode(CRecord* record, CNode* parent)
    : m_Record(record),
      m_Boundaries(record->m_Position, record->m_Position),
      m_Size(0),
      m_Parent(parent),
      m_Next(nullptr)
    {}
    // ==============================================================================================================
    CNode(size_t max_records, const CBoundaries& boundaries, CNode* parent)
    : m_Record(nullptr),
      m_Boundaries(boundaries),
      m_Size(0),
      m_Parent(parent),
      m_Next(new CNode*[max_records + 1])
    {}
    // ==============================================================================================================
    ~CNode(void)
    {
      for (size_t i = 0; i < m_Size; ++i)
        delete m_Next[i];
      delete [] m_Next;
      delete m_Record;
    }
  };

  size_t m_Counter;
  size_t m_MinRecords, m_MaxRecords;
  CNode* m_Root;
  bool m_Quadratic;
 
  // ==============================================================================================================
  bool test_boundaries(CNode* node);
  // ==============================================================================================================
  double calculate_growth (const CBoundaries& boundaries, const CPoint& point);
  // ==============================================================================================================
  double calculate_growth (const CBoundaries& boundaries, const CBoundaries& new_boundaries);
  // ==============================================================================================================
  CBoundaries extend_boundaries (const CBoundaries& b1, const CBoundaries& b2);
  // ==============================================================================================================
  CBoundaries extend_boundaries (const CBoundaries& b1, const CPoint& p);
  // ==============================================================================================================
  bool overlap (const CBoundaries& b1, const CBoundaries& b2);
  // ==============================================================================================================
  bool overlap (const CBoundaries& b, const CPoint& p);
  // ==============================================================================================================
  CNode* choose_leaf (const CPoint& point);
  // ==============================================================================================================
  void erase_node(CNode* node);
  // ==============================================================================================================
  std::pair<CNode*, CNode*> quadratic_split (CNode* node, CNode* new_node);
  // ==============================================================================================================
  std::pair<CNode*, CNode*> linear_split (CNode* node, CNode* new_node);
  // ==============================================================================================================  
  std::vector<CRecord*> find_in_range_rec (CNode* node, const CBoundaries& boundaries);
  // ============================================================================================================== 
  void knn_rec (const CNode* node, const CPoint& p, std::vector<CRecord*>& neighbors, std::vector<double>& distances);
  // ==============================================================================================================
public:
  // ==============================================================================================================
  inline CRTree(int dimension, int min_records, int max_records, bool quadratic) 
  : CIndex(dimension),
    m_Counter(0),
    m_MinRecords(min_records),
    m_MaxRecords(max_records),
    m_Root(new CNode(max_records, CBoundaries(m_Dimension), nullptr)),
    m_Quadratic(quadratic) {
    assert(m_MinRecords >= 1);
    assert(m_MaxRecords > m_MinRecords);
  }
  // ==============================================================================================================
  inline ~CRTree() {delete m_Root;}
  // ==============================================================================================================
  inline size_t size (void) override {return m_Counter;}
  // ==============================================================================================================
  size_t insert (CRecord* record) override;
  // ==============================================================================================================  
  std::vector<CRecord*> find_in_range (const CBoundaries& boundaries, bool sorted = true) override;
  // ==============================================================================================================  
  std::vector<size_t> find_in_range_id_s (const CBoundaries& boundaries, bool sorted = true) override;
  // ============================================================================================================== 
  std::vector<CRecord*> knn (const CPoint& p, size_t k, bool sorted = true) override;
  // ==============================================================================================================  
  std::vector<size_t> knn_id_s (const CPoint& p, size_t k, bool sorted = true) override;
  // ==============================================================================================================  
  bool save (const std::string& filename) override;
  // ==============================================================================================================  
  bool load (const std::string& filename) override;
  // ==============================================================================================================  
  void render (CGraphics* graphics, const SDL_Color& colorNode, const SDL_Color& colorBox, int topBorder) override;
  // ==============================================================================================================  
};

#endif //R_TREE_H