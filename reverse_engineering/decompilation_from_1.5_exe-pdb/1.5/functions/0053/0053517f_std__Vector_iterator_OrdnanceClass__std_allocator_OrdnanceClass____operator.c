/*
 * Entry: 0053517f
 * Name: std::_Vector_iterator<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_>::operator++
 * Namespace: std::_Vector_iterator<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_>
 * Signature: _Vector_iterator<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_> * operator++(_Vector_iterator<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_> * __thiscall
std::_Vector_iterator<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_>::operator++
          (_Vector_iterator<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_> *this)

{
  _Vector_const_iterator<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_>::operator++
            ((_Vector_const_iterator<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_> *)this);
  return this;
}
