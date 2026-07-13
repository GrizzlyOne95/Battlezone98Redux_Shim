/*
 * Entry: 00519d8f
 * Name: std::vector<GridPoint,std::allocator<GridPoint>_>::_Insert_n
 * Namespace: std::vector<GridPoint,std::allocator<GridPoint>_>
 * Signature: void _Insert_n(vector<GridPoint,std::allocator<GridPoint>_> * this, _Vector_const_iterator<GridPoint,std::allocator<GridPoint>_> param_1, uint param_2, GridPoint * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::vector<GridPoint,std::allocator<GridPoint>_>::_Insert_n
          (vector<GridPoint,std::allocator<GridPoint>_> *this,
          _Vector_const_iterator<GridPoint,std::allocator<GridPoint>_> param_1,uint param_2,
          GridPoint *param_3)

{
  GridPoint *pGVar1;
  int iVar2;
  uint uVar3;
  GridPoint *pGVar4;
  GridPoint *pGVar5;
  GridPoint local_c;
  
  local_c.x = (int)this;
  local_c.y = (int)this;
  local_c.y = capacity(this);
  if (param_2 != 0) {
    pGVar1 = this->_Mylast;
    iVar2 = (int)pGVar1 - (int)this->_Myfirst >> 3;
    if (0x1fffffffU - iVar2 < param_2) {
      _Xlen();
    }
    else {
      uVar3 = iVar2 + param_2;
      if ((uint)local_c.y < uVar3) {
        if (0x1fffffff - ((uint)local_c.y >> 1) < (uint)local_c.y) {
          local_c.y = 0;
        }
        else {
          local_c.y = local_c.y + ((uint)local_c.y >> 1);
        }
        if ((uint)local_c.y < uVar3) {
          local_c.y = uVar3;
        }
        pGVar4 = _Allocate<GridPoint>(local_c.y,(GridPoint *)0x0);
        iVar2 = (int)param_1._Myptr - (int)this->_Myfirst >> 3;
        _Ufill(this,pGVar4 + iVar2,param_2,param_3);
        _Umove<GridPoint_*>(this,this->_Myfirst,param_1._Myptr,pGVar4);
        _Umove<GridPoint_*>(this,param_1._Myptr,this->_Mylast,pGVar4 + iVar2 + param_2);
        pGVar1 = this->_Myfirst;
        pGVar5 = this->_Mylast;
        if (pGVar1 != (GridPoint *)0x0) {
          operator_delete(pGVar1);
        }
        this->_Myend = pGVar4 + local_c.y;
        this->_Mylast = pGVar4 + param_2 + ((int)pGVar5 - (int)pGVar1 >> 3);
        this->_Myfirst = pGVar4;
      }
      else if ((uint)((int)pGVar1 - (int)param_1._Myptr >> 3) < param_2) {
        local_c.x = param_3->x;
        local_c.y = param_3->y;
        _Umove<GridPoint_*>(this,param_1._Myptr,pGVar1,param_1._Myptr + param_2);
        _Ufill(this,this->_Mylast,param_2 - ((int)this->_Mylast - (int)param_1._Myptr >> 3),&local_c
              );
        this->_Mylast = this->_Mylast + param_2;
        _Fill<GridPoint_*,GridPoint>(param_1._Myptr,this->_Mylast + -param_2,&local_c);
      }
      else {
        local_c.x = param_3->x;
        local_c.y = param_3->y;
        pGVar5 = _Umove<GridPoint_*>(this,pGVar1 + -param_2,pGVar1,pGVar1);
        this->_Mylast = pGVar5;
        stdext::_Unchecked_move_backward<GridPoint_*,GridPoint_*>
                  (param_1._Myptr,pGVar1 + -param_2,pGVar1);
        _Fill<GridPoint_*,GridPoint>(param_1._Myptr,param_1._Myptr + param_2,&local_c);
      }
    }
  }
  return;
}
