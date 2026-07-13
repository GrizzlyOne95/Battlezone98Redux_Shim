/*
 * Entry: 004894b0
 * Name: std::vector<Craft_*,std::allocator<Craft_*>_>::_Insert_n
 * Namespace: std::vector<Craft_*,std::allocator<Craft_*>_>
 * Signature: void _Insert_n(vector<Craft_*,std::allocator<Craft_*>_> * this, _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_> param_1, uint param_2, Craft * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::vector<Craft_*,std::allocator<Craft_*>_>::_Insert_n
          (vector<Craft_*,std::allocator<Craft_*>_> *this,
          _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_> param_1,uint param_2,
          Craft **param_3)

{
  Craft **ppCVar1;
  Craft *pCVar2;
  Craft **ppCVar3;
  Craft **ppCVar4;
  int iVar5;
  uint uVar6;
  uint local_8;
  
  local_8 = capacity(this);
  if (param_2 != 0) {
    ppCVar1 = this->_Mylast;
    iVar5 = (int)ppCVar1 - (int)this->_Myfirst >> 2;
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
        ppCVar3 = _Allocate<Craft_*>(local_8,(Craft **)0x0);
        iVar5 = (int)param_1._Myptr - (int)this->_Myfirst >> 2;
        _Ufill(this,ppCVar3 + iVar5,param_2,param_3);
        _Umove<Craft_*_*>(this,this->_Myfirst,param_1._Myptr,ppCVar3);
        _Umove<Craft_*_*>(this,param_1._Myptr,this->_Mylast,ppCVar3 + iVar5 + param_2);
        ppCVar1 = this->_Myfirst;
        ppCVar4 = this->_Mylast;
        if (ppCVar1 != (Craft **)0x0) {
          operator_delete(ppCVar1);
        }
        this->_Myend = ppCVar3 + local_8;
        this->_Mylast = ppCVar3 + param_2 + ((int)ppCVar4 - (int)ppCVar1 >> 2);
        this->_Myfirst = ppCVar3;
      }
      else if ((uint)((int)ppCVar1 - (int)param_1._Myptr >> 2) < param_2) {
        param_3 = (Craft **)*param_3;
        _Umove<Craft_*_*>(this,param_1._Myptr,ppCVar1,param_1._Myptr + param_2);
        _Ufill(this,this->_Mylast,param_2 - ((int)this->_Mylast - (int)param_1._Myptr >> 2),
               (Craft **)&param_3);
        this->_Mylast = this->_Mylast + param_2;
        ppCVar1 = this->_Mylast;
        for (; param_1._Myptr != ppCVar1 + -param_2; param_1._Myptr = param_1._Myptr + 1) {
          *param_1._Myptr = (Craft *)param_3;
        }
      }
      else {
        pCVar2 = *param_3;
        param_3 = ppCVar1 + -param_2;
        ppCVar4 = _Umove<Craft_*_*>(this,param_3,ppCVar1,ppCVar1);
        this->_Mylast = ppCVar4;
        stdext::_Unchecked_move_backward<Craft_*_*,Craft_*_*>(param_1._Myptr,param_3,ppCVar1);
        ppCVar1 = param_1._Myptr + param_2;
        for (; param_1._Myptr != ppCVar1; param_1._Myptr = param_1._Myptr + 1) {
          *param_1._Myptr = pCVar2;
        }
      }
    }
  }
  return;
}
