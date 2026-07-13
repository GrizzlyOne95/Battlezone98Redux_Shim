/*
 * Entry: 004529d0
 * Name: std::vector<PathPoint,std::allocator<PathPoint>_>::clear
 * Namespace: std::vector<PathPoint,std::allocator<PathPoint>_>
 * Signature: void clear(vector<PathPoint,std::allocator<PathPoint>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::vector<PathPoint,std::allocator<PathPoint>_>::clear
          (vector<PathPoint,std::allocator<PathPoint>_> *this)

{
  PathPoint *pPVar1;
  PathPoint *pPVar2;
  _Vector_const_iterator<PathPoint,std::allocator<PathPoint>_> _Var3;
  _Vector_const_iterator<PathPoint,std::allocator<PathPoint>_> _Var4;
  undefined1 local_8 [8];
  
  if (this->_Mylast < this->_Myfirst) {
    _invalid_parameter_noinfo();
  }
  pPVar1 = this->_Myfirst;
  pPVar2 = (PathPoint *)this->_padding_;
  if (this->_Mylast < pPVar1) {
    _invalid_parameter_noinfo();
  }
  _Var3._Myptr = (PathPoint *)this->_padding_;
  _Var3._padding_ = (int)local_8;
  _Var4._Myptr = pPVar2;
  _Var4._padding_ = (int)pPVar1;
  erase(this,_Var3,_Var4);
  return;
}
