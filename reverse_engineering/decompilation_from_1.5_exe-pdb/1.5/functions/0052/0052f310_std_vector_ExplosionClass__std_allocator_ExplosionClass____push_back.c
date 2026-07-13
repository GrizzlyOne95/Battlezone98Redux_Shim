/*
 * Entry: 0052f310
 * Name: std::vector<ExplosionClass_*,std::allocator<ExplosionClass_*>_>::push_back
 * Namespace: std::vector<ExplosionClass_*,std::allocator<ExplosionClass_*>_>
 * Signature: void push_back(vector<ExplosionClass_*,std::allocator<ExplosionClass_*>_> * this, ExplosionClass * * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::vector<ExplosionClass_*,std::allocator<ExplosionClass_*>_>::push_back
          (vector<ExplosionClass_*,std::allocator<ExplosionClass_*>_> *this,ExplosionClass **param_1
          )

{
  _Vector_const_iterator<ExplosionClass_*,std::allocator<ExplosionClass_*>_> _Var1;
  uint uVar2;
  ExplosionClass **ppEVar3;
  _Vector_const_iterator<ExplosionClass_*,std::allocator<ExplosionClass_*>_> local_c;
  
  ppEVar3 = this->_Mylast;
  local_c._padding_ = (int)this;
  local_c._Myptr = (ExplosionClass **)this;
  uVar2 = capacity(this);
  if ((uint)((int)ppEVar3 - (int)this->_Myfirst >> 2) < uVar2) {
    ppEVar3 = _Ufill(this,ppEVar3,1,param_1);
    this->_Mylast = ppEVar3;
  }
  else {
    _Vector_const_iterator<ExplosionClass_*,std::allocator<ExplosionClass_*>_>::
    _Vector_const_iterator<ExplosionClass_*,std::allocator<ExplosionClass_*>_>
              (&local_c,ppEVar3,(_Container_base_aux *)this);
    _Var1._Myptr = (ExplosionClass **)local_c._padding_;
    _Var1._padding_ = (int)&local_c;
    insert(this,_Var1,local_c._Myptr);
  }
  return;
}
