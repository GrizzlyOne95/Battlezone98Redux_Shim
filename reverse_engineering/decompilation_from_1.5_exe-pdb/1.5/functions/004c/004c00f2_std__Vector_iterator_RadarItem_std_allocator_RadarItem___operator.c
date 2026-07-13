/*
 * Entry: 004c00f2
 * Name: std::_Vector_iterator<RadarItem,std::allocator<RadarItem>_>::operator++
 * Namespace: std::_Vector_iterator<RadarItem,std::allocator<RadarItem>_>
 * Signature: _Vector_iterator<RadarItem,std::allocator<RadarItem>_> operator++(_Vector_iterator<RadarItem,std::allocator<RadarItem>_> * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<RadarItem,std::allocator<RadarItem>_> __thiscall
std::_Vector_iterator<RadarItem,std::allocator<RadarItem>_>::operator++
          (_Vector_iterator<RadarItem,std::allocator<RadarItem>_> *this,int param_1)

{
  undefined4 extraout_EDX;
  _Vector_iterator<RadarItem,std::allocator<RadarItem>_> _Var1;
  
  *(undefined4 *)param_1 = *(undefined4 *)this;
  *(undefined4 *)(param_1 + 4) = *(undefined4 *)&this->field_0x4;
  _Vector_const_iterator<RadarItem,std::allocator<RadarItem>_>::operator++
            ((_Vector_const_iterator<RadarItem,std::allocator<RadarItem>_> *)this);
  _Var1._4_4_ = extraout_EDX;
  _Var1._0_4_ = param_1;
  return _Var1;
}
