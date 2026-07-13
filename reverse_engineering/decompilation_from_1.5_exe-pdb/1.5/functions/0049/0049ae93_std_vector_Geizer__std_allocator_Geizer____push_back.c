/*
 * Entry: 0049ae93
 * Name: std::vector<Geizer_*,std::allocator<Geizer_*>_>::push_back
 * Namespace: std::vector<Geizer_*,std::allocator<Geizer_*>_>
 * Signature: void push_back(vector<Geizer_*,std::allocator<Geizer_*>_> * this, Geizer * * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::vector<Geizer_*,std::allocator<Geizer_*>_>::push_back
          (vector<Geizer_*,std::allocator<Geizer_*>_> *this,Geizer **param_1)

{
  _Vector_const_iterator<Geizer_*,std::allocator<Geizer_*>_> _Var1;
  uint uVar2;
  Geizer **ppGVar3;
  _Vector_const_iterator<Geizer_*,std::allocator<Geizer_*>_> local_c;
  
  ppGVar3 = this->_Mylast;
  local_c._padding_ = (int)this;
  local_c._Myptr = (Geizer **)this;
  uVar2 = capacity(this);
  if ((uint)((int)ppGVar3 - (int)this->_Myfirst >> 2) < uVar2) {
    ppGVar3 = _Ufill(this,ppGVar3,1,param_1);
    this->_Mylast = ppGVar3;
  }
  else {
    _Vector_const_iterator<Geizer_*,std::allocator<Geizer_*>_>::
    _Vector_const_iterator<Geizer_*,std::allocator<Geizer_*>_>
              (&local_c,ppGVar3,(_Container_base_aux *)this);
    _Var1._Myptr = (Geizer **)local_c._padding_;
    _Var1._padding_ = (int)&local_c;
    insert(this,_Var1,local_c._Myptr);
  }
  return;
}
