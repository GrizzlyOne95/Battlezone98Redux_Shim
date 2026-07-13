/*
 * Entry: 00535949
 * Name: std::vector<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_>::push_back
 * Namespace: std::vector<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_>
 * Signature: void push_back(vector<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_> * this, OrdnanceClass * * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::vector<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_>::push_back
          (vector<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_> *this,OrdnanceClass **param_1)

{
  _Vector_const_iterator<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_> _Var1;
  uint uVar2;
  OrdnanceClass **ppOVar3;
  _Vector_const_iterator<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_> local_c;
  
  ppOVar3 = this->_Mylast;
  local_c._padding_ = (int)this;
  local_c._Myptr = (OrdnanceClass **)this;
  uVar2 = capacity(this);
  if ((uint)((int)ppOVar3 - (int)this->_Myfirst >> 2) < uVar2) {
    ppOVar3 = _Ufill(this,ppOVar3,1,param_1);
    this->_Mylast = ppOVar3;
  }
  else {
    _Vector_const_iterator<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_>::
    _Vector_const_iterator<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_>
              (&local_c,ppOVar3,(_Container_base_aux *)this);
    _Var1._Myptr = (OrdnanceClass **)local_c._padding_;
    _Var1._padding_ = (int)&local_c;
    insert(this,_Var1,local_c._Myptr);
  }
  return;
}
