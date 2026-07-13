/*
 * Entry: 004089c0
 * Name: std::_Vector_iterator<PathPoint,std::allocator<PathPoint>_>::operator*
 * Namespace: std::_Vector_iterator<PathPoint,std::allocator<PathPoint>_>
 * Signature: PathPoint * operator*(_Vector_iterator<PathPoint,std::allocator<PathPoint>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

PathPoint * __thiscall
std::_Vector_iterator<PathPoint,std::allocator<PathPoint>_>::operator*
          (_Vector_iterator<PathPoint,std::allocator<PathPoint>_> *this)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = *(int **)this;
  if (piVar1 == (int *)0x0) {
    _invalid_parameter_noinfo();
    piVar1 = *(int **)this;
    if (piVar1 == (int *)0x0) {
      iVar2 = 0;
      goto LAB_00405abd;
    }
  }
  iVar2 = *piVar1;
LAB_00405abd:
  if (*(uint *)(iVar2 + 0x10) <= *(uint *)&this->field_0x4) {
    _invalid_parameter_noinfo();
  }
  return *(PathPoint **)&this->field_0x4;
}
