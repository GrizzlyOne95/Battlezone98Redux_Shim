/*
 * Entry: 00450080
 * Name: StripHeap::~StripHeap
 * Namespace: StripHeap
 * Signature: void ~StripHeap(StripHeap * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall StripHeap::~StripHeap(StripHeap *this)

{
  *(undefined ***)this = &Heap_Class<struct_Strip*,float>::_vftable_;
  if (this->field_0xc == '\x01') {
    operator_delete__(*(void **)&this->field_0x10);
  }
  return;
}
