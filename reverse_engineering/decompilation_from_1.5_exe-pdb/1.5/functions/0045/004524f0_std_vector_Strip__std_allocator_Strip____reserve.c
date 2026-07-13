/*
 * Entry: 004524f0
 * Name: std::vector<Strip_*,std::allocator<Strip_*>_>::reserve
 * Namespace: std::vector<Strip_*,std::allocator<Strip_*>_>
 * Signature: void reserve(vector<Strip_*,std::allocator<Strip_*>_> * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::vector<Strip_*,std::allocator<Strip_*>_>::reserve
          (vector<Strip_*,std::allocator<Strip_*>_> *this,uint param_1)

{
  rsize_t _DstSize;
  Strip **ppSVar1;
  Strip **ppSVar2;
  uint uVar3;
  Strip **_Dst;
  int iVar4;
  
  if (0x3fffffff < param_1) {
    _Xlen();
    return;
  }
  if (this->_Myfirst == (Strip **)0x0) {
    uVar3 = 0;
  }
  else {
    uVar3 = (int)this->_Myend - (int)this->_Myfirst >> 2;
  }
  if (uVar3 < param_1) {
    _Dst = _Allocate<Strip_*>(param_1,(Strip **)0x0);
    ppSVar1 = this->_Mylast;
    if (ppSVar1 < this->_Myfirst) {
      _invalid_parameter_noinfo();
    }
    ppSVar2 = this->_Myfirst;
    if (this->_Mylast < ppSVar2) {
      _invalid_parameter_noinfo();
    }
    iVar4 = (int)ppSVar1 - (int)ppSVar2 >> 2;
    if (iVar4 != 0) {
      _DstSize = iVar4 * 4;
      memmove_s(_Dst,_DstSize,ppSVar2,_DstSize);
    }
    ppSVar1 = this->_Myfirst;
    ppSVar2 = this->_Mylast;
    if (ppSVar1 != (Strip **)0x0) {
      operator_delete(ppSVar1);
    }
    this->_Myfirst = _Dst;
    this->_Myend = _Dst + param_1;
    this->_Mylast = _Dst + ((int)ppSVar2 - (int)ppSVar1 >> 2);
  }
  return;
}
