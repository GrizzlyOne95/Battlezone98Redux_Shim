/*
 * Entry: 00452c80
 * Name: std::vector<Strip_*,std::allocator<Strip_*>_>::push_back
 * Namespace: std::vector<Strip_*,std::allocator<Strip_*>_>
 * Signature: void push_back(vector<Strip_*,std::allocator<Strip_*>_> * this, Strip * * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::vector<Strip_*,std::allocator<Strip_*>_>::push_back
          (vector<Strip_*,std::allocator<Strip_*>_> *this,Strip **param_1)

{
  Strip **ppSVar1;
  Strip **ppSVar2;
  _Vector_const_iterator<Strip_*,std::allocator<Strip_*>_> _Var3;
  uint uVar4;
  undefined1 local_8 [8];
  
  ppSVar1 = this->_Myfirst;
  if (ppSVar1 == (Strip **)0x0) {
    uVar4 = 0;
  }
  else {
    uVar4 = (int)this->_Myend - (int)ppSVar1 >> 2;
  }
  ppSVar2 = this->_Mylast;
  if ((uint)((int)ppSVar2 - (int)ppSVar1 >> 2) < uVar4) {
    *ppSVar2 = *param_1;
    this->_Mylast = ppSVar2 + 1;
    return;
  }
  if (ppSVar2 < ppSVar1) {
    _invalid_parameter_noinfo();
  }
  _Var3._Myptr = (Strip **)this->_padding_;
  _Var3._padding_ = (int)local_8;
  insert(this,_Var3,ppSVar2);
  return;
}
