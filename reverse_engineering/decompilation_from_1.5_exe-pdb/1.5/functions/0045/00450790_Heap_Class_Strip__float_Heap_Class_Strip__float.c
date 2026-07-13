/*
 * Entry: 00450790
 * Name: Heap_Class<Strip_*,float>::Heap_Class<Strip_*,float>
 * Namespace: Heap_Class<Strip_*,float>
 * Signature: Heap_Class<Strip_*,float> * Heap_Class<Strip_*,float>(Heap_Class<Strip_*,float> * this, int param_1, float param_2, void * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Heap_Class<Strip_*,float> * __thiscall
Heap_Class<Strip_*,float>::Heap_Class<Strip_*,float>
          (Heap_Class<Strip_*,float> *this,int param_1,float param_2,void *param_3)

{
  longlong lVar1;
  
  this->_padding_ = (int)&Heap_Class<struct_Strip*,float>::_vftable_;
  if (param_3 == (void *)0x0) {
    lVar1 = (ulonglong)(param_1 + 1) * 8;
    this->Allocated = true;
    param_3 = operator_new__(-(uint)((int)((ulonglong)lVar1 >> 0x20) != 0) | (uint)lVar1);
  }
  else {
    this->Allocated = false;
  }
  this->Pool = param_3;
  this->Max_Count = param_1;
  ((RECORD *)param_3)->Key = param_2;
  this->Count = 0;
  return this;
}
