/*
 * Entry: 00450f80
 * Name: std::_Container_base_aux_alloc_real<std::allocator<PathPoint>_>::_Container_base_aux_alloc_real<std::allocator<PathPoint>_>
 * Namespace: std::_Container_base_aux_alloc_real<std::allocator<PathPoint>_>
 * Signature: _Container_base_aux_alloc_real<std::allocator<PathPoint>_> * _Container_base_aux_alloc_real<std::allocator<PathPoint>_>(_Container_base_aux_alloc_real<std::allocator<PathPoint>_> * this, allocator<PathPoint> param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Container_base_aux_alloc_real<std::allocator<PathPoint>_> * __thiscall
std::_Container_base_aux_alloc_real<std::allocator<PathPoint>_>::
_Container_base_aux_alloc_real<std::allocator<PathPoint>_>
          (_Container_base_aux_alloc_real<std::allocator<PathPoint>_> *this,
          allocator<PathPoint> param_1)

{
  undefined4 *puVar1;
  
  puVar1 = operator_new(4);
  if (puVar1 != (undefined4 *)0x0) {
    *puVar1 = this;
    this->_padding_ = (int)puVar1;
    return this;
  }
  this->_padding_ = 0;
  return this;
}
