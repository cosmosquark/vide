#ifndef __HV_KDTREE_HPP
#define __HV_KDTREE_HPP

#include <cmath>
#include "config.hpp"
#include "bqueue.hpp"

namespace CosmoTool {

  template<int N, typename CType = ComputePrecision> 
  struct KDDef
  {
    typedef CType CoordType;
    typedef float KDCoordinates[N];
  };
  
  template<int N, typename ValType, typename CType = ComputePrecision>
  struct KDCell
  {
    bool active;
    ValType val;
    typename KDDef<N,CType>::KDCoordinates coord;
  };

  class NotEnoughCells: public Exception
  {
  public:
    NotEnoughCells() : Exception() {}
    ~NotEnoughCells() throw () {}
  };

  class InvalidOnDiskKDTree : public Exception
  {
  public:
    InvalidOnDiskKDTree() : Exception() {}
    ~InvalidOnDiskKDTree() throw () {}
  };

  template<int N, typename ValType, typename CType = ComputePrecision>
  struct KDTreeNode
  {
    KDCell<N,ValType,CType> *value;
    KDTreeNode<N,ValType,CType> *children[2];
    typename KDDef<N,CType>::KDCoordinates minBound, maxBound;
#ifdef __KD_TREE_NUMNODES
    uint32_t numNodes;
#endif
  };

  template<int N, typename ValType, typename CType = ComputePrecision>
  class RecursionInfoCells
  {
  public:

    typename KDDef<N,CType>::KDCoordinates x;
    typename KDDef<N,CType>::CoordType r, r2;
    KDCell<N, ValType,CType> **cells;
    typename KDDef<N,CType>::CoordType *distances;
    uint32_t currentRank;
    uint32_t numCells;
  };
  

  template<int N, typename ValType, typename CType = ComputePrecision>
  class RecursionMultipleInfo
  {
  public:
    const typename KDDef<N,CType>::KDCoordinates& x;
    BoundedQueue< KDCell<N,ValType,CType> *, typename KDDef<N,CType>::CoordType> queue;
    int traversed;

    RecursionMultipleInfo(const typename KDDef<N,CType>::KDCoordinates& rx,
			  KDCell<N,ValType,CType> **cells,
			  uint32_t numCells)
      : x(rx), queue(cells, numCells, INFINITY),traversed(0)
    {      
    }
  };

  template<int N, typename ValType, typename CType = ComputePrecision> 
  struct KD_default_cell_splitter
  {
    void operator()(KDCell<N,ValType,CType> **cells, uint32_t Ncells, uint32_t& split_index, int axis, typename KDDef<N,CType>::KDCoordinates minBound, typename KDDef<N,CType>::KDCoordinates maxBound);
  };

  template<int N, typename ValType, typename CType = ComputePrecision, typename CellSplitter = KD_default_cell_splitter<N,ValType,CType> >
  class KDTree
  {
  public:
    typedef typename KDDef<N,CType>::CoordType CoordType;
    typedef typename KDDef<N>::KDCoordinates coords;
    typedef KDCell<N,ValType,CType> Cell;
    typedef KDTreeNode<N,ValType,CType> Node;
    
    CellSplitter splitter;

    KDTree(Cell *cells, uint32_t Ncells);
    ~KDTree();

    uint32_t getIntersection(const coords& x, CoordType r, 
			     Cell **cells,
			     uint32_t numCells)
      throw (NotEnoughCells);
    uint32_t getIntersection(const coords& x, CoordType r, 
			     Cell **cells,
			     CoordType *distances,
			     uint32_t numCells)
      throw (NotEnoughCells);
    uint32_t countCells(const coords& x, CoordType r);

    Cell *getNearestNeighbour(const coords& x);

    void getNearestNeighbours(const coords& x, uint32_t NumCells,
			      Cell **cells);
    void getNearestNeighbours(const coords& x, uint32_t NumCells,
			      Cell **cells,
			      CoordType *distances);

    Node *getRoot() { return root; }

    void optimize();

    Node *getAllNodes() { return nodes; }
    uint32_t getNumNodes() const { return lastNode; }

    uint32_t countActives() const;

#ifdef __KD_TREE_NUMNODES
    uint32_t getNumberInNode(const Node *n) const { return n->numNodes; }
#else
    uint32_t getNumberInNode(const Node *n) const {
      if (n == 0) 
        return 0;
      return 1+getNumberInNode(n->children[0])+getNumberInNode(n->children[1]);
    }
#endif

#ifdef __KD_TREE_SAVE_ON_DISK
    KDTree(std::istream& i, Cell *cells, uint32_t Ncells)
      throw (InvalidOnDiskKDTree);

    void saveTree(std::ostream& o) const;
#endif
  protected:
    Node *nodes;
    uint32_t numNodes;
    uint32_t lastNode;

    Node *root;
    Cell **sortingHelper;
    Cell *base_cell;

    Node *buildTree(Cell **cell0,
		    uint32_t NumCells,
		    uint32_t depth,
		    coords minBound,
		    coords maxBound);
    
    template<bool justCount>
    void recursiveIntersectionCells(RecursionInfoCells<N,ValType, CType>& info,
				    Node *node,
				    int level)
      throw (NotEnoughCells);

    CoordType computeDistance(const Cell *cell, const coords& x) const;
    void recursiveNearest(Node *node,
			  int level,
			  const coords& x,
			  CoordType& R2,
			  Cell*& cell);
    void recursiveMultipleNearest(RecursionMultipleInfo<N,ValType,CType>& info, Node *node,
				  int level);    

  };

  template<int N, typename T, typename CType>
  uint32_t gatherActiveCells(KDCell<N,T,CType> **cells, uint32_t numCells);

};

#include "mykdtree.tcc"

#endif