/*
 * Entry: 00535753
 * Name: std::vector<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_>::_Insert_n
 * Namespace: std::vector<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_>
 * Signature: void _Insert_n(vector<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_> * this, _Vector_const_iterator<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_> param_1, uint param_2, OrdnanceClass * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::vector<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_>::_Insert_n
          (vector<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_> *this,
          _Vector_const_iterator<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_> param_1,
          uint param_2,OrdnanceClass **param_3)

{
  OrdnanceClass **ppOVar1;
  OrdnanceClass *pOVar2;
  OrdnanceClass **ppOVar3;
  OrdnanceClass **ppOVar4;
  int iVar5;
  uint uVar6;
  uint local_8;
  
  local_8 = capacity(this);
  if (param_2 != 0) {
    ppOVar1 = this->_Mylast;
    iVar5 = (int)ppOVar1 - (int)this->_Myfirst >> 2;
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
        ppOVar3 = _Allocate<OrdnanceClass_*>(local_8,(OrdnanceClass **)0x0);
        iVar5 = (int)param_1._Myptr - (int)this->_Myfirst >> 2;
        _Ufill(this,ppOVar3 + iVar5,param_2,param_3);
        _Umove<OrdnanceClass_*_*>(this,this->_Myfirst,param_1._Myptr,ppOVar3);
        _Umove<OrdnanceClass_*_*>(this,param_1._Myptr,this->_Mylast,ppOVar3 + iVar5 + param_2);
        ppOVar1 = this->_Myfirst;
        ppOVar4 = this->_Mylast;
        if (ppOVar1 != (OrdnanceClass **)0x0) {
          operator_delete(ppOVar1);
        }
        this->_Myend = ppOVar3 + local_8;
        this->_Mylast = ppOVar3 + param_2 + ((int)ppOVar4 - (int)ppOVar1 >> 2);
        this->_Myfirst = ppOVar3;
      }
      else if ((uint)((int)ppOVar1 - (int)param_1._Myptr >> 2) < param_2) {
        param_3 = (OrdnanceClass **)*param_3;
        _Umove<OrdnanceClass_*_*>(this,param_1._Myptr,ppOVar1,param_1._Myptr + param_2);
        _Ufill(this,this->_Mylast,param_2 - ((int)this->_Mylast - (int)param_1._Myptr >> 2),
               (OrdnanceClass **)&param_3);
        this->_Mylast = this->_Mylast + param_2;
        ppOVar1 = this->_Mylast;
        for (; param_1._Myptr != ppOVar1 + -param_2; param_1._Myptr = param_1._Myptr + 1) {
          *param_1._Myptr = (OrdnanceClass *)param_3;
        }
      }
      else {
        pOVar2 = *param_3;
        param_3 = ppOVar1 + -param_2;
        ppOVar4 = _Umove<OrdnanceClass_*_*>(this,param_3,ppOVar1,ppOVar1);
        this->_Mylast = ppOVar4;
        stdext::_Unchecked_move_backward<OrdnanceClass_*_*,OrdnanceClass_*_*>
                  (param_1._Myptr,param_3,ppOVar1);
        ppOVar1 = param_1._Myptr + param_2;
        for (; param_1._Myptr != ppOVar1; param_1._Myptr = param_1._Myptr + 1) {
          *param_1._Myptr = pOVar2;
        }
      }
    }
  }
  return;
}
