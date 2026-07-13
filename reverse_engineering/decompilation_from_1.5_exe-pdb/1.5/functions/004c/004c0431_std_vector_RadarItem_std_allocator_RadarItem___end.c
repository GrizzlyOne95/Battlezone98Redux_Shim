/*
 * Entry: 004c0431
 * Name: std::vector<RadarItem,std::allocator<RadarItem>_>::end
 * Namespace: std::vector<RadarItem,std::allocator<RadarItem>_>
 * Signature: _Vector_iterator<RadarItem,std::allocator<RadarItem>_> end(vector<RadarItem,std::allocator<RadarItem>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<RadarItem,std::allocator<RadarItem>_> __thiscall
std::vector<RadarItem,std::allocator<RadarItem>_>::end
          (vector<RadarItem,std::allocator<RadarItem>_> *this)

{
  undefined4 extraout_EDX;
  _Vector_iterator<RadarItem,std::allocator<RadarItem>_> _Var1;
  _Vector_const_iterator<RadarItem,std::allocator<RadarItem>_> *in_stack_00000004;
  
  _Vector_const_iterator<RadarItem,std::allocator<RadarItem>_>::
  _Vector_const_iterator<RadarItem,std::allocator<RadarItem>_>
            (in_stack_00000004,this->_Mylast,(_Container_base_aux *)this);
  _Var1._4_4_ = extraout_EDX;
  _Var1._0_4_ = in_stack_00000004;
  return _Var1;
}
