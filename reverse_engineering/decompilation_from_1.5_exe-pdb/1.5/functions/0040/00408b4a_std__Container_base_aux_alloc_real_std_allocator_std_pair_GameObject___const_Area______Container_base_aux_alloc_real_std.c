/*
 * Entry: 00408b4a
 * Name: std::_Container_base_aux_alloc_real<std::allocator<std::pair<GameObject_*_const,Area>_>_>::_Container_base_aux_alloc_real<std::allocator<std::pair<GameObject_*_const,Area>_>_>
 * Namespace: std::_Container_base_aux_alloc_real<std::allocator<std::pair<GameObject_*_const,Area>_>_>
 * Signature: _Container_base_aux_alloc_real<std::allocator<std::pair<GameObject_*_const,Area>_>_> * _Container_base_aux_alloc_real<std::allocator<std::pair<GameObject_*_const,Area>_>_>(_Container_base_aux_alloc_real<std::allocator<std::pair<GameObject_*_const,Area>_>_> * this, allocator<std::pair<GameObject_*_const,Area>_> param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Container_base_aux_alloc_real<std::allocator<std::pair<GameObject_*_const,Area>_>_> * __thiscall
std::_Container_base_aux_alloc_real<std::allocator<std::pair<GameObject_*_const,Area>_>_>::
_Container_base_aux_alloc_real<std::allocator<std::pair<GameObject_*_const,Area>_>_>
          (_Container_base_aux_alloc_real<std::allocator<std::pair<GameObject_*_const,Area>_>_>
           *this,allocator<std::pair<GameObject_*_const,Area>_> param_1)

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
