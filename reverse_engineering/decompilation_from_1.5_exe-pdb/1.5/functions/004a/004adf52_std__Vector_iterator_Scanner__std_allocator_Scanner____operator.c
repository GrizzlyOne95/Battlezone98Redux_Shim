/*
 * Entry: 004adf52
 * Name: std::_Vector_iterator<Scanner_*,std::allocator<Scanner_*>_>::operator+=
 * Namespace: std::_Vector_iterator<Scanner_*,std::allocator<Scanner_*>_>
 * Signature: _Vector_iterator<Scanner_*,std::allocator<Scanner_*>_> * operator+=(_Vector_iterator<Scanner_*,std::allocator<Scanner_*>_> * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<Scanner_*,std::allocator<Scanner_*>_> * __thiscall
std::_Vector_iterator<Scanner_*,std::allocator<Scanner_*>_>::operator+=
          (_Vector_iterator<Scanner_*,std::allocator<Scanner_*>_> *this,int param_1)

{
  _Vector_const_iterator<Scanner_*,std::allocator<Scanner_*>_>::operator+=
            ((_Vector_const_iterator<Scanner_*,std::allocator<Scanner_*>_> *)this,param_1);
  return this;
}
