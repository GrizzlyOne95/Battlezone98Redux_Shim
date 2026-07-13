/*
 * Entry: 004552a0
 * Name: std::vector<PathPoint,std::allocator<PathPoint>_>::push_back
 * Namespace: std::vector<PathPoint,std::allocator<PathPoint>_>
 * Signature: void push_back(vector<PathPoint,std::allocator<PathPoint>_> * this, PathPoint * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::vector<PathPoint,std::allocator<PathPoint>_>::push_back
          (vector<PathPoint,std::allocator<PathPoint>_> *this,PathPoint *param_1)

{
  PathPoint *pPVar1;
  PathPoint *pPVar2;
  _Vector_const_iterator<PathPoint,std::allocator<PathPoint>_> _Var3;
  uint uVar4;
  undefined1 local_8 [8];
  
  pPVar1 = this->_Myfirst;
  if (pPVar1 == (PathPoint *)0x0) {
    uVar4 = 0;
  }
  else {
    uVar4 = (int)this->_Myend - (int)pPVar1 >> 4;
  }
  pPVar2 = this->_Mylast;
  if ((uint)((int)pPVar2 - (int)pPVar1 >> 4) < uVar4) {
    if (pPVar2 != (PathPoint *)0x0) {
      (pPVar2->point).x = (param_1->point).x;
      (pPVar2->point).z = (param_1->point).z;
      pPVar2->strip = param_1->strip;
      pPVar2->seqNo = param_1->seqNo;
    }
    this->_Mylast = pPVar2 + 1;
    return;
  }
  if (pPVar2 < pPVar1) {
    _invalid_parameter_noinfo();
  }
  _Var3._Myptr = (PathPoint *)this->_padding_;
  _Var3._padding_ = (int)local_8;
  insert(this,_Var3,pPVar2);
  return;
}
