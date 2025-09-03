#ifndef INDEX_H
#define INDEX_H

#include <SDL2/SDL.h>
#include "object.h"
#include "graphics.h"

class CIndex {
protected:
  size_t m_Dimension;
public:
  // ==============================================================================================================
  CIndex(int dimension) : m_Dimension(dimension) {}
  // ==============================================================================================================
  virtual ~CIndex() = default;
  // ==============================================================================================================
  inline size_t dimension (void) {return m_Dimension;}
  // ==============================================================================================================
  virtual size_t size (void) = 0;
  // ==============================================================================================================
  virtual size_t insert (CRecord* record) = 0;
  // ==============================================================================================================  
  virtual std::vector<CRecord*> find_in_range (const CBoundaries& boundaries, bool sorted = true) = 0;
  // ==============================================================================================================  
  virtual std::vector<size_t> find_in_range_id_s (const CBoundaries& boundaries, bool sorted = true) = 0;
  // ==============================================================================================================
  virtual std::vector<CRecord*> knn (const CPoint& p, size_t k, bool sorted = true) = 0;
  // ==============================================================================================================  
  virtual std::vector<size_t> knn_id_s (const CPoint& p, size_t k, bool sorted = true) = 0;  
  // ==============================================================================================================  
  virtual bool save (const std::string& filename) = 0;
  // ==============================================================================================================  
  virtual bool load (const std::string& filename) = 0;
  // ==============================================================================================================  
  virtual void render (CGraphics* graphics, const SDL_Color& colorNode, const SDL_Color& colorBox, int topBorder) = 0;
  // ==============================================================================================================  
};

#endif // INDEX_H