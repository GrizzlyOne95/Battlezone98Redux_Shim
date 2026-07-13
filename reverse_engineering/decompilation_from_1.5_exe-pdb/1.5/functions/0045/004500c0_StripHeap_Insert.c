/*
 * Entry: 004500c0
 * Name: StripHeap::Insert
 * Namespace: StripHeap
 * Signature: void Insert(StripHeap * this, Strip * param_1, float param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall StripHeap::Insert(StripHeap *this,Strip *param_1,float param_2)

{
  Heap_Class<Strip_*,float>::Push((Heap_Class<Strip_*,float> *)this,param_1,-param_2);
  param_1->open = true;
  return;
}
