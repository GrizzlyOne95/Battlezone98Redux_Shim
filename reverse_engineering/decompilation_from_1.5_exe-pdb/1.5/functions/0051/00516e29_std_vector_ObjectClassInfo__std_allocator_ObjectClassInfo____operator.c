/*
 * Entry: 00516e29
 * Name: std::vector<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>::operator[]
 * Namespace: std::vector<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>
 * Signature: ObjectClassInfo * * operator[](vector<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_> * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ObjectClassInfo ** __thiscall
std::vector<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>::operator[]
          (vector<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_> *this,uint param_1)

{
  if ((uint)((int)this->_Mylast - (int)this->_Myfirst >> 2) <= param_1) {
    _invalid_parameter_noinfo();
  }
  return this->_Myfirst + param_1;
}
