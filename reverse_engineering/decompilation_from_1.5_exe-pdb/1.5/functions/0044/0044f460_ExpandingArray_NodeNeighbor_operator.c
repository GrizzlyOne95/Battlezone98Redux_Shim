/*
 * Entry: 0044f460
 * Name: ExpandingArray<NodeNeighbor>::operator[]
 * Namespace: ExpandingArray<NodeNeighbor>
 * Signature: NodeNeighbor * operator[](ExpandingArray<NodeNeighbor> * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

NodeNeighbor * __thiscall
ExpandingArray<NodeNeighbor>::operator[](ExpandingArray<NodeNeighbor> *this,int param_1)

{
  int iVar1;
  longlong lVar2;
  NodeNeighbor *pNVar3;
  int iVar4;
  
  iVar1 = this->size;
  if (iVar1 <= param_1) {
    if (iVar1 == 0) {
      pNVar3 = operator_new__(0x40);
      this->array = pNVar3;
      this->size = 0x10;
      return pNVar3 + param_1;
    }
    lVar2 = (ulonglong)(uint)(iVar1 * 2) * 4;
    pNVar3 = operator_new__(-(uint)((int)((ulonglong)lVar2 >> 0x20) != 0) | (uint)lVar2);
    iVar4 = 0;
    if (0 < this->size) {
      do {
        pNVar3[iVar4].node = this->array[iVar4].node;
        iVar4 = iVar4 + 1;
      } while (iVar4 < this->size);
    }
    operator_delete(this->array);
    this->array = pNVar3;
    this->size = iVar1 * 2;
  }
  return this->array + param_1;
}
