/*
 * Entry: 004507f0
 * Name: ExpandingArray<NodeNeighbor>::~ExpandingArray<NodeNeighbor>
 * Namespace: ExpandingArray<NodeNeighbor>
 * Signature: void ~ExpandingArray<NodeNeighbor>(ExpandingArray<NodeNeighbor> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
ExpandingArray<NodeNeighbor>::~ExpandingArray<NodeNeighbor>(ExpandingArray<NodeNeighbor> *this)

{
  if (this->array != (NodeNeighbor *)0x0) {
    operator_delete__(this->array);
  }
  this->size = 0;
  this->array = (NodeNeighbor *)0x0;
  return;
}
