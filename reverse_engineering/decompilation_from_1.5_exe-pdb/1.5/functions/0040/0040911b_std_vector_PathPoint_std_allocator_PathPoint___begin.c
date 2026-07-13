/*
 * Entry: 0040911b
 * Name: std::vector<PathPoint,std::allocator<PathPoint>_>::begin
 * Namespace: std::vector<PathPoint,std::allocator<PathPoint>_>
 * Signature: _Vector_iterator<PathPoint,std::allocator<PathPoint>_> begin(vector<PathPoint,std::allocator<PathPoint>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<PathPoint,std::allocator<PathPoint>_> __thiscall
std::vector<PathPoint,std::allocator<PathPoint>_>::begin
          (vector<PathPoint,std::allocator<PathPoint>_> *this)

{
  undefined4 extraout_EDX;
  _Vector_iterator<PathPoint,std::allocator<PathPoint>_> _Var1;
  _Vector_const_iterator<PathPoint,std::allocator<PathPoint>_> *in_stack_00000004;
  
  _Vector_const_iterator<PathPoint,std::allocator<PathPoint>_>::
  _Vector_const_iterator<PathPoint,std::allocator<PathPoint>_>
            (in_stack_00000004,this->_Myfirst,(_Container_base_aux *)this);
  _Var1._4_4_ = extraout_EDX;
  _Var1._0_4_ = in_stack_00000004;
  return _Var1;
}
