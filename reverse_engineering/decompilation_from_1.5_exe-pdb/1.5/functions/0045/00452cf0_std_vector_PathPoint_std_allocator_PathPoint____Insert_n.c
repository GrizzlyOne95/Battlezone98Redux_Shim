/*
 * Entry: 00452cf0
 * Name: std::vector<PathPoint,std::allocator<PathPoint>_>::_Insert_n
 * Namespace: std::vector<PathPoint,std::allocator<PathPoint>_>
 * Signature: void _Insert_n(vector<PathPoint,std::allocator<PathPoint>_> * this, _Vector_const_iterator<PathPoint,std::allocator<PathPoint>_> param_1, uint param_2, PathPoint * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::vector<PathPoint,std::allocator<PathPoint>_>::_Insert_n
          (vector<PathPoint,std::allocator<PathPoint>_> *this,
          _Vector_const_iterator<PathPoint,std::allocator<PathPoint>_> param_1,uint param_2,
          PathPoint *param_3)

{
  uint uVar1;
  PathPoint *pPVar2;
  int iVar3;
  PathPoint *pPVar4;
  PathPoint *pPVar5;
  uint uVar6;
  PathPoint local_10;
  
  pPVar5 = this->_Myfirst;
  if (pPVar5 == (PathPoint *)0x0) {
    uVar6 = 0;
  }
  else {
    uVar6 = (int)this->_Myend - (int)pPVar5 >> 4;
  }
  if (param_2 != 0) {
    pPVar2 = this->_Mylast;
    iVar3 = (int)pPVar2 - (int)pPVar5 >> 4;
    if (0xfffffffU - iVar3 < param_2) {
      _Xlen();
      return;
    }
    uVar1 = iVar3 + param_2;
    if (uVar6 < uVar1) {
      if (0xfffffff - (uVar6 >> 1) < uVar6) {
        uVar6 = 0;
      }
      else {
        uVar6 = uVar6 + (uVar6 >> 1);
      }
      if (uVar6 < uVar1) {
        uVar6 = uVar1;
      }
      pPVar4 = _Allocate<PathPoint>(uVar6,(PathPoint *)0x0);
      iVar3 = (int)param_1._Myptr - (int)this->_Myfirst >> 4;
      _Ufill(this,pPVar4 + iVar3,param_2,param_3);
      _Uninit_copy<PathPoint_*,PathPoint_*,std::allocator<PathPoint>_>
                (this->_Myfirst,param_1._Myptr,pPVar4,(allocator<PathPoint> *)&this->_padding_,
                 (_Nonscalar_ptr_iterator_tag)0x0,(_Range_checked_iterator_tag)0x0);
      _Uninit_copy<PathPoint_*,PathPoint_*,std::allocator<PathPoint>_>
                (param_1._Myptr,this->_Mylast,pPVar4 + param_2 + iVar3,
                 (allocator<PathPoint> *)&this->_padding_,(_Nonscalar_ptr_iterator_tag)0x0,
                 (_Range_checked_iterator_tag)0x0);
      pPVar5 = this->_Myfirst;
      pPVar2 = this->_Mylast;
      if (pPVar5 != (PathPoint *)0x0) {
        operator_delete(pPVar5);
      }
      this->_Myfirst = pPVar4;
      this->_Mylast = pPVar4 + param_2 + ((int)pPVar2 - (int)pPVar5 >> 4);
      this->_Myend = pPVar4 + uVar6;
      return;
    }
    local_10.point.x = (param_3->point).x;
    if ((uint)((int)pPVar2 - (int)param_1._Myptr >> 4) < param_2) {
      local_10.point.z = (param_3->point).z;
      local_10.strip = param_3->strip;
      local_10.seqNo = param_3->seqNo;
      _Umove<PathPoint_*>(this,param_1._Myptr,pPVar2,param_1._Myptr + param_2);
      _Ufill(this,this->_Mylast,param_2 - ((int)this->_Mylast - (int)param_1._Myptr >> 4),&local_10)
      ;
      this->_Mylast = this->_Mylast + param_2;
      fill<PathPoint_*,PathPoint>(param_1._Myptr,this->_Mylast + -param_2,&local_10);
      return;
    }
    local_10.point.z = (param_3->point).z;
    local_10.strip = param_3->strip;
    local_10.seqNo = param_3->seqNo;
    pPVar5 = _Umove<PathPoint_*>(this,pPVar2 + -param_2,pPVar2,pPVar2);
    this->_Mylast = pPVar5;
    stdext::_Unchecked_move_backward<PathPoint_*,PathPoint_*>
              (param_1._Myptr,pPVar2 + -param_2,pPVar2);
    fill<PathPoint_*,PathPoint>(param_1._Myptr,param_1._Myptr + param_2,&local_10);
  }
  return;
}
