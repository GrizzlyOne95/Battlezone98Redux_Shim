/*
 * Entry: 0053f157
 * Name: std::vector<WeaponClass_*,std::allocator<WeaponClass_*>_>::_Insert_n
 * Namespace: std::vector<WeaponClass_*,std::allocator<WeaponClass_*>_>
 * Signature: void _Insert_n(vector<WeaponClass_*,std::allocator<WeaponClass_*>_> * this, _Vector_const_iterator<WeaponClass_*,std::allocator<WeaponClass_*>_> param_1, uint param_2, WeaponClass * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::vector<WeaponClass_*,std::allocator<WeaponClass_*>_>::_Insert_n
          (vector<WeaponClass_*,std::allocator<WeaponClass_*>_> *this,
          _Vector_const_iterator<WeaponClass_*,std::allocator<WeaponClass_*>_> param_1,uint param_2,
          WeaponClass **param_3)

{
  WeaponClass **ppWVar1;
  WeaponClass *pWVar2;
  WeaponClass **ppWVar3;
  WeaponClass **ppWVar4;
  int iVar5;
  uint uVar6;
  uint local_8;
  
  local_8 = capacity(this);
  if (param_2 != 0) {
    ppWVar1 = this->_Mylast;
    iVar5 = (int)ppWVar1 - (int)this->_Myfirst >> 2;
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
        ppWVar3 = _Allocate<WeaponClass_*>(local_8,(WeaponClass **)0x0);
        iVar5 = (int)param_1._Myptr - (int)this->_Myfirst >> 2;
        _Ufill(this,ppWVar3 + iVar5,param_2,param_3);
        _Umove<WeaponClass_*_*>(this,this->_Myfirst,param_1._Myptr,ppWVar3);
        _Umove<WeaponClass_*_*>(this,param_1._Myptr,this->_Mylast,ppWVar3 + iVar5 + param_2);
        ppWVar1 = this->_Myfirst;
        ppWVar4 = this->_Mylast;
        if (ppWVar1 != (WeaponClass **)0x0) {
          operator_delete(ppWVar1);
        }
        this->_Myend = ppWVar3 + local_8;
        this->_Mylast = ppWVar3 + param_2 + ((int)ppWVar4 - (int)ppWVar1 >> 2);
        this->_Myfirst = ppWVar3;
      }
      else if ((uint)((int)ppWVar1 - (int)param_1._Myptr >> 2) < param_2) {
        param_3 = (WeaponClass **)*param_3;
        _Umove<WeaponClass_*_*>(this,param_1._Myptr,ppWVar1,param_1._Myptr + param_2);
        _Ufill(this,this->_Mylast,param_2 - ((int)this->_Mylast - (int)param_1._Myptr >> 2),
               (WeaponClass **)&param_3);
        this->_Mylast = this->_Mylast + param_2;
        ppWVar1 = this->_Mylast;
        for (; param_1._Myptr != ppWVar1 + -param_2; param_1._Myptr = param_1._Myptr + 1) {
          *param_1._Myptr = (WeaponClass *)param_3;
        }
      }
      else {
        pWVar2 = *param_3;
        param_3 = ppWVar1 + -param_2;
        ppWVar4 = _Umove<WeaponClass_*_*>(this,param_3,ppWVar1,ppWVar1);
        this->_Mylast = ppWVar4;
        stdext::_Unchecked_move_backward<WeaponClass_*_*,WeaponClass_*_*>
                  (param_1._Myptr,param_3,ppWVar1);
        ppWVar1 = param_1._Myptr + param_2;
        for (; param_1._Myptr != ppWVar1; param_1._Myptr = param_1._Myptr + 1) {
          *param_1._Myptr = pWVar2;
        }
      }
    }
  }
  return;
}
