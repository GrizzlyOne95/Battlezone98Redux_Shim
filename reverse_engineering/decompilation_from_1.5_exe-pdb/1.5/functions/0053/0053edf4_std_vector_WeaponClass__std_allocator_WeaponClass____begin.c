/*
 * Entry: 0053edf4
 * Name: std::vector<WeaponClass_*,std::allocator<WeaponClass_*>_>::begin
 * Namespace: std::vector<WeaponClass_*,std::allocator<WeaponClass_*>_>
 * Signature: _Vector_iterator<WeaponClass_*,std::allocator<WeaponClass_*>_> begin(vector<WeaponClass_*,std::allocator<WeaponClass_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<WeaponClass_*,std::allocator<WeaponClass_*>_> __thiscall
std::vector<WeaponClass_*,std::allocator<WeaponClass_*>_>::begin
          (vector<WeaponClass_*,std::allocator<WeaponClass_*>_> *this)

{
  undefined4 extraout_EDX;
  _Vector_iterator<WeaponClass_*,std::allocator<WeaponClass_*>_> _Var1;
  _Vector_const_iterator<WeaponClass_*,std::allocator<WeaponClass_*>_> *in_stack_00000004;
  
  _Vector_const_iterator<WeaponClass_*,std::allocator<WeaponClass_*>_>::
  _Vector_const_iterator<WeaponClass_*,std::allocator<WeaponClass_*>_>
            (in_stack_00000004,this->_Myfirst,(_Container_base_aux *)this);
  _Var1._4_4_ = extraout_EDX;
  _Var1._0_4_ = in_stack_00000004;
  return _Var1;
}
