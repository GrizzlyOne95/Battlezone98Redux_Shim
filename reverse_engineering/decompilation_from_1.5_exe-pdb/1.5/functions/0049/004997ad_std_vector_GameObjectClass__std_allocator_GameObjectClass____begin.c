/*
 * Entry: 004997ad
 * Name: std::vector<GameObjectClass_*,std::allocator<GameObjectClass_*>_>::begin
 * Namespace: std::vector<GameObjectClass_*,std::allocator<GameObjectClass_*>_>
 * Signature: _Vector_iterator<GameObjectClass_*,std::allocator<GameObjectClass_*>_> begin(vector<GameObjectClass_*,std::allocator<GameObjectClass_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<GameObjectClass_*,std::allocator<GameObjectClass_*>_> __thiscall
std::vector<GameObjectClass_*,std::allocator<GameObjectClass_*>_>::begin
          (vector<GameObjectClass_*,std::allocator<GameObjectClass_*>_> *this)

{
  undefined4 extraout_EDX;
  _Vector_iterator<GameObjectClass_*,std::allocator<GameObjectClass_*>_> _Var1;
  _Vector_const_iterator<GameObjectClass_*,std::allocator<GameObjectClass_*>_> *in_stack_00000004;
  
  _Vector_const_iterator<GameObjectClass_*,std::allocator<GameObjectClass_*>_>::
  _Vector_const_iterator<GameObjectClass_*,std::allocator<GameObjectClass_*>_>
            (in_stack_00000004,this->_Myfirst,(_Container_base_aux *)this);
  _Var1._4_4_ = extraout_EDX;
  _Var1._0_4_ = in_stack_00000004;
  return _Var1;
}
