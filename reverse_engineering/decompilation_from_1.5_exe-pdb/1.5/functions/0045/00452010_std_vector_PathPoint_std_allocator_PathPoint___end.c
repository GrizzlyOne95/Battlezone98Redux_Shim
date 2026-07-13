/*
 * Entry: 00452010
 * Name: std::vector<PathPoint,std::allocator<PathPoint>_>::end
 * Namespace: std::vector<PathPoint,std::allocator<PathPoint>_>
 * Signature: _Vector_iterator<PathPoint,std::allocator<PathPoint>_> end(vector<PathPoint,std::allocator<PathPoint>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<PathPoint,std::allocator<PathPoint>_> __thiscall
std::vector<PathPoint,std::allocator<PathPoint>_>::end
          (vector<PathPoint,std::allocator<PathPoint>_> *this)

{
  PathPoint *pPVar1;
  undefined4 in_EDX;
  undefined4 extraout_EDX;
  _Vector_iterator<PathPoint,std::allocator<PathPoint>_> _Var2;
  int *in_stack_00000004;
  
  pPVar1 = this->_Mylast;
  *in_stack_00000004 = 0;
  if (pPVar1 < this->_Myfirst) {
    _invalid_parameter_noinfo();
    in_EDX = extraout_EDX;
  }
  *in_stack_00000004 = this->_padding_;
  in_stack_00000004[1] = (int)pPVar1;
  _Var2._4_4_ = in_EDX;
  _Var2._0_4_ = in_stack_00000004;
  return _Var2;
}
