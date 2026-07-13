/*
 * Entry: 0051933c
 * Name: std::vector<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>::_Umove<ObjectClassInfo_*_*>
 * Namespace: std::vector<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>
 * Signature: ObjectClassInfo * * _Umove<ObjectClassInfo_*_*>(vector<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_> * this, ObjectClassInfo * * param_1, ObjectClassInfo * * param_2, ObjectClassInfo * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ObjectClassInfo ** __thiscall
std::vector<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>::_Umove<ObjectClassInfo_*_*>
          (vector<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_> *this,
          ObjectClassInfo **param_1,ObjectClassInfo **param_2,ObjectClassInfo **param_3)

{
  ObjectClassInfo **ppOVar1;
  
  ppOVar1 = stdext::
            unchecked_uninitialized_copy<ObjectClassInfo_*_*,ObjectClassInfo_*_*,std::allocator<ObjectClassInfo_*>_>
                      (param_1,param_2,param_3,(allocator<ObjectClassInfo_*> *)&this->_padding_);
  return ppOVar1;
}
