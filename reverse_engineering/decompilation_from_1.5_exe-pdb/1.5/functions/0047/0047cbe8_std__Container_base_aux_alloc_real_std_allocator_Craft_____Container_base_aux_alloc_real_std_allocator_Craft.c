/*
 * Entry: 0047cbe8
 * Name: std::_Container_base_aux_alloc_real<std::allocator<Craft_*>_>::_Container_base_aux_alloc_real<std::allocator<Craft_*>_>
 * Namespace: std::_Container_base_aux_alloc_real<std::allocator<Craft_*>_>
 * Signature: _Container_base_aux_alloc_real<std::allocator<Craft_*>_> * _Container_base_aux_alloc_real<std::allocator<Craft_*>_>(_Container_base_aux_alloc_real<std::allocator<Craft_*>_> * this, allocator<Craft_*> param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Container_base_aux_alloc_real<std::allocator<Craft_*>_> * __thiscall
std::_Container_base_aux_alloc_real<std::allocator<Craft_*>_>::
_Container_base_aux_alloc_real<std::allocator<Craft_*>_>
          (_Container_base_aux_alloc_real<std::allocator<Craft_*>_> *this,allocator<Craft_*> param_1
          )

{
  _Aux_cont *p_Var1;
  
  p_Var1 = _Allocate<std::_Aux_cont>(1,(_Aux_cont *)0x0);
  if (p_Var1 == (_Aux_cont *)0x0) {
    p_Var1 = (_Aux_cont *)0x0;
  }
  else {
    p_Var1->_Mycontainer = (_Container_base_aux *)this;
  }
  this->_padding_ = (int)p_Var1;
  return this;
}
