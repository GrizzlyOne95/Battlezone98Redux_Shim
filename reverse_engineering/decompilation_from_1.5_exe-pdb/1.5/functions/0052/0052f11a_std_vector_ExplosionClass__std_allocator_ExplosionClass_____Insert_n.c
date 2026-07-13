/*
 * Entry: 0052f11a
 * Name: std::vector<ExplosionClass_*,std::allocator<ExplosionClass_*>_>::_Insert_n
 * Namespace: std::vector<ExplosionClass_*,std::allocator<ExplosionClass_*>_>
 * Signature: void _Insert_n(vector<ExplosionClass_*,std::allocator<ExplosionClass_*>_> * this, _Vector_const_iterator<ExplosionClass_*,std::allocator<ExplosionClass_*>_> param_1, uint param_2, ExplosionClass * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::vector<ExplosionClass_*,std::allocator<ExplosionClass_*>_>::_Insert_n
          (vector<ExplosionClass_*,std::allocator<ExplosionClass_*>_> *this,
          _Vector_const_iterator<ExplosionClass_*,std::allocator<ExplosionClass_*>_> param_1,
          uint param_2,ExplosionClass **param_3)

{
  ExplosionClass **ppEVar1;
  ExplosionClass *pEVar2;
  ExplosionClass **ppEVar3;
  ExplosionClass **ppEVar4;
  int iVar5;
  uint uVar6;
  uint local_8;
  
  local_8 = capacity(this);
  if (param_2 != 0) {
    ppEVar1 = this->_Mylast;
    iVar5 = (int)ppEVar1 - (int)this->_Myfirst >> 2;
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
        ppEVar3 = _Allocate<ExplosionClass_*>(local_8,(ExplosionClass **)0x0);
        iVar5 = (int)param_1._Myptr - (int)this->_Myfirst >> 2;
        _Ufill(this,ppEVar3 + iVar5,param_2,param_3);
        _Umove<ExplosionClass_*_*>(this,this->_Myfirst,param_1._Myptr,ppEVar3);
        _Umove<ExplosionClass_*_*>(this,param_1._Myptr,this->_Mylast,ppEVar3 + iVar5 + param_2);
        ppEVar1 = this->_Myfirst;
        ppEVar4 = this->_Mylast;
        if (ppEVar1 != (ExplosionClass **)0x0) {
          operator_delete(ppEVar1);
        }
        this->_Myend = ppEVar3 + local_8;
        this->_Mylast = ppEVar3 + param_2 + ((int)ppEVar4 - (int)ppEVar1 >> 2);
        this->_Myfirst = ppEVar3;
      }
      else if ((uint)((int)ppEVar1 - (int)param_1._Myptr >> 2) < param_2) {
        param_3 = (ExplosionClass **)*param_3;
        _Umove<ExplosionClass_*_*>(this,param_1._Myptr,ppEVar1,param_1._Myptr + param_2);
        _Ufill(this,this->_Mylast,param_2 - ((int)this->_Mylast - (int)param_1._Myptr >> 2),
               (ExplosionClass **)&param_3);
        this->_Mylast = this->_Mylast + param_2;
        ppEVar1 = this->_Mylast;
        for (; param_1._Myptr != ppEVar1 + -param_2; param_1._Myptr = param_1._Myptr + 1) {
          *param_1._Myptr = (ExplosionClass *)param_3;
        }
      }
      else {
        pEVar2 = *param_3;
        param_3 = ppEVar1 + -param_2;
        ppEVar4 = _Umove<ExplosionClass_*_*>(this,param_3,ppEVar1,ppEVar1);
        this->_Mylast = ppEVar4;
        stdext::_Unchecked_move_backward<ExplosionClass_*_*,ExplosionClass_*_*>
                  (param_1._Myptr,param_3,ppEVar1);
        ppEVar1 = param_1._Myptr + param_2;
        for (; param_1._Myptr != ppEVar1; param_1._Myptr = param_1._Myptr + 1) {
          *param_1._Myptr = pEVar2;
        }
      }
    }
  }
  return;
}
