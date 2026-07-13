/*
 * Entry: 00452650
 * Name: std::vector<Strip_*,std::allocator<Strip_*>_>::_Insert_n
 * Namespace: std::vector<Strip_*,std::allocator<Strip_*>_>
 * Signature: void _Insert_n(vector<Strip_*,std::allocator<Strip_*>_> * this, _Vector_const_iterator<Strip_*,std::allocator<Strip_*>_> param_1, uint param_2, Strip * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::vector<Strip_*,std::allocator<Strip_*>_>::_Insert_n
          (vector<Strip_*,std::allocator<Strip_*>_> *this,
          _Vector_const_iterator<Strip_*,std::allocator<Strip_*>_> param_1,uint param_2,
          Strip **param_3)

{
  uint uVar1;
  Strip **ppSVar2;
  int iVar3;
  Strip **ppSVar4;
  Strip **ppSVar5;
  uint local_4;
  
  ppSVar5 = this->_Myfirst;
  if (ppSVar5 == (Strip **)0x0) {
    local_4 = 0;
  }
  else {
    local_4 = (int)this->_Myend - (int)ppSVar5 >> 2;
  }
  if (param_2 != 0) {
    ppSVar2 = this->_Mylast;
    iVar3 = (int)ppSVar2 - (int)ppSVar5 >> 2;
    if (0x3fffffffU - iVar3 < param_2) {
      _Xlen();
      return;
    }
    uVar1 = iVar3 + param_2;
    if (local_4 < uVar1) {
      if (0x3fffffff - (local_4 >> 1) < local_4) {
        local_4 = 0;
      }
      else {
        local_4 = local_4 + (local_4 >> 1);
      }
      if (local_4 < uVar1) {
        local_4 = uVar1;
      }
      ppSVar4 = _Allocate<Strip_*>(local_4,(Strip **)0x0);
      iVar3 = (int)param_1._Myptr - (int)this->_Myfirst >> 2;
      _Ufill(this,ppSVar4 + iVar3,param_2,param_3);
      _Umove<Strip_*_*>(this,this->_Myfirst,param_1._Myptr,ppSVar4);
      _Umove<Strip_*_*>(this,param_1._Myptr,this->_Mylast,ppSVar4 + iVar3 + param_2);
      ppSVar5 = this->_Myfirst;
      ppSVar2 = this->_Mylast;
      if (ppSVar5 != (Strip **)0x0) {
        operator_delete(ppSVar5);
      }
      this->_Myfirst = ppSVar4;
      this->_Myend = ppSVar4 + local_4;
      this->_Mylast = ppSVar4 + param_2 + ((int)ppSVar2 - (int)ppSVar5 >> 2);
      return;
    }
    param_3 = (Strip **)*param_3;
    if ((uint)((int)ppSVar2 - (int)param_1._Myptr >> 2) < param_2) {
      _Umove<Strip_*_*>(this,param_1._Myptr,ppSVar2,param_1._Myptr + param_2);
      _Ufill(this,this->_Mylast,param_2 - ((int)this->_Mylast - (int)param_1._Myptr >> 2),
             (Strip **)&param_3);
      this->_Mylast = this->_Mylast + param_2;
      fill<Strip_*_*,Strip_*>(param_1._Myptr,this->_Mylast + -param_2,(Strip **)&param_3);
      return;
    }
    ppSVar5 = _Umove<Strip_*_*>(this,ppSVar2 + -param_2,ppSVar2,ppSVar2);
    this->_Mylast = ppSVar5;
    stdext::_Unchecked_move_backward<Strip_*_*,Strip_*_*>(param_1._Myptr,ppSVar2 + -param_2,ppSVar2)
    ;
    fill<Strip_*_*,Strip_*>(param_1._Myptr,param_1._Myptr + param_2,(Strip **)&param_3);
  }
  return;
}
