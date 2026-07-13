/*
 * Entry: 0055bd68
 * Name: std::vector<Player_*,std::allocator<Player_*>_>::_Insert_n
 * Namespace: std::vector<Player_*,std::allocator<Player_*>_>
 * Signature: void _Insert_n(vector<Player_*,std::allocator<Player_*>_> * this, _Vector_const_iterator<Player_*,std::allocator<Player_*>_> param_1, uint param_2, Player * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::vector<Player_*,std::allocator<Player_*>_>::_Insert_n
          (vector<Player_*,std::allocator<Player_*>_> *this,
          _Vector_const_iterator<Player_*,std::allocator<Player_*>_> param_1,uint param_2,
          Player **param_3)

{
  Player **ppPVar1;
  Player *pPVar2;
  Player **ppPVar3;
  Player **ppPVar4;
  int iVar5;
  uint uVar6;
  uint local_8;
  
  local_8 = capacity(this);
  if (param_2 != 0) {
    ppPVar1 = this->_Mylast;
    iVar5 = (int)ppPVar1 - (int)this->_Myfirst >> 2;
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
        ppPVar3 = _Allocate<Player_*>(local_8,(Player **)0x0);
        iVar5 = (int)param_1._Myptr - (int)this->_Myfirst >> 2;
        _Ufill(this,ppPVar3 + iVar5,param_2,param_3);
        _Umove<Player_*_*>(this,this->_Myfirst,param_1._Myptr,ppPVar3);
        _Umove<Player_*_*>(this,param_1._Myptr,this->_Mylast,ppPVar3 + iVar5 + param_2);
        ppPVar1 = this->_Myfirst;
        ppPVar4 = this->_Mylast;
        if (ppPVar1 != (Player **)0x0) {
          operator_delete(ppPVar1);
        }
        this->_Myend = ppPVar3 + local_8;
        this->_Mylast = ppPVar3 + param_2 + ((int)ppPVar4 - (int)ppPVar1 >> 2);
        this->_Myfirst = ppPVar3;
      }
      else if ((uint)((int)ppPVar1 - (int)param_1._Myptr >> 2) < param_2) {
        param_3 = (Player **)*param_3;
        _Umove<Player_*_*>(this,param_1._Myptr,ppPVar1,param_1._Myptr + param_2);
        _Ufill(this,this->_Mylast,param_2 - ((int)this->_Mylast - (int)param_1._Myptr >> 2),
               (Player **)&param_3);
        this->_Mylast = this->_Mylast + param_2;
        ppPVar1 = this->_Mylast;
        for (; param_1._Myptr != ppPVar1 + -param_2; param_1._Myptr = param_1._Myptr + 1) {
          *param_1._Myptr = (Player *)param_3;
        }
      }
      else {
        pPVar2 = *param_3;
        param_3 = ppPVar1 + -param_2;
        ppPVar4 = _Umove<Player_*_*>(this,param_3,ppPVar1,ppPVar1);
        this->_Mylast = ppPVar4;
        stdext::_Unchecked_move_backward<Player_*_*,Player_*_*>(param_1._Myptr,param_3,ppPVar1);
        ppPVar1 = param_1._Myptr + param_2;
        for (; param_1._Myptr != ppPVar1; param_1._Myptr = param_1._Myptr + 1) {
          *param_1._Myptr = pPVar2;
        }
      }
    }
  }
  return;
}
