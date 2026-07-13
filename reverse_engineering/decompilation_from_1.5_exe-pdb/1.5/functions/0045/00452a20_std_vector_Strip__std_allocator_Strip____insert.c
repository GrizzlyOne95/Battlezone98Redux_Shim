/*
 * Entry: 00452a20
 * Name: std::vector<Strip_*,std::allocator<Strip_*>_>::insert
 * Namespace: std::vector<Strip_*,std::allocator<Strip_*>_>
 * Signature: _Vector_iterator<Strip_*,std::allocator<Strip_*>_> insert(vector<Strip_*,std::allocator<Strip_*>_> * this, _Vector_const_iterator<Strip_*,std::allocator<Strip_*>_> param_1, Strip * * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<Strip_*,std::allocator<Strip_*>_> __thiscall
std::vector<Strip_*,std::allocator<Strip_*>_>::insert
          (vector<Strip_*,std::allocator<Strip_*>_> *this,
          _Vector_const_iterator<Strip_*,std::allocator<Strip_*>_> param_1,Strip **param_2)

{
  Strip **ppSVar1;
  int *piVar2;
  _Vector_const_iterator<Strip_*,std::allocator<Strip_*>_> _Var3;
  int iVar4;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 extraout_EDX_01;
  undefined4 extraout_EDX_02;
  undefined4 uVar5;
  int iVar6;
  _Vector_iterator<Strip_*,std::allocator<Strip_*>_> _Var7;
  Strip **in_stack_00000010;
  
  ppSVar1 = this->_Myfirst;
  if (((int)this->_Mylast - (int)ppSVar1 & 0xfffffffcU) == 0) {
    iVar6 = 0;
  }
  else {
    if (this->_Mylast < ppSVar1) {
      _invalid_parameter_noinfo();
    }
    if ((param_1._Myptr == (Strip **)0x0) || (param_1._Myptr != (Strip **)this->_padding_)) {
      _invalid_parameter_noinfo();
    }
    iVar6 = (int)param_2 - (int)ppSVar1 >> 2;
  }
  _Var3._Myptr = param_2;
  _Var3._padding_ = (int)param_1._Myptr;
  _Insert_n(this,_Var3,1,in_stack_00000010);
  ppSVar1 = this->_Myfirst;
  uVar5 = extraout_EDX;
  if (this->_Mylast < ppSVar1) {
    _invalid_parameter_noinfo();
    uVar5 = extraout_EDX_00;
  }
  piVar2 = (int *)this->_padding_;
  if (piVar2 == (int *)0x0) {
    _invalid_parameter_noinfo();
    iVar4 = 0;
    uVar5 = extraout_EDX_01;
  }
  else {
    iVar4 = *piVar2;
  }
  ppSVar1 = ppSVar1 + iVar6;
  if (ppSVar1 <= *(Strip ***)(iVar4 + 0x10)) {
    if (piVar2 == (int *)0x0) {
      iVar6 = 0;
    }
    else {
      iVar6 = *piVar2;
    }
    if (*(Strip ***)(iVar6 + 0xc) <= ppSVar1) goto LAB_00452ac1;
  }
  _invalid_parameter_noinfo();
  uVar5 = extraout_EDX_02;
LAB_00452ac1:
  *(Strip ***)(param_1._padding_ + 4) = ppSVar1;
  *(int **)param_1._padding_ = piVar2;
  _Var7._4_4_ = uVar5;
  _Var7._0_4_ = param_1._padding_;
  return _Var7;
}
