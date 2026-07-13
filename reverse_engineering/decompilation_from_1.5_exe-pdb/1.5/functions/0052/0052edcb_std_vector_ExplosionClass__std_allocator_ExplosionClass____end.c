/*
 * Entry: 0052edcb
 * Name: std::vector<ExplosionClass_*,std::allocator<ExplosionClass_*>_>::end
 * Namespace: std::vector<ExplosionClass_*,std::allocator<ExplosionClass_*>_>
 * Signature: _Vector_iterator<ExplosionClass_*,std::allocator<ExplosionClass_*>_> end(vector<ExplosionClass_*,std::allocator<ExplosionClass_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<ExplosionClass_*,std::allocator<ExplosionClass_*>_> __thiscall
std::vector<ExplosionClass_*,std::allocator<ExplosionClass_*>_>::end
          (vector<ExplosionClass_*,std::allocator<ExplosionClass_*>_> *this)

{
  undefined4 extraout_EDX;
  _Vector_iterator<ExplosionClass_*,std::allocator<ExplosionClass_*>_> _Var1;
  _Vector_const_iterator<ExplosionClass_*,std::allocator<ExplosionClass_*>_> *in_stack_00000004;
  
  _Vector_const_iterator<ExplosionClass_*,std::allocator<ExplosionClass_*>_>::
  _Vector_const_iterator<ExplosionClass_*,std::allocator<ExplosionClass_*>_>
            (in_stack_00000004,this->_Mylast,(_Container_base_aux *)this);
  _Var1._4_4_ = extraout_EDX;
  _Var1._0_4_ = in_stack_00000004;
  return _Var1;
}
