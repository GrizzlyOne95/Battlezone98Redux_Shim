/*
 * Entry: 0047d678
 * Name: std::vector<AnimSprite_*,std::allocator<AnimSprite_*>_>::_Insert_n
 * Namespace: std::vector<AnimSprite_*,std::allocator<AnimSprite_*>_>
 * Signature: void _Insert_n(vector<AnimSprite_*,std::allocator<AnimSprite_*>_> * this, _Vector_const_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_> param_1, uint param_2, AnimSprite * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::vector<AnimSprite_*,std::allocator<AnimSprite_*>_>::_Insert_n
          (vector<AnimSprite_*,std::allocator<AnimSprite_*>_> *this,
          _Vector_const_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_> param_1,uint param_2,
          AnimSprite **param_3)

{
  AnimSprite **ppAVar1;
  AnimSprite *pAVar2;
  AnimSprite **ppAVar3;
  AnimSprite **ppAVar4;
  int iVar5;
  uint uVar6;
  uint local_8;
  
  local_8 = capacity(this);
  if (param_2 != 0) {
    ppAVar1 = this->_Mylast;
    iVar5 = (int)ppAVar1 - (int)this->_Myfirst >> 2;
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
        ppAVar3 = _Allocate<AnimSprite_*>(local_8,(AnimSprite **)0x0);
        iVar5 = (int)param_1._Myptr - (int)this->_Myfirst >> 2;
        _Ufill(this,ppAVar3 + iVar5,param_2,param_3);
        _Umove<AnimSprite_*_*>(this,this->_Myfirst,param_1._Myptr,ppAVar3);
        _Umove<AnimSprite_*_*>(this,param_1._Myptr,this->_Mylast,ppAVar3 + iVar5 + param_2);
        ppAVar1 = this->_Myfirst;
        ppAVar4 = this->_Mylast;
        if (ppAVar1 != (AnimSprite **)0x0) {
          operator_delete(ppAVar1);
        }
        this->_Myend = ppAVar3 + local_8;
        this->_Mylast = ppAVar3 + param_2 + ((int)ppAVar4 - (int)ppAVar1 >> 2);
        this->_Myfirst = ppAVar3;
      }
      else if ((uint)((int)ppAVar1 - (int)param_1._Myptr >> 2) < param_2) {
        param_3 = (AnimSprite **)*param_3;
        _Umove<AnimSprite_*_*>(this,param_1._Myptr,ppAVar1,param_1._Myptr + param_2);
        _Ufill(this,this->_Mylast,param_2 - ((int)this->_Mylast - (int)param_1._Myptr >> 2),
               (AnimSprite **)&param_3);
        this->_Mylast = this->_Mylast + param_2;
        ppAVar1 = this->_Mylast;
        for (; param_1._Myptr != ppAVar1 + -param_2; param_1._Myptr = param_1._Myptr + 1) {
          *param_1._Myptr = (AnimSprite *)param_3;
        }
      }
      else {
        pAVar2 = *param_3;
        param_3 = ppAVar1 + -param_2;
        ppAVar4 = _Umove<AnimSprite_*_*>(this,param_3,ppAVar1,ppAVar1);
        this->_Mylast = ppAVar4;
        stdext::_Unchecked_move_backward<AnimSprite_*_*,AnimSprite_*_*>
                  (param_1._Myptr,param_3,ppAVar1);
        ppAVar1 = param_1._Myptr + param_2;
        for (; param_1._Myptr != ppAVar1; param_1._Myptr = param_1._Myptr + 1) {
          *param_1._Myptr = pAVar2;
        }
      }
    }
  }
  return;
}
