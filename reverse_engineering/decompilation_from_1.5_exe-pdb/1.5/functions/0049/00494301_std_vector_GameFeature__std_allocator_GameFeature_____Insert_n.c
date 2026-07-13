/*
 * Entry: 00494301
 * Name: std::vector<GameFeature_*,std::allocator<GameFeature_*>_>::_Insert_n
 * Namespace: std::vector<GameFeature_*,std::allocator<GameFeature_*>_>
 * Signature: void _Insert_n(vector<GameFeature_*,std::allocator<GameFeature_*>_> * this, _Vector_const_iterator<GameFeature_*,std::allocator<GameFeature_*>_> param_1, uint param_2, GameFeature * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::vector<GameFeature_*,std::allocator<GameFeature_*>_>::_Insert_n
          (vector<GameFeature_*,std::allocator<GameFeature_*>_> *this,
          _Vector_const_iterator<GameFeature_*,std::allocator<GameFeature_*>_> param_1,uint param_2,
          GameFeature **param_3)

{
  GameFeature **ppGVar1;
  GameFeature *pGVar2;
  GameFeature **ppGVar3;
  GameFeature **ppGVar4;
  int iVar5;
  uint uVar6;
  uint local_8;
  
  local_8 = capacity(this);
  if (param_2 != 0) {
    ppGVar1 = this->_Mylast;
    iVar5 = (int)ppGVar1 - (int)this->_Myfirst >> 2;
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
        ppGVar3 = _Allocate<GameFeature_*>(local_8,(GameFeature **)0x0);
        iVar5 = (int)param_1._Myptr - (int)this->_Myfirst >> 2;
        _Ufill(this,ppGVar3 + iVar5,param_2,param_3);
        _Umove<GameFeature_*_*>(this,this->_Myfirst,param_1._Myptr,ppGVar3);
        _Umove<GameFeature_*_*>(this,param_1._Myptr,this->_Mylast,ppGVar3 + iVar5 + param_2);
        ppGVar1 = this->_Myfirst;
        ppGVar4 = this->_Mylast;
        if (ppGVar1 != (GameFeature **)0x0) {
          operator_delete(ppGVar1);
        }
        this->_Myend = ppGVar3 + local_8;
        this->_Mylast = ppGVar3 + param_2 + ((int)ppGVar4 - (int)ppGVar1 >> 2);
        this->_Myfirst = ppGVar3;
      }
      else if ((uint)((int)ppGVar1 - (int)param_1._Myptr >> 2) < param_2) {
        param_3 = (GameFeature **)*param_3;
        _Umove<GameFeature_*_*>(this,param_1._Myptr,ppGVar1,param_1._Myptr + param_2);
        _Ufill(this,this->_Mylast,param_2 - ((int)this->_Mylast - (int)param_1._Myptr >> 2),
               (GameFeature **)&param_3);
        this->_Mylast = this->_Mylast + param_2;
        ppGVar1 = this->_Mylast;
        for (; param_1._Myptr != ppGVar1 + -param_2; param_1._Myptr = param_1._Myptr + 1) {
          *param_1._Myptr = (GameFeature *)param_3;
        }
      }
      else {
        pGVar2 = *param_3;
        param_3 = ppGVar1 + -param_2;
        ppGVar4 = _Umove<GameFeature_*_*>(this,param_3,ppGVar1,ppGVar1);
        this->_Mylast = ppGVar4;
        stdext::_Unchecked_move_backward<GameFeature_*_*,GameFeature_*_*>
                  (param_1._Myptr,param_3,ppGVar1);
        ppGVar1 = param_1._Myptr + param_2;
        for (; param_1._Myptr != ppGVar1; param_1._Myptr = param_1._Myptr + 1) {
          *param_1._Myptr = pGVar2;
        }
      }
    }
  }
  return;
}
