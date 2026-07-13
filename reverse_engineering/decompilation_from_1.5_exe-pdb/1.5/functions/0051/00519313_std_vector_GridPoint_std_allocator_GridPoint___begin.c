/*
 * Entry: 00519313
 * Name: std::vector<GridPoint,std::allocator<GridPoint>_>::begin
 * Namespace: std::vector<GridPoint,std::allocator<GridPoint>_>
 * Signature: _Vector_iterator<GridPoint,std::allocator<GridPoint>_> begin(vector<GridPoint,std::allocator<GridPoint>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<GridPoint,std::allocator<GridPoint>_> __thiscall
std::vector<GridPoint,std::allocator<GridPoint>_>::begin
          (vector<GridPoint,std::allocator<GridPoint>_> *this)

{
  undefined4 extraout_EDX;
  _Vector_iterator<GridPoint,std::allocator<GridPoint>_> _Var1;
  _Vector_const_iterator<GridPoint,std::allocator<GridPoint>_> *in_stack_00000004;
  
  _Vector_const_iterator<GridPoint,std::allocator<GridPoint>_>::
  _Vector_const_iterator<GridPoint,std::allocator<GridPoint>_>
            (in_stack_00000004,this->_Myfirst,(_Container_base_aux *)this);
  _Var1._4_4_ = extraout_EDX;
  _Var1._0_4_ = in_stack_00000004;
  return _Var1;
}
