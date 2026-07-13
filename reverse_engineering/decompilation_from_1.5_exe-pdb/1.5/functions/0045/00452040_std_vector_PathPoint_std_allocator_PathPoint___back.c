/*
 * Entry: 00452040
 * Name: std::vector<PathPoint,std::allocator<PathPoint>_>::back
 * Namespace: std::vector<PathPoint,std::allocator<PathPoint>_>
 * Signature: PathPoint * back(vector<PathPoint,std::allocator<PathPoint>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

PathPoint * __thiscall
std::vector<PathPoint,std::allocator<PathPoint>_>::back
          (vector<PathPoint,std::allocator<PathPoint>_> *this)

{
  PathPoint *pPVar1;
  int *piVar2;
  int iVar3;
  
  pPVar1 = this->_Mylast;
  if (pPVar1 < this->_Myfirst) {
    _invalid_parameter_noinfo();
  }
  piVar2 = (int *)this->_padding_;
  if (piVar2 == (int *)0x0) {
    _invalid_parameter_noinfo();
    iVar3 = 0;
  }
  else {
    iVar3 = *piVar2;
  }
  if (pPVar1 + -1 <= *(PathPoint **)(iVar3 + 0x10)) {
    if (piVar2 == (int *)0x0) {
      iVar3 = 0;
    }
    else {
      iVar3 = *piVar2;
    }
    if (*(PathPoint **)(iVar3 + 0xc) <= pPVar1 + -1) goto LAB_00452086;
  }
  _invalid_parameter_noinfo();
LAB_00452086:
  if (piVar2 == (int *)0x0) {
    _invalid_parameter_noinfo();
    iVar3 = 0;
  }
  else {
    iVar3 = *piVar2;
  }
  if (*(PathPoint **)(iVar3 + 0x10) <= pPVar1 + -1) {
    _invalid_parameter_noinfo();
  }
  return pPVar1 + -1;
}
