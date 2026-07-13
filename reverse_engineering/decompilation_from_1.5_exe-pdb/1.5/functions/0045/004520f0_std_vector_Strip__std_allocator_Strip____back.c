/*
 * Entry: 004520f0
 * Name: std::vector<Strip_*,std::allocator<Strip_*>_>::back
 * Namespace: std::vector<Strip_*,std::allocator<Strip_*>_>
 * Signature: Strip * * back(vector<Strip_*,std::allocator<Strip_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Strip ** __thiscall
std::vector<Strip_*,std::allocator<Strip_*>_>::back(vector<Strip_*,std::allocator<Strip_*>_> *this)

{
  Strip **ppSVar1;
  int *piVar2;
  int iVar3;
  
  ppSVar1 = this->_Mylast;
  if (ppSVar1 < this->_Myfirst) {
    _invalid_parameter_noinfo();
  }
  piVar2 = (int *)this->_padding_;
  if (piVar2 == (int *)0x0) {
    _invalid_parameter_noinfo();
    iVar3 = 0;
  }
  else {
    iVar3 = *piVar2;
  }
  if (ppSVar1 + -1 <= *(Strip ***)(iVar3 + 0x10)) {
    if (piVar2 == (int *)0x0) {
      iVar3 = 0;
    }
    else {
      iVar3 = *piVar2;
    }
    if (*(Strip ***)(iVar3 + 0xc) <= ppSVar1 + -1) goto LAB_00452136;
  }
  _invalid_parameter_noinfo();
LAB_00452136:
  if (piVar2 == (int *)0x0) {
    _invalid_parameter_noinfo();
    iVar3 = 0;
  }
  else {
    iVar3 = *piVar2;
  }
  if (*(Strip ***)(iVar3 + 0x10) <= ppSVar1 + -1) {
    _invalid_parameter_noinfo();
  }
  return ppSVar1 + -1;
}
