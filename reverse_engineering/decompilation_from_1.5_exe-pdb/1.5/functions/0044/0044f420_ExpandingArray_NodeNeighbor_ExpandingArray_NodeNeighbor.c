/*
 * Entry: 0044f420
 * Name: ExpandingArray<NodeNeighbor>::ExpandingArray<NodeNeighbor>
 * Namespace: ExpandingArray<NodeNeighbor>
 * Signature: ExpandingArray<NodeNeighbor> * ExpandingArray<NodeNeighbor>(ExpandingArray<NodeNeighbor> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ExpandingArray<NodeNeighbor> * __thiscall
ExpandingArray<NodeNeighbor>::ExpandingArray<NodeNeighbor>(ExpandingArray<NodeNeighbor> *this)

{
  this->array = (NodeNeighbor *)0x0;
  this->size = 0;
  return this;
}
