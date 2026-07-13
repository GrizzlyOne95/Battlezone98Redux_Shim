/*
 * Entry: 0046153f
 * Name: std::vector<Scrap_*,std::allocator<Scrap_*>_>::_Insert_n
 * Namespace: std::vector<Scrap_*,std::allocator<Scrap_*>_>
 * Signature: void _Insert_n(vector<Scrap_*,std::allocator<Scrap_*>_> * this, _Vector_const_iterator<Scrap_*,std::allocator<Scrap_*>_> param_1, uint param_2, Scrap * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::vector<Scrap_*,std::allocator<Scrap_*>_>::_Insert_n
          (vector<Scrap_*,std::allocator<Scrap_*>_> *this,
          _Vector_const_iterator<Scrap_*,std::allocator<Scrap_*>_> param_1,uint param_2,
          Scrap **param_3)

{
  Scrap **ppSVar1;
  Scrap *pSVar2;
  Scrap **ppSVar3;
  Scrap **ppSVar4;
  int iVar5;
  uint uVar6;
  uint local_8;
  
  local_8 = capacity(this);
  if (param_2 != 0) {
    ppSVar1 = this->_Mylast;
    iVar5 = (int)ppSVar1 - (int)this->_Myfirst >> 2;
    if (0x3fffffffU - iVar5 < param_2) {
      _Xlen();
    }
    else {
      uVar6 = iVar5 + param_2;
      if (local_8 < uVar6) {
        if (0x3fffffff - (local_8 >> 1) < local_8) {
          local_8 = 0;
        }
        else {
          local_8 = local_8 + (local_8 >> 1);
        }
        if (local_8 < uVar6) {
          local_8 = uVar6;
        }
        ppSVar3 = _Allocate<Scrap_*>(local_8,(Scrap **)0x0);
        iVar5 = (int)param_1._Myptr - (int)this->_Myfirst >> 2;
        _Ufill(this,ppSVar3 + iVar5,param_2,param_3);
        _Umove<Scrap_*_*>(this,this->_Myfirst,param_1._Myptr,ppSVar3);
        _Umove<Scrap_*_*>(this,param_1._Myptr,this->_Mylast,ppSVar3 + iVar5 + param_2);
        ppSVar1 = this->_Myfirst;
        ppSVar4 = this->_Mylast;
        if (ppSVar1 != (Scrap **)0x0) {
          operator_delete(ppSVar1);
        }
        this->_Myend = ppSVar3 + local_8;
        this->_Mylast = ppSVar3 + param_2 + ((int)ppSVar4 - (int)ppSVar1 >> 2);
        this->_Myfirst = ppSVar3;
      }
      else if ((uint)((int)ppSVar1 - (int)param_1._Myptr >> 2) < param_2) {
        param_3 = (Scrap **)*param_3;
        _Umove<Scrap_*_*>(this,param_1._Myptr,ppSVar1,param_1._Myptr + param_2);
        _Ufill(this,this->_Mylast,param_2 - ((int)this->_Mylast - (int)param_1._Myptr >> 2),
               (Scrap **)&param_3);
        this->_Mylast = this->_Mylast + param_2;
        ppSVar1 = this->_Mylast;
        for (; param_1._Myptr != ppSVar1 + -param_2; param_1._Myptr = param_1._Myptr + 1) {
          *param_1._Myptr = (Scrap *)param_3;
        }
      }
      else {
        pSVar2 = *param_3;
        param_3 = ppSVar1 + -param_2;
        ppSVar4 = _Umove<Scrap_*_*>(this,param_3,ppSVar1,ppSVar1);
        this->_Mylast = ppSVar4;
        stdext::_Unchecked_move_backward<Scrap_*_*,Scrap_*_*>(param_1._Myptr,param_3,ppSVar1);
        ppSVar1 = param_1._Myptr + param_2;
        for (; param_1._Myptr != ppSVar1; param_1._Myptr = param_1._Myptr + 1) {
          *param_1._Myptr = pSVar2;
        }
      }
    }
  }
  return;
}
