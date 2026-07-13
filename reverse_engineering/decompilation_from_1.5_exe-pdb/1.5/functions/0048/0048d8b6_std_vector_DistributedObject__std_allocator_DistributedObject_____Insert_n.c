/*
 * Entry: 0048d8b6
 * Name: std::vector<DistributedObject_*,std::allocator<DistributedObject_*>_>::_Insert_n
 * Namespace: std::vector<DistributedObject_*,std::allocator<DistributedObject_*>_>
 * Signature: void _Insert_n(vector<DistributedObject_*,std::allocator<DistributedObject_*>_> * this, _Vector_const_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_> param_1, uint param_2, DistributedObject * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::vector<DistributedObject_*,std::allocator<DistributedObject_*>_>::_Insert_n
          (vector<DistributedObject_*,std::allocator<DistributedObject_*>_> *this,
          _Vector_const_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_> param_1,
          uint param_2,DistributedObject **param_3)

{
  DistributedObject **ppDVar1;
  DistributedObject *pDVar2;
  DistributedObject **ppDVar3;
  DistributedObject **ppDVar4;
  int iVar5;
  uint uVar6;
  uint local_8;
  
  local_8 = capacity(this);
  if (param_2 != 0) {
    ppDVar1 = this->_Mylast;
    iVar5 = (int)ppDVar1 - (int)this->_Myfirst >> 2;
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
        ppDVar3 = _Allocate<DistributedObject_*>(local_8,(DistributedObject **)0x0);
        iVar5 = (int)param_1._Myptr - (int)this->_Myfirst >> 2;
        _Ufill(this,ppDVar3 + iVar5,param_2,param_3);
        _Umove<DistributedObject_*_*>(this,this->_Myfirst,param_1._Myptr,ppDVar3);
        _Umove<DistributedObject_*_*>(this,param_1._Myptr,this->_Mylast,ppDVar3 + iVar5 + param_2);
        ppDVar1 = this->_Myfirst;
        ppDVar4 = this->_Mylast;
        if (ppDVar1 != (DistributedObject **)0x0) {
          operator_delete(ppDVar1);
        }
        this->_Myend = ppDVar3 + local_8;
        this->_Mylast = ppDVar3 + param_2 + ((int)ppDVar4 - (int)ppDVar1 >> 2);
        this->_Myfirst = ppDVar3;
      }
      else if ((uint)((int)ppDVar1 - (int)param_1._Myptr >> 2) < param_2) {
        param_3 = (DistributedObject **)*param_3;
        _Umove<DistributedObject_*_*>(this,param_1._Myptr,ppDVar1,param_1._Myptr + param_2);
        _Ufill(this,this->_Mylast,param_2 - ((int)this->_Mylast - (int)param_1._Myptr >> 2),
               (DistributedObject **)&param_3);
        this->_Mylast = this->_Mylast + param_2;
        ppDVar1 = this->_Mylast;
        for (; param_1._Myptr != ppDVar1 + -param_2; param_1._Myptr = param_1._Myptr + 1) {
          *param_1._Myptr = (DistributedObject *)param_3;
        }
      }
      else {
        pDVar2 = *param_3;
        param_3 = ppDVar1 + -param_2;
        ppDVar4 = _Umove<DistributedObject_*_*>(this,param_3,ppDVar1,ppDVar1);
        this->_Mylast = ppDVar4;
        stdext::_Unchecked_move_backward<DistributedObject_*_*,DistributedObject_*_*>
                  (param_1._Myptr,param_3,ppDVar1);
        ppDVar1 = param_1._Myptr + param_2;
        for (; param_1._Myptr != ppDVar1; param_1._Myptr = param_1._Myptr + 1) {
          *param_1._Myptr = pDVar2;
        }
      }
    }
  }
  return;
}
