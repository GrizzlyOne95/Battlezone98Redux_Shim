/*
 * Entry: 00519984
 * Name: std::vector<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>::_Insert_n
 * Namespace: std::vector<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>
 * Signature: void _Insert_n(vector<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_> * this, _Vector_const_iterator<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_> param_1, uint param_2, ObjectClassInfo * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::vector<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>::_Insert_n
          (vector<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_> *this,
          _Vector_const_iterator<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_> param_1,
          uint param_2,ObjectClassInfo **param_3)

{
  ObjectClassInfo **ppOVar1;
  ObjectClassInfo *pOVar2;
  ObjectClassInfo **ppOVar3;
  ObjectClassInfo **ppOVar4;
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
        ppOVar3 = _Allocate<ObjectClassInfo_*>(local_8,(ObjectClassInfo **)0x0);
        iVar5 = (int)param_1._Myptr - (int)this->_Myfirst >> 2;
        _Ufill(this,ppOVar3 + iVar5,param_2,param_3);
        _Umove<ObjectClassInfo_*_*>(this,this->_Myfirst,param_1._Myptr,ppOVar3);
        _Umove<ObjectClassInfo_*_*>(this,param_1._Myptr,this->_Mylast,ppOVar3 + iVar5 + param_2);
        ppOVar1 = this->_Myfirst;
        ppOVar4 = this->_Mylast;
        if (ppOVar1 != (ObjectClassInfo **)0x0) {
          operator_delete(ppOVar1);
        }
        this->_Myend = ppOVar3 + local_8;
        this->_Mylast = ppOVar3 + param_2 + ((int)ppOVar4 - (int)ppOVar1 >> 2);
        this->_Myfirst = ppOVar3;
      }
      else if ((uint)((int)ppOVar1 - (int)param_1._Myptr >> 2) < param_2) {
        param_3 = (ObjectClassInfo **)*param_3;
        _Umove<ObjectClassInfo_*_*>(this,param_1._Myptr,ppOVar1,param_1._Myptr + param_2);
        _Ufill(this,this->_Mylast,param_2 - ((int)this->_Mylast - (int)param_1._Myptr >> 2),
               (ObjectClassInfo **)&param_3);
        this->_Mylast = this->_Mylast + param_2;
        ppOVar1 = this->_Mylast;
        for (; param_1._Myptr != ppOVar1 + -param_2; param_1._Myptr = param_1._Myptr + 1) {
          *param_1._Myptr = (ObjectClassInfo *)param_3;
        }
      }
      else {
        pOVar2 = *param_3;
        param_3 = ppOVar1 + -param_2;
        ppOVar4 = _Umove<ObjectClassInfo_*_*>(this,param_3,ppOVar1,ppOVar1);
        this->_Mylast = ppOVar4;
        stdext::_Unchecked_move_backward<ObjectClassInfo_*_*,ObjectClassInfo_*_*>
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
