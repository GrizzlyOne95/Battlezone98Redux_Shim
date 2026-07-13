/*
 * Entry: 0052eda5
 * Name: std::vector<ExplosionClass_*,std::allocator<ExplosionClass_*>_>::~vector<ExplosionClass_*,std::allocator<ExplosionClass_*>_>
 * Namespace: std::vector<ExplosionClass_*,std::allocator<ExplosionClass_*>_>
 * Signature: void ~vector<ExplosionClass_*,std::allocator<ExplosionClass_*>_>(vector<ExplosionClass_*,std::allocator<ExplosionClass_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::vector<ExplosionClass_*,std::allocator<ExplosionClass_*>_>::
~vector<ExplosionClass_*,std::allocator<ExplosionClass_*>_>
          (vector<ExplosionClass_*,std::allocator<ExplosionClass_*>_> *this)

{
  _Tidy(this);
  operator_delete((void *)this->_padding_);
  return;
}
