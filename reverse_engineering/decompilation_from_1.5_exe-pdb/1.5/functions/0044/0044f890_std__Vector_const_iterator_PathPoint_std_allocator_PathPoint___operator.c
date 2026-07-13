/*
 * Entry: 0044f890
 * Name: std::_Vector_const_iterator<PathPoint,std::allocator<PathPoint>_>::operator+=
 * Namespace: std::_Vector_const_iterator<PathPoint,std::allocator<PathPoint>_>
 * Signature: _Vector_const_iterator<PathPoint,std::allocator<PathPoint>_> * operator+=(_Vector_const_iterator<PathPoint,std::allocator<PathPoint>_> * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_const_iterator<PathPoint,std::allocator<PathPoint>_> * __thiscall
std::_Vector_const_iterator<PathPoint,std::allocator<PathPoint>_>::operator+=
          (_Vector_const_iterator<PathPoint,std::allocator<PathPoint>_> *this,int param_1)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = (int *)this->_padding_;
  if (piVar1 == (int *)0x0) {
    _invalid_parameter_noinfo();
    piVar1 = (int *)this->_padding_;
    if (piVar1 != (int *)0x0) goto LAB_0044f8a9;
    iVar2 = 0;
  }
  else {
LAB_0044f8a9:
    iVar2 = *piVar1;
  }
  if (this->_Myptr + param_1 <= *(PathPoint **)(iVar2 + 0x10)) {
    if (piVar1 == (int *)0x0) {
      iVar2 = 0;
    }
    else {
      iVar2 = *piVar1;
    }
    if (*(PathPoint **)(iVar2 + 0xc) <= this->_Myptr + param_1) goto LAB_0044f8d1;
  }
  _invalid_parameter_noinfo();
LAB_0044f8d1:
  this->_Myptr = this->_Myptr + param_1;
  return this;
}
