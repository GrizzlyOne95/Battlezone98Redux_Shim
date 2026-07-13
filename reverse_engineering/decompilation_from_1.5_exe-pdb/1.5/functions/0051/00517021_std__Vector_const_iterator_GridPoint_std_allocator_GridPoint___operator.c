/*
 * Entry: 00517021
 * Name: std::_Vector_const_iterator<GridPoint,std::allocator<GridPoint>_>::operator*
 * Namespace: std::_Vector_const_iterator<GridPoint,std::allocator<GridPoint>_>
 * Signature: GridPoint * operator*(_Vector_const_iterator<GridPoint,std::allocator<GridPoint>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GridPoint * __thiscall
std::_Vector_const_iterator<GridPoint,std::allocator<GridPoint>_>::operator*
          (_Vector_const_iterator<GridPoint,std::allocator<GridPoint>_> *this)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = (int *)this->_padding_;
  if (piVar1 == (int *)0x0) {
    _invalid_parameter_noinfo();
    piVar1 = (int *)this->_padding_;
    if (piVar1 == (int *)0x0) {
      iVar2 = 0;
      goto LAB_0051703f;
    }
  }
  iVar2 = *piVar1;
LAB_0051703f:
  if (*(GridPoint **)(iVar2 + 0x10) <= this->_Myptr) {
    _invalid_parameter_noinfo();
  }
  return this->_Myptr;
}
