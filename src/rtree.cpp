#include "rtree.h"

// ==============================================================================================================
bool CRTree::test_boundaries(CNode* node) {
  for (size_t i = 0; i < node->m_Size; ++i) {
    auto& my = node->m_Boundaries;
    auto& inter = node->m_Next[i]->m_Boundaries;
    if (my.m_BottomLeft.m_Coordinates[0] > inter.m_BottomLeft.m_Coordinates[0] 
     || my.m_BottomLeft.m_Coordinates[1] > inter.m_BottomLeft.m_Coordinates[1]
     || my.m_TopRight.m_Coordinates[0] < inter.m_TopRight.m_Coordinates[0]
     || my.m_TopRight.m_Coordinates[1] < inter.m_TopRight.m_Coordinates[1] 
     || !test_boundaries(node->m_Next[i]))
      return false;
      
  }
  return true;
}
// ==============================================================================================================
double CRTree::calculate_growth (const CBoundaries& boundaries, const CPoint& point) {
  double original_product = 1;
  for (size_t i = 0; i < m_Dimension; ++i)
    original_product *= std::abs(boundaries.m_TopRight.m_Coordinates[i] - boundaries.m_BottomLeft.m_Coordinates[i]);

  double new_product = 1;
  for (size_t i = 0; i < m_Dimension; ++i) {
    new_product *= std::abs(std::max(boundaries.m_TopRight.m_Coordinates[i], point.m_Coordinates[i]) 
                          - std::min(boundaries.m_BottomLeft.m_Coordinates[i], point.m_Coordinates[i]));
  }
  return new_product - original_product;
}
// ==============================================================================================================
double CRTree::calculate_growth (const CBoundaries& boundaries, const CBoundaries& new_boundaries) {
  double original_product = 1;
  double new_product = 1;

  for (size_t i = 0; i < m_Dimension; ++i)
    original_product *= std::abs(boundaries.m_TopRight.m_Coordinates[i] - boundaries.m_BottomLeft.m_Coordinates[i]);

  for (size_t i = 0; i < m_Dimension; ++i)
    new_product *= std::abs(std::max(boundaries.m_TopRight.m_Coordinates[i], new_boundaries.m_TopRight.m_Coordinates[i]) 
                          - std::min(boundaries.m_BottomLeft.m_Coordinates[i], new_boundaries.m_BottomLeft.m_Coordinates[i]));

  return new_product - original_product;
}
// ==============================================================================================================
CBoundaries CRTree::extend_boundaries (const CBoundaries& b1, const CBoundaries& b2) {
  CBoundaries res(m_Dimension);
  for (size_t k = 0; k < m_Dimension; ++k) {
    res.m_BottomLeft.m_Coordinates[k] = std::min(b1.m_BottomLeft.m_Coordinates[k], b2.m_BottomLeft.m_Coordinates[k]);
    res.m_TopRight.m_Coordinates[k]   = std::max(b1.m_TopRight.m_Coordinates[k],   b2.m_TopRight.m_Coordinates[k]);
  }

  return res;
}
// ==============================================================================================================
CBoundaries CRTree::extend_boundaries (const CBoundaries& b1, const CPoint& p) {
  return extend_boundaries(b1, CBoundaries(p));
}
// ==============================================================================================================
bool CRTree::overlap (const CBoundaries& b1, const CBoundaries& b2) {
  for (size_t k = 0; k < m_Dimension; ++k)
    if (b2.m_BottomLeft.m_Coordinates[k] > b1.m_TopRight.m_Coordinates[k] || b2.m_TopRight.m_Coordinates[k] < b1.m_BottomLeft.m_Coordinates[k])
      return false;

  return true;
}
// ==============================================================================================================
bool CRTree::overlap (const CBoundaries& b, const CPoint& p) {
  return overlap(b, CBoundaries(p));
}
// ==============================================================================================================
CRTree::CNode* CRTree::choose_leaf (const CPoint& point) {
  CNode* current = m_Root;
  if (m_Counter == 0) return current;

  while (current->m_Next && current->m_Next[0]->m_Next) {
    double growth = DBL_MAX;
    double area = DBL_MAX;
    CNode* next = nullptr;

    for (size_t i = 0; i < current->m_Size; ++i) {
      const auto& boundaries = current->m_Next[i]->m_Boundaries;
      double new_growth = calculate_growth(boundaries, point);
  
      double new_area = 1;
      for (size_t j = 0; j < m_Dimension; ++j)
        new_area *= std::abs(boundaries.m_TopRight.m_Coordinates[j] - boundaries.m_BottomLeft.m_Coordinates[j]);

      if (new_growth < growth 
       || (std::abs(new_growth - growth) < 1e-10 && (new_area < area || std::abs(new_area - area) < 1e-10))) {
        area = new_area;
        growth = new_growth;
        next = current->m_Next[i];
      }
    }
    current = next;

  }
  return current;
}
// ==============================================================================================================
void CRTree::erase_node(CNode* node) {
  if (!node) return;

  node->m_Parent = nullptr;
  node->m_Record = nullptr;
  for (size_t i = 0; i < node->m_Size; ++i)
    node->m_Next[i] = nullptr;

  delete node;
}
// ==============================================================================================================
std::pair<CRTree::CNode*, CRTree::CNode*> CRTree::quadratic_split (CNode* node, CNode* new_node) {
  CNode* first_pos = node->m_Next[0];
  CNode* second_pos = node->m_Next[0];
  double max_area = 0;
    
  node->m_Next[node->m_Size++] = new_node;
    
  for (size_t i = 0; i < node->m_Size; ++i)
     for (size_t j = 0; j < node->m_Size; ++j) {
      if (i == j) continue;
      CNode* tmp_first = node->m_Next[i];
      CNode* tmp_second = node->m_Next[j];
      
      double area = 1;
      for (size_t k = 0; k < m_Dimension; ++k)
      area *= std::abs(std::max(tmp_first->m_Boundaries.m_TopRight.m_Coordinates[k], tmp_second->m_Boundaries.m_TopRight.m_Coordinates[k]) 
                     - std::min(tmp_first->m_Boundaries.m_BottomLeft.m_Coordinates[k], tmp_second->m_Boundaries.m_BottomLeft.m_Coordinates[k]));
      
      if (area > max_area) {
        first_pos = node->m_Next[i];
        second_pos = node->m_Next[j];
        max_area = area;
    }
  }

  CNode* first_new  = new CNode(m_MaxRecords, first_pos->m_Boundaries, nullptr); 
  CNode* second_new = new CNode(m_MaxRecords, second_pos->m_Boundaries, nullptr);
    
  for (size_t i = 0; i < node->m_Size; ++i) {
    double first_growth = calculate_growth(first_new->m_Boundaries, node->m_Next[i]->m_Boundaries);
    double second_growth = calculate_growth(second_new->m_Boundaries, node->m_Next[i]->m_Boundaries);
    
    if (first_new->m_Size < m_MinRecords && node->m_Size - i == m_MinRecords - first_new->m_Size) {
      node->m_Next[i]->m_Parent = first_new;
      first_new->m_Next[first_new->m_Size++] = node->m_Next[i];
      first_new->m_Boundaries = extend_boundaries(first_new->m_Boundaries, node->m_Next[i]->m_Boundaries);
    }
    else if (second_new->m_Size < m_MinRecords && node->m_Size - i == m_MinRecords - second_new->m_Size) {
      node->m_Next[i]->m_Parent = second_new;
      second_new->m_Next[second_new->m_Size++] = node->m_Next[i];
      second_new->m_Boundaries = extend_boundaries(second_new->m_Boundaries, node->m_Next[i]->m_Boundaries);
    }
    else if (first_growth < second_growth) {
      node->m_Next[i]->m_Parent = first_new;
      first_new->m_Next[first_new->m_Size++] = node->m_Next[i];
      first_new->m_Boundaries = extend_boundaries(first_new->m_Boundaries, node->m_Next[i]->m_Boundaries);
    } 
    else {
      node->m_Next[i]->m_Parent = second_new;
      second_new->m_Next[second_new->m_Size++] = node->m_Next[i];
      second_new->m_Boundaries = extend_boundaries(second_new->m_Boundaries, node->m_Next[i]->m_Boundaries);
    }
  }
  return {first_new, second_new};
}
// ==============================================================================================================
std::pair<CRTree::CNode*, CRTree::CNode*> CRTree::linear_split (CNode* node, CNode* new_node) {
  node->m_Next[node->m_Size++] = new_node;

  CNode* first_pos = node->m_Next[0];
  CNode* second_pos = node->m_Next[0];
  double best_separation = DBL_MIN;

  for (size_t d = 0; d < m_Dimension; ++d) {
    double min_top = DBL_MAX;
    double max_bot = DBL_MIN;
    double min = DBL_MAX;
    double max = DBL_MIN;
    CNode* current_first_pos = node->m_Next[0];
    CNode* current_second_pos = node->m_Next[0];

    for (size_t i = 0; i < node->m_Size; ++i) {
      if (node->m_Next[i]->m_Boundaries.m_BottomLeft.m_Coordinates[d] < min)
        min = node->m_Next[i]->m_Boundaries.m_BottomLeft.m_Coordinates[d];
      if (node->m_Next[i]->m_Boundaries.m_BottomLeft.m_Coordinates[d] > max_bot) {
        max_bot = node->m_Next[i]->m_Boundaries.m_BottomLeft.m_Coordinates[d];
        current_first_pos = node->m_Next[i];
      }

      if (node->m_Next[i]->m_Boundaries.m_TopRight.m_Coordinates[d] > max)
        max = node->m_Next[i]->m_Boundaries.m_TopRight.m_Coordinates[d];
      if (node->m_Next[i]->m_Boundaries.m_TopRight.m_Coordinates[d] < min_top) {
        min_top = node->m_Next[i]->m_Boundaries.m_TopRight.m_Coordinates[d];
        current_second_pos = node->m_Next[i];
      }
    }
    double separation = (max_bot - min_top) / (max - min);

    if (separation > best_separation) {
      first_pos = current_first_pos;
      second_pos = current_second_pos;
      best_separation = separation;
    }
  }

  CNode* first_new  = new CNode(m_MaxRecords, first_pos->m_Boundaries, nullptr); 
  CNode* second_new = new CNode(m_MaxRecords, second_pos->m_Boundaries, nullptr);
    
  for (size_t i = 0; i < node->m_Size; ++i) {
    double first_growth = calculate_growth(first_new->m_Boundaries, node->m_Next[i]->m_Boundaries);
    double second_growth = calculate_growth(second_new->m_Boundaries, node->m_Next[i]->m_Boundaries);
    
    if (first_new->m_Size < m_MinRecords && node->m_Size - i == m_MinRecords - first_new->m_Size) {
      node->m_Next[i]->m_Parent = first_new;
      first_new->m_Next[first_new->m_Size++] = node->m_Next[i];
      first_new->m_Boundaries = extend_boundaries(first_new->m_Boundaries, node->m_Next[i]->m_Boundaries);
    }
    else if (second_new->m_Size < m_MinRecords && node->m_Size - i == m_MinRecords - second_new->m_Size) {
      node->m_Next[i]->m_Parent = second_new;
      second_new->m_Next[second_new->m_Size++] = node->m_Next[i];
      second_new->m_Boundaries = extend_boundaries(second_new->m_Boundaries, node->m_Next[i]->m_Boundaries);
    }
    else if (first_growth < second_growth) {
      node->m_Next[i]->m_Parent = first_new;
      first_new->m_Next[first_new->m_Size++] = node->m_Next[i];
      first_new->m_Boundaries = extend_boundaries(first_new->m_Boundaries, node->m_Next[i]->m_Boundaries);
      
    } 
    else {
      node->m_Next[i]->m_Parent = second_new;
      second_new->m_Next[second_new->m_Size++] = node->m_Next[i];
      second_new->m_Boundaries = extend_boundaries(second_new->m_Boundaries, node->m_Next[i]->m_Boundaries);
    }
  }

  return {first_new, second_new};
}
// ==============================================================================================================
size_t CRTree::insert (CRecord* record) {
  assert(record->m_Position.m_Coordinates.size() == m_Dimension);

  CNode* node = choose_leaf(record->m_Position);

  if (node->m_Size < m_MaxRecords) {
    node->m_Next[node->m_Size++] = new CNode(record, node);
    CNode* tmp = node;
    while (tmp) {
      tmp->m_Boundaries = extend_boundaries(tmp->m_Boundaries, record->m_Position);
      tmp = tmp->m_Parent;
    }
  }
  else {
    std::pair<CNode*, CNode*> pair;

    if (m_Quadratic)
      pair = quadratic_split(node, new CNode(record, nullptr));
    else
      pair = linear_split(node, new CNode(record, nullptr));

    CNode* parent = node->m_Parent;
    erase_node(node);

    bool split_root = true;
    while (parent) {
      for (size_t i = 0; i < parent->m_Size; ++i)
        if (parent->m_Next[i] == node) {
          parent->m_Next[i] = pair.first;
          parent->m_Next[i]->m_Parent = parent;
          CNode* tmp = parent;
          while (tmp) {
            tmp->m_Boundaries = extend_boundaries(tmp->m_Boundaries, pair.first->m_Boundaries);
            tmp = tmp->m_Parent;
          }
        }
        
      if (parent->m_Size < m_MaxRecords) { 
        pair.second->m_Parent = parent;
        parent->m_Next[parent->m_Size++] = pair.second;
        CNode* tmp = parent;
        while (tmp) {
          tmp->m_Boundaries = extend_boundaries(tmp->m_Boundaries, pair.second->m_Boundaries);
          tmp = tmp->m_Parent;
        }
        split_root = false;
        break;
      }
      else {
        if (m_Quadratic)
          pair = quadratic_split(parent, pair.second);
        else 
          pair = linear_split(parent, pair.second);

        node = parent;
        parent = parent->m_Parent;
        erase_node(node);
      }
    }

    if (split_root) {
      m_Root = new CNode(m_MaxRecords, CBoundaries(extend_boundaries(pair.first->m_Boundaries, pair.second->m_Boundaries)), nullptr);
      pair.first->m_Parent = m_Root;
      pair.second->m_Parent = m_Root;
      m_Root->m_Next[m_Root->m_Size++] = pair.first; 
      m_Root->m_Next[m_Root->m_Size++] = pair.second;
    }
  }

  return ++m_Counter;
}
// ==============================================================================================================  
std::vector<CRecord*> CRTree::find_in_range_rec (CNode* node, const CBoundaries& boundaries) {
  std::vector<CRecord*> result;

  if (node->m_Record)
    return {node->m_Record};
  for (size_t i = 0; i < node->m_Size; ++i) {
    if (overlap(node->m_Next[i]->m_Boundaries, boundaries)) {
      auto tmp = find_in_range_rec(node->m_Next[i], boundaries);
      result.insert(result.end(), tmp.begin(), tmp.end());
    }
  }
  return result;
}
// ==============================================================================================================  
std::vector<CRecord*> CRTree::find_in_range (const CBoundaries& boundaries, bool sorted) {
  assert(boundaries.m_BottomLeft.m_Coordinates.size() == m_Dimension);
  assert(boundaries.m_TopRight.m_Coordinates.size() == m_Dimension);
  
  auto tmp = find_in_range_rec(m_Root, boundaries);
  
  if (sorted) std::sort(tmp.begin(), tmp.end(), [](const CRecord* a, const CRecord* b) {return a->m_Id < b->m_Id;});

  return tmp;
}
// ==============================================================================================================  
std::vector<size_t> CRTree::find_in_range_id_s (const CBoundaries& boundaries, bool sorted) {
  assert(boundaries.m_BottomLeft.m_Coordinates.size() == m_Dimension);
  assert(boundaries.m_TopRight.m_Coordinates.size() == m_Dimension);

  std::vector<size_t> res;
  auto tmp = find_in_range_rec(m_Root, boundaries);

  for (const auto& it: tmp)
    res.push_back(it->m_Id);

  if (sorted) std::sort(res.begin(), res.end());

  return res;
}
// ============================================================================================================== 
void CRTree::knn_rec (const CNode* node, const CPoint& p, std::vector<CRecord*>& neighbors, std::vector<double>& distances) {
  std::vector<std::pair<double, CNode*>> activeBranch;

  if (node->m_Record)
    for (size_t i = 0; i < distances.size(); ++i)
      if (distances[i] > euclideanDistance(node->m_Record->m_Position, p)) {
         for (size_t j = distances.size() - 1; j > i; --j) {
          distances[j] = distances[j - 1];
          neighbors[j] = neighbors[j - 1];
        }
        distances[i] = euclideanDistance(node->m_Record->m_Position, p);
        neighbors[i] = node->m_Record;
        return;
      }

  for (size_t i = 0; i < node->m_Size; ++i)
    activeBranch.emplace_back(pointRectDist(p, node->m_Next[i]->m_Boundaries), node->m_Next[i]);

  std::sort(activeBranch.begin(), activeBranch.end(), [](const auto& a, const auto& b) {return a.first < b.first;});

  for (size_t i = 0; i < activeBranch.size(); ++i)
    if (activeBranch[i].first < distances.back())
      knn_rec(activeBranch[i].second, p, neighbors, distances);
}
// ============================================================================================================== 
std::vector<CRecord*> CRTree::knn (const CPoint& p, size_t k, bool sorted) {
  assert(p.m_Coordinates.size() == m_Dimension);
  assert(k > 0);
  
  std::vector<CRecord*> tmp(std::min(k, m_Counter), nullptr);
  std::vector<double> distances(std::min(k, m_Counter), DBL_MAX);

  knn_rec(m_Root, p, tmp, distances);

  if (sorted) std::sort(tmp.begin(), tmp.end(), [](const CRecord* a, const CRecord* b) {return a->m_Id < b->m_Id;});
  
  return tmp;
}
// ==============================================================================================================  
std::vector<size_t> CRTree::knn_id_s (const CPoint& p, size_t k, bool sorted) {
  assert(p.m_Coordinates.size() == m_Dimension);
  assert(k > 0);

  std::vector<CRecord*> tmp(std::min(k, m_Counter), nullptr);
  std::vector<double> distances(std::min(k, m_Counter), DBL_MAX);

  knn_rec(m_Root, p, tmp, distances);

  std::vector<size_t> res;

  for (const auto& it: tmp)
    res.push_back(it->m_Id);

  if (sorted) std::sort(res.begin(), res.end());

  return res;
} 
// ============================================================================================================== 
bool CRTree::save(const std::string& filename) {

  std::ofstream outStream;
  outStream.open(filename, std::ios::out | std::ios::binary );
  if (!outStream.is_open()) return false;

  outStream.write((char*) &m_Dimension, sizeof(size_t));
  if (outStream.fail() || outStream.bad()) return false;

  outStream.write((char*) &m_Counter, sizeof(size_t));
  if (outStream.fail() || outStream.bad()) return false;
  
  outStream.write((char*) &m_MinRecords, sizeof(size_t));
  if (outStream.fail() || outStream.bad()) return false;

  outStream.write((char*) &m_MaxRecords, sizeof(size_t));
  if (outStream.fail() || outStream.bad()) return false;

  outStream.write((char*) &m_Quadratic, sizeof(bool));
  if (outStream.fail() || outStream.bad()) return false;

  std::queue<CNode*> q;
  q.push(m_Root);

  while (!q.empty()) {
    CNode* tmp = q.front(); q.pop();
    
    // printf("%zu %lf %lf %lf %lf\n", tmp->m_Size, tmp->m_Boundaries.m_BottomLeft.m_Coordinates[0], tmp->m_Boundaries.m_BottomLeft.m_Coordinates[1],
    //                                              tmp->m_Boundaries.m_TopRight.m_Coordinates[0], tmp->m_Boundaries.m_TopRight.m_Coordinates[1]);

    outStream.write((char*) &tmp->m_Size, sizeof(size_t));
    if (outStream.fail() || outStream.bad()) return false;
    
    if (tmp->m_Size == 0) {
      outStream.write((char*) &tmp->m_Record->m_Id, sizeof(size_t));
      if (outStream.fail() || outStream.bad()) return false;

      outStream.write((char*) &tmp->m_Record->m_Position.m_Coordinates[0], sizeof(double) * m_Dimension);
      if (outStream.fail() || outStream.bad()) return false;
  
    }
    else {
      outStream.write((char*) &tmp->m_Boundaries.m_BottomLeft.m_Coordinates[0], sizeof(double) * m_Dimension);
      if (outStream.fail() || outStream.bad()) return false;

      outStream.write((char*) &tmp->m_Boundaries.m_TopRight.m_Coordinates[0], sizeof(double) * m_Dimension);
      if (outStream.fail() || outStream.bad()) return false;

      for (size_t i = 0; i < tmp->m_Size; ++i)
        q.push(tmp->m_Next[i]);
    }
  }

  return true;
}
// ============================================================================================================== 
bool CRTree::load(const std::string& filename) {
  // printf("load\n");
  std::ifstream inStream;
  inStream.open(filename, std::ios::in | std::ios::binary);
  if (!inStream.is_open()) return false;

  inStream.read((char*) &m_Dimension, sizeof(size_t));
  if (inStream.fail() || inStream.bad()) return false;

  inStream.read((char*) &m_Counter, sizeof(size_t));
  if (inStream.fail() || inStream.bad()) return false;
  
  inStream.read((char*) &m_MaxRecords, sizeof(size_t));
  if (inStream.fail() || inStream.bad()) return false;

  inStream.read((char*) &m_MaxRecords, sizeof(size_t));
  if (inStream.fail() || inStream.bad()) return false;

  inStream.read((char*) &m_Quadratic, sizeof(bool));
  if (inStream.fail() || inStream.bad()) return false;

  delete m_Root;
  m_Root = new CNode();

  inStream.read((char*) &m_Root->m_Size, sizeof(size_t));
  if (inStream.fail() || inStream.bad()) return false;

  m_Root->m_Boundaries.m_BottomLeft.m_Coordinates.resize(m_Dimension);
  m_Root->m_Boundaries.m_TopRight.m_Coordinates.resize(m_Dimension);

  inStream.read((char*) &m_Root->m_Boundaries.m_BottomLeft.m_Coordinates[0], sizeof(double) * m_Dimension);
  if (inStream.fail() || inStream.bad()) return false;

  inStream.read((char*) &m_Root->m_Boundaries.m_TopRight.m_Coordinates[0], sizeof(double) * m_Dimension);
  if (inStream.fail() || inStream.bad()) return false;

  // printf("%zu %lf %lf %lf %lf\n", m_Root->m_Size, m_Root->m_Boundaries.m_BottomLeft.m_Coordinates[0], m_Root->m_Boundaries.m_BottomLeft.m_Coordinates[1],
  //                                                 m_Root->m_Boundaries.m_TopRight.m_Coordinates[0], m_Root->m_Boundaries.m_TopRight.m_Coordinates[1]);

  std::queue<CNode*> q;
  m_Root->m_Parent = nullptr;
  m_Root->m_Record = nullptr;
  m_Root->m_Next = new CNode*[m_MaxRecords + 1];
  
  for (size_t i = 0; i < m_Root->m_Size; ++i) {
    m_Root->m_Next[i] = new CNode();
    m_Root->m_Next[i]->m_Parent = m_Root;

    inStream.read((char*) &m_Root->m_Next[i]->m_Size, sizeof(size_t));
    if (inStream.fail() || inStream.bad()) return false;

    if (m_Root->m_Next[i]->m_Size == 0) {
      m_Root->m_Next[i]->m_Record = new CRecord();

      inStream.read((char*) &m_Root->m_Next[i]->m_Record->m_Id, sizeof(size_t));
      if (inStream.fail() || inStream.bad()) return false;

      m_Root->m_Next[i]->m_Record->m_Position.m_Coordinates.resize(m_Dimension);
      inStream.read((char*) &m_Root->m_Next[i]->m_Record->m_Position.m_Coordinates[0], sizeof(double) * m_Dimension);
      if (inStream.fail() || inStream.bad()) return false;

      m_Root->m_Next[i]->m_Boundaries = CBoundaries(m_Root->m_Next[i]->m_Record->m_Position.m_Coordinates);
    } 
    else {
      m_Root->m_Next[i]->m_Boundaries.m_BottomLeft.m_Coordinates.resize(m_Dimension);
      m_Root->m_Next[i]->m_Boundaries.m_TopRight.m_Coordinates.resize(m_Dimension);
  
      inStream.read((char*) &m_Root->m_Next[i]->m_Boundaries.m_BottomLeft.m_Coordinates[0], sizeof(double) * m_Dimension);
      if (inStream.fail() || inStream.bad()) return false;
  
      inStream.read((char*) &m_Root->m_Next[i]->m_Boundaries.m_TopRight.m_Coordinates[0], sizeof(double) * m_Dimension);
      if (inStream.fail() || inStream.bad()) return false;

      m_Root->m_Next[i]->m_Record = nullptr;
      m_Root->m_Next[i]->m_Next = new CNode*[m_MaxRecords + 1];
      
      q.push(m_Root->m_Next[i]);
    }
  }

  while (!q.empty()) {
    CNode* tmp = q.front(); q.pop();    
    for (size_t i = 0; i < tmp->m_Size; ++i) {
      tmp->m_Next[i] = new CNode();
      tmp->m_Next[i]->m_Parent = m_Root;
  
      inStream.read((char*) &tmp->m_Next[i]->m_Size, sizeof(size_t));
      if (inStream.fail() || inStream.bad()) return false;
  
      if (tmp->m_Next[i]->m_Size == 0) {
        tmp->m_Next[i]->m_Record = new CRecord();
  
        inStream.read((char*) &tmp->m_Next[i]->m_Record->m_Id, sizeof(size_t));
        if (inStream.fail() || inStream.bad()) return false;
  
        tmp->m_Next[i]->m_Record->m_Position.m_Coordinates.resize(m_Dimension);
        inStream.read((char*) &tmp->m_Next[i]->m_Record->m_Position.m_Coordinates[0], sizeof(double) * m_Dimension);
        if (inStream.fail() || inStream.bad()) return false;

        tmp->m_Next[i]->m_Boundaries = CBoundaries(tmp->m_Next[i]->m_Record->m_Position.m_Coordinates);
      } 
      else {
        tmp->m_Next[i]->m_Boundaries.m_BottomLeft.m_Coordinates.resize(m_Dimension);
        tmp->m_Next[i]->m_Boundaries.m_TopRight.m_Coordinates.resize(m_Dimension);
    
        inStream.read((char*) &tmp->m_Next[i]->m_Boundaries.m_BottomLeft.m_Coordinates[0], sizeof(double) * m_Dimension);
        if (inStream.fail() || inStream.bad()) return false;
    
        inStream.read((char*) &tmp->m_Next[i]->m_Boundaries.m_TopRight.m_Coordinates[0], sizeof(double) * m_Dimension);
        if (inStream.fail() || inStream.bad()) return false;
  
        tmp->m_Next[i]->m_Record = nullptr;
        tmp->m_Next[i]->m_Parent = tmp;
        tmp->m_Next[i]->m_Next = new CNode*[m_MaxRecords + 1];
        
        q.push(tmp->m_Next[i]);
      }
    }
  }

  return true;
}
// ============================================================================================================== 
void CRTree::render (CGraphics* graphics, const SDL_Color& colorNode, const SDL_Color& colorBox, int topBorder) {
  auto size = graphics->getWindowSize();
  int W = size.first, H = size.second;
  std::queue<CNode*> q;
  q.push(m_Root);

  while (!q.empty()) {
    CNode* tmp = q.front();
    q.pop();

    if (tmp->m_Record) {
      graphics->renderCircle(tmp->m_Record->m_Position.m_Coordinates[0] + W / 2, H - (tmp->m_Record->m_Position.m_Coordinates[1] + (H - topBorder) / 2), 5, colorNode);
    } else {
      const CBoundaries& b = tmp->m_Boundaries;
      graphics->renderLine(W / 2 + static_cast<int>(b.m_BottomLeft.m_Coordinates[0]), topBorder + (H - topBorder) / 2 - static_cast<int>(b.m_BottomLeft.m_Coordinates[1]), W / 2 + static_cast<int>(b.m_TopRight.m_Coordinates[0]),   topBorder + (H - topBorder) / 2 - static_cast<int>(b.m_BottomLeft.m_Coordinates[1]), colorBox);
      graphics->renderLine(W / 2 + static_cast<int>(b.m_BottomLeft.m_Coordinates[0]), topBorder + (H - topBorder) / 2 - static_cast<int>(b.m_BottomLeft.m_Coordinates[1]), W / 2 + static_cast<int>(b.m_BottomLeft.m_Coordinates[0]), topBorder + (H - topBorder) / 2 - static_cast<int>(b.m_TopRight.m_Coordinates[1]),   colorBox);
      graphics->renderLine(W / 2 + static_cast<int>(b.m_TopRight.m_Coordinates[0]),   topBorder + (H - topBorder) / 2 - static_cast<int>(b.m_TopRight.m_Coordinates[1]),   W / 2 + static_cast<int>(b.m_TopRight.m_Coordinates[0]),   topBorder + (H - topBorder) / 2 - static_cast<int>(b.m_BottomLeft.m_Coordinates[1]), colorBox);
      graphics->renderLine(W / 2 + static_cast<int>(b.m_TopRight.m_Coordinates[0]),   topBorder + (H - topBorder) / 2 - static_cast<int>(b.m_TopRight.m_Coordinates[1]),   W / 2 + static_cast<int>(b.m_BottomLeft.m_Coordinates[0]), topBorder + (H - topBorder) / 2 - static_cast<int>(b.m_TopRight.m_Coordinates[1]),   colorBox);
      for (size_t i = 0; i < tmp->m_Size; ++i) {
        q.push(tmp->m_Next[i]);
      }
    }
  }
}