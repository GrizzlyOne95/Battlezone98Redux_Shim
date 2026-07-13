/*
 * Entry: 00497830
 * Name: std::_Vector_iterator<Scanner_*,std::allocator<Scanner_*>_>::_Vector_iterator<Scanner_*,std::allocator<Scanner_*>_>
 * Namespace: std::_Vector_iterator<Scanner_*,std::allocator<Scanner_*>_>
 * Signature: _Vector_iterator<Scanner_*,std::allocator<Scanner_*>_> * _Vector_iterator<Scanner_*,std::allocator<Scanner_*>_>(_Vector_iterator<Scanner_*,std::allocator<Scanner_*>_> * this, Scanner * * param_1, _Container_base_aux * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<Scanner_*,std::allocator<Scanner_*>_> * __thiscall
std::_Vector_iterator<Scanner_*,std::allocator<Scanner_*>_>::
_Vector_iterator<Scanner_*,std::allocator<Scanner_*>_>
          (_Vector_iterator<Scanner_*,std::allocator<Scanner_*>_> *this,Scanner **param_1,
          _Container_base_aux *param_2)

{
  _Vector_const_iterator<Scanner_*,std::allocator<Scanner_*>_>::
  _Vector_const_iterator<Scanner_*,std::allocator<Scanner_*>_>
            ((_Vector_const_iterator<Scanner_*,std::allocator<Scanner_*>_> *)this,param_1,param_2);
  return this;
}
