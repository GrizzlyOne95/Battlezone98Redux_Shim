/*
 * Entry: 00497699
 * Name: std::_Vector_iterator<Scanner_*,std::allocator<Scanner_*>_>::operator++
 * Namespace: std::_Vector_iterator<Scanner_*,std::allocator<Scanner_*>_>
 * Signature: _Vector_iterator<Scanner_*,std::allocator<Scanner_*>_> * operator++(_Vector_iterator<Scanner_*,std::allocator<Scanner_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<Scanner_*,std::allocator<Scanner_*>_> * __thiscall
std::_Vector_iterator<Scanner_*,std::allocator<Scanner_*>_>::operator++
          (_Vector_iterator<Scanner_*,std::allocator<Scanner_*>_> *this)

{
  _Vector_const_iterator<Scanner_*,std::allocator<Scanner_*>_>::operator++
            ((_Vector_const_iterator<Scanner_*,std::allocator<Scanner_*>_> *)this);
  return this;
}
