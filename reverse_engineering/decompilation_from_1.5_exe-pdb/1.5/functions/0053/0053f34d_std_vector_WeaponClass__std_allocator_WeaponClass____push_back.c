/*
 * Entry: 0053f34d
 * Name: std::vector<WeaponClass_*,std::allocator<WeaponClass_*>_>::push_back
 * Namespace: std::vector<WeaponClass_*,std::allocator<WeaponClass_*>_>
 * Signature: void push_back(vector<WeaponClass_*,std::allocator<WeaponClass_*>_> * this, WeaponClass * * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::vector<WeaponClass_*,std::allocator<WeaponClass_*>_>::push_back
          (vector<WeaponClass_*,std::allocator<WeaponClass_*>_> *this,WeaponClass **param_1)

{
  _Vector_const_iterator<WeaponClass_*,std::allocator<WeaponClass_*>_> _Var1;
  uint uVar2;
  WeaponClass **ppWVar3;
  _Vector_const_iterator<WeaponClass_*,std::allocator<WeaponClass_*>_> local_c;
  
  ppWVar3 = this->_Mylast;
  local_c._padding_ = (int)this;
  local_c._Myptr = (WeaponClass **)this;
  uVar2 = capacity(this);
  if ((uint)((int)ppWVar3 - (int)this->_Myfirst >> 2) < uVar2) {
    ppWVar3 = _Ufill(this,ppWVar3,1,param_1);
    this->_Mylast = ppWVar3;
  }
  else {
    _Vector_const_iterator<WeaponClass_*,std::allocator<WeaponClass_*>_>::
    _Vector_const_iterator<WeaponClass_*,std::allocator<WeaponClass_*>_>
              (&local_c,ppWVar3,(_Container_base_aux *)this);
    _Var1._Myptr = (WeaponClass **)local_c._padding_;
    _Var1._padding_ = (int)&local_c;
    insert(this,_Var1,local_c._Myptr);
  }
  return;
}
