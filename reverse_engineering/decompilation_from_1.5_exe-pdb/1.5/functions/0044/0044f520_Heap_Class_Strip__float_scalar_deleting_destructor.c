/*
 * Entry: 0044f520
 * Name: Heap_Class<Strip_*,float>::`scalar_deleting_destructor'
 * Namespace: Heap_Class<Strip_*,float>
 * Signature: void * `scalar_deleting_destructor'(Heap_Class<Strip_*,float> * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall
Heap_Class<Strip_*,float>::_scalar_deleting_destructor_
          (Heap_Class<Strip_*,float> *this,uint param_1)

{
  this->_padding_ = (int)&Heap_Class<struct_Strip*,float>::_vftable_;
  if (this->Allocated == true) {
    operator_delete__(this->Pool);
  }
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
