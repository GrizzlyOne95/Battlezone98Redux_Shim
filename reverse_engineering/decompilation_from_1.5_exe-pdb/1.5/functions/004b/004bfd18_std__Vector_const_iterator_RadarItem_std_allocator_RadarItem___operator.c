/*
 * Entry: 004bfd18
 * Name: std::_Vector_const_iterator<RadarItem,std::allocator<RadarItem>_>::operator*
 * Namespace: std::_Vector_const_iterator<RadarItem,std::allocator<RadarItem>_>
 * Signature: RadarItem * operator*(_Vector_const_iterator<RadarItem,std::allocator<RadarItem>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

RadarItem * __thiscall
std::_Vector_const_iterator<RadarItem,std::allocator<RadarItem>_>::operator*
          (_Vector_const_iterator<RadarItem,std::allocator<RadarItem>_> *this)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = (int *)this->_padding_;
  if (piVar1 == (int *)0x0) {
    _invalid_parameter_noinfo();
    piVar1 = (int *)this->_padding_;
    if (piVar1 == (int *)0x0) {
      iVar2 = 0;
      goto LAB_004bfd36;
    }
  }
  iVar2 = *piVar1;
LAB_004bfd36:
  if (*(RadarItem **)(iVar2 + 0x10) <= this->_Myptr) {
    _invalid_parameter_noinfo();
  }
  return this->_Myptr;
}
