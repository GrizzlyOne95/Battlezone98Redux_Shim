/*
 * Entry: 00450cf0
 * Name: StripHeap::StripHeap
 * Namespace: StripHeap
 * Signature: StripHeap * StripHeap(StripHeap * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

StripHeap * __thiscall StripHeap::StripHeap(StripHeap *this)

{
  undefined4 *puVar1;
  
  *(undefined ***)this = &Heap_Class<struct_Strip*,float>::_vftable_;
  this->field_0xc = 1;
  puVar1 = operator_new__(0x10008);
  *(undefined4 **)&this->field_0x10 = puVar1;
  *(undefined4 *)&this->field_0x8 = 0x2000;
  *puVar1 = 0;
  *(undefined4 *)&this->field_0x4 = 0;
  *(undefined ***)this = &_vftable_;
  return this;
}
