/*
 * Entry: 00518421
 * Name: std::_Vector_iterator<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>::operator++
 * Namespace: std::_Vector_iterator<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>
 * Signature: _Vector_iterator<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_> * operator++(_Vector_iterator<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_> * __thiscall
std::_Vector_iterator<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>::operator++
          (_Vector_iterator<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_> *this)

{
  _Vector_const_iterator<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>::operator++
            ((_Vector_const_iterator<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_> *)this);
  return this;
}
