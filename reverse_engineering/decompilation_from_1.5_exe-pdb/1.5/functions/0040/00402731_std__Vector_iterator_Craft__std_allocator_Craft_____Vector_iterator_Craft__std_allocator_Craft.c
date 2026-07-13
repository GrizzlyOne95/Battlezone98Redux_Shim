/*
 * Entry: 00402731
 * Name: std::_Vector_iterator<Craft_*,std::allocator<Craft_*>_>::_Vector_iterator<Craft_*,std::allocator<Craft_*>_>
 * Namespace: std::_Vector_iterator<Craft_*,std::allocator<Craft_*>_>
 * Signature: _Vector_iterator<Craft_*,std::allocator<Craft_*>_> * _Vector_iterator<Craft_*,std::allocator<Craft_*>_>(_Vector_iterator<Craft_*,std::allocator<Craft_*>_> * this, Craft * * param_1, _Container_base_aux * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<Craft_*,std::allocator<Craft_*>_> * __thiscall
std::_Vector_iterator<Craft_*,std::allocator<Craft_*>_>::
_Vector_iterator<Craft_*,std::allocator<Craft_*>_>
          (_Vector_iterator<Craft_*,std::allocator<Craft_*>_> *this,Craft **param_1,
          _Container_base_aux *param_2)

{
  _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>::
  _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>
            ((_Vector_const_iterator<Craft_*,std::allocator<Craft_*>_> *)this,param_1,param_2);
  return this;
}
