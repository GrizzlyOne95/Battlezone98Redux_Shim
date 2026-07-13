/*
 * Entry: 00450720
 * Name: std::_Vector_iterator<Strip_*,std::allocator<Strip_*>_>::operator++
 * Namespace: std::_Vector_iterator<Strip_*,std::allocator<Strip_*>_>
 * Signature: _Vector_iterator<Strip_*,std::allocator<Strip_*>_> * operator++(_Vector_iterator<Strip_*,std::allocator<Strip_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<Strip_*,std::allocator<Strip_*>_> * __thiscall
std::_Vector_iterator<Strip_*,std::allocator<Strip_*>_>::operator++
          (_Vector_iterator<Strip_*,std::allocator<Strip_*>_> *this)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = *(int **)this;
  if (piVar1 == (int *)0x0) {
    _invalid_parameter_noinfo();
    piVar1 = *(int **)this;
    if (piVar1 == (int *)0x0) {
      iVar2 = 0;
      goto LAB_0045073e;
    }
  }
  iVar2 = *piVar1;
LAB_0045073e:
  if (*(uint *)(iVar2 + 0x10) <= *(uint *)&this->field_0x4) {
    _invalid_parameter_noinfo();
  }
  *(int *)&this->field_0x4 = *(int *)&this->field_0x4 + 4;
  return this;
}
