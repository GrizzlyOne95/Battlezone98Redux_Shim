/*
 * Entry: 00493dc5
 * Name: std::vector<GameFeature_*,std::allocator<GameFeature_*>_>::end
 * Namespace: std::vector<GameFeature_*,std::allocator<GameFeature_*>_>
 * Signature: _Vector_iterator<GameFeature_*,std::allocator<GameFeature_*>_> end(vector<GameFeature_*,std::allocator<GameFeature_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<GameFeature_*,std::allocator<GameFeature_*>_> __thiscall
std::vector<GameFeature_*,std::allocator<GameFeature_*>_>::end
          (vector<GameFeature_*,std::allocator<GameFeature_*>_> *this)

{
  undefined4 extraout_EDX;
  _Vector_iterator<GameFeature_*,std::allocator<GameFeature_*>_> _Var1;
  _Vector_const_iterator<GameFeature_*,std::allocator<GameFeature_*>_> *in_stack_00000004;
  
  _Vector_const_iterator<GameFeature_*,std::allocator<GameFeature_*>_>::
  _Vector_const_iterator<GameFeature_*,std::allocator<GameFeature_*>_>
            (in_stack_00000004,this->_Mylast,(_Container_base_aux *)this);
  _Var1._4_4_ = extraout_EDX;
  _Var1._0_4_ = in_stack_00000004;
  return _Var1;
}
