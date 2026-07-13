/*
 * Entry: 00518a98
 * Name: std::_Vector_iterator<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>::operator-=
 * Namespace: std::_Vector_iterator<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>
 * Signature: _Vector_iterator<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_> * operator-=(_Vector_iterator<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_> * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_> * __thiscall
std::_Vector_iterator<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>::operator-=
          (_Vector_iterator<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_> *this,int param_1)

{
  _Vector_const_iterator<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>::operator+=
            ((_Vector_const_iterator<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_> *)this,
             -param_1);
  return this;
}
