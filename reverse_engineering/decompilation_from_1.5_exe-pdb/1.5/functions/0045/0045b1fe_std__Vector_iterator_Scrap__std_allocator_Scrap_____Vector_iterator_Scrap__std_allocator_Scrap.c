/*
 * Entry: 0045b1fe
 * Name: std::_Vector_iterator<Scrap_*,std::allocator<Scrap_*>_>::_Vector_iterator<Scrap_*,std::allocator<Scrap_*>_>
 * Namespace: std::_Vector_iterator<Scrap_*,std::allocator<Scrap_*>_>
 * Signature: _Vector_iterator<Scrap_*,std::allocator<Scrap_*>_> * _Vector_iterator<Scrap_*,std::allocator<Scrap_*>_>(_Vector_iterator<Scrap_*,std::allocator<Scrap_*>_> * this, Scrap * * param_1, _Container_base_aux * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<Scrap_*,std::allocator<Scrap_*>_> * __thiscall
std::_Vector_iterator<Scrap_*,std::allocator<Scrap_*>_>::
_Vector_iterator<Scrap_*,std::allocator<Scrap_*>_>
          (_Vector_iterator<Scrap_*,std::allocator<Scrap_*>_> *this,Scrap **param_1,
          _Container_base_aux *param_2)

{
  _Vector_const_iterator<Scrap_*,std::allocator<Scrap_*>_>::
  _Vector_const_iterator<Scrap_*,std::allocator<Scrap_*>_>
            ((_Vector_const_iterator<Scrap_*,std::allocator<Scrap_*>_> *)this,param_1,param_2);
  return this;
}
