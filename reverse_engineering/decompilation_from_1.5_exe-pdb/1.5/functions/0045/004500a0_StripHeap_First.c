/*
 * Entry: 004500a0
 * Name: StripHeap::First
 * Namespace: StripHeap
 * Signature: Strip * First(StripHeap * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Strip * __thiscall StripHeap::First(StripHeap *this)

{
  Strip *pSVar1;
  
  if (*(int *)&this->field_0x4 == 0) {
    return (Strip *)0x0;
  }
  pSVar1 = *(Strip **)(*(int *)&this->field_0x10 + 0xc);
  Heap_Class<Strip_*,float>::Pop((Heap_Class<Strip_*,float> *)this);
  pSVar1->open = false;
  return pSVar1;
}
