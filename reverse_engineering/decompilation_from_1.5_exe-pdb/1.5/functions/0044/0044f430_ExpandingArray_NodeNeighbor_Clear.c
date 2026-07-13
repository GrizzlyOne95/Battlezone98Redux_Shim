/*
 * Entry: 0044f430
 * Name: ExpandingArray<NodeNeighbor>::Clear
 * Namespace: ExpandingArray<NodeNeighbor>
 * Signature: void Clear(ExpandingArray<NodeNeighbor> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ExpandingArray<NodeNeighbor>::Clear(ExpandingArray<NodeNeighbor> *this)

{
  if (this->array != (NodeNeighbor *)0x0) {
    operator_delete__(this->array);
  }
  this->size = 0;
  this->array = (NodeNeighbor *)0x0;
  return;
}
