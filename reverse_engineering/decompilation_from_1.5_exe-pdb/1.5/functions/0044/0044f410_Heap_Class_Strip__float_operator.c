/*
 * Entry: 0044f410
 * Name: Heap_Class<Strip_*,float>::operator[]
 * Namespace: Heap_Class<Strip_*,float>
 * Signature: Strip * operator[](Heap_Class<Strip_*,float> * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Strip * __thiscall
Heap_Class<Strip_*,float>::operator[](Heap_Class<Strip_*,float> *this,int param_1)

{
  return this->Pool[param_1 + 1].Data;
}
