/*
 * Entry: 00450d40
 * Name: StripHeap::`scalar_deleting_destructor'
 * Namespace: StripHeap
 * Signature: void * `scalar_deleting_destructor'(StripHeap * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall StripHeap::_scalar_deleting_destructor_(StripHeap *this,uint param_1)

{
  *(undefined ***)this = &Heap_Class<struct_Strip*,float>::_vftable_;
  if (this->field_0xc == '\x01') {
    operator_delete__(*(void **)&this->field_0x10);
  }
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
