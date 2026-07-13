/*
 * Entry: 00408c89
 * Name: std::_Vector_iterator<PathPoint,std::allocator<PathPoint>_>::operator++
 * Namespace: std::_Vector_iterator<PathPoint,std::allocator<PathPoint>_>
 * Signature: _Vector_iterator<PathPoint,std::allocator<PathPoint>_> operator++(_Vector_iterator<PathPoint,std::allocator<PathPoint>_> * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<PathPoint,std::allocator<PathPoint>_> __thiscall
std::_Vector_iterator<PathPoint,std::allocator<PathPoint>_>::operator++
          (_Vector_iterator<PathPoint,std::allocator<PathPoint>_> *this,int param_1)

{
  undefined4 extraout_EDX;
  _Vector_iterator<PathPoint,std::allocator<PathPoint>_> _Var1;
  
  *(undefined4 *)param_1 = *(undefined4 *)this;
  *(undefined4 *)(param_1 + 4) = *(undefined4 *)&this->field_0x4;
  _Vector_const_iterator<PathPoint,std::allocator<PathPoint>_>::operator++
            ((_Vector_const_iterator<PathPoint,std::allocator<PathPoint>_> *)this);
  _Var1._4_4_ = extraout_EDX;
  _Var1._0_4_ = param_1;
  return _Var1;
}
