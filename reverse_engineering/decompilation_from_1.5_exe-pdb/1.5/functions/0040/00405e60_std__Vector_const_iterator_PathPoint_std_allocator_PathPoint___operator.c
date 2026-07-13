/*
 * Entry: 00405e60
 * Name: std::_Vector_const_iterator<PathPoint,std::allocator<PathPoint>_>::operator++
 * Namespace: std::_Vector_const_iterator<PathPoint,std::allocator<PathPoint>_>
 * Signature: _Vector_const_iterator<PathPoint,std::allocator<PathPoint>_> * operator++(_Vector_const_iterator<PathPoint,std::allocator<PathPoint>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_const_iterator<PathPoint,std::allocator<PathPoint>_> * __thiscall
std::_Vector_const_iterator<PathPoint,std::allocator<PathPoint>_>::operator++
          (_Vector_const_iterator<PathPoint,std::allocator<PathPoint>_> *this)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = (int *)this->_padding_;
  if (piVar1 == (int *)0x0) {
    _invalid_parameter_noinfo();
    piVar1 = (int *)this->_padding_;
    if (piVar1 == (int *)0x0) {
      iVar2 = 0;
      goto LAB_00405e7e;
    }
  }
  iVar2 = *piVar1;
LAB_00405e7e:
  if (*(PathPoint **)(iVar2 + 0x10) <= this->_Myptr) {
    _invalid_parameter_noinfo();
  }
  this->_Myptr = this->_Myptr + 1;
  return this;
}
