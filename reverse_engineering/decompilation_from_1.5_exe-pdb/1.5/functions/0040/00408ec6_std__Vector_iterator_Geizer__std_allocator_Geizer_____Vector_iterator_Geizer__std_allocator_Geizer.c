/*
 * Entry: 00408ec6
 * Name: std::_Vector_iterator<Geizer_*,std::allocator<Geizer_*>_>::_Vector_iterator<Geizer_*,std::allocator<Geizer_*>_>
 * Namespace: std::_Vector_iterator<Geizer_*,std::allocator<Geizer_*>_>
 * Signature: _Vector_iterator<Geizer_*,std::allocator<Geizer_*>_> * _Vector_iterator<Geizer_*,std::allocator<Geizer_*>_>(_Vector_iterator<Geizer_*,std::allocator<Geizer_*>_> * this, Geizer * * param_1, _Container_base_aux * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<Geizer_*,std::allocator<Geizer_*>_> * __thiscall
std::_Vector_iterator<Geizer_*,std::allocator<Geizer_*>_>::
_Vector_iterator<Geizer_*,std::allocator<Geizer_*>_>
          (_Vector_iterator<Geizer_*,std::allocator<Geizer_*>_> *this,Geizer **param_1,
          _Container_base_aux *param_2)

{
  _Vector_const_iterator<Geizer_*,std::allocator<Geizer_*>_>::
  _Vector_const_iterator<Geizer_*,std::allocator<Geizer_*>_>
            ((_Vector_const_iterator<Geizer_*,std::allocator<Geizer_*>_> *)this,param_1,param_2);
  return this;
}
