/*
 * Entry: 0044f3e0
 * Name: Heap_Class<Strip_*,float>::~Heap_Class<Strip_*,float>
 * Namespace: Heap_Class<Strip_*,float>
 * Signature: void ~Heap_Class<Strip_*,float>(Heap_Class<Strip_*,float> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
Heap_Class<Strip_*,float>::~Heap_Class<Strip_*,float>(Heap_Class<Strip_*,float> *this)

{
  this->_padding_ = (int)&Heap_Class<struct_Strip*,float>::_vftable_;
  if (this->Allocated == true) {
    operator_delete__(this->Pool);
  }
  return;
}
