/*
 * Entry: 004996ee
 * Name: std::_Vector_iterator<GameObjectClass_*,std::allocator<GameObjectClass_*>_>::operator+
 * Namespace: std::_Vector_iterator<GameObjectClass_*,std::allocator<GameObjectClass_*>_>
 * Signature: _Vector_iterator<GameObjectClass_*,std::allocator<GameObjectClass_*>_> operator+(_Vector_iterator<GameObjectClass_*,std::allocator<GameObjectClass_*>_> * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<GameObjectClass_*,std::allocator<GameObjectClass_*>_> __thiscall
std::_Vector_iterator<GameObjectClass_*,std::allocator<GameObjectClass_*>_>::operator+
          (_Vector_iterator<GameObjectClass_*,std::allocator<GameObjectClass_*>_> *this,int param_1)

{
  undefined4 extraout_EDX;
  _Vector_iterator<GameObjectClass_*,std::allocator<GameObjectClass_*>_> _Var1;
  int in_stack_00000008;
  _Vector_const_iterator<GameObjectClass_*,std::allocator<GameObjectClass_*>_> local_c;
  
  local_c._padding_ = *(int *)this;
  local_c._Myptr = *(GameObjectClass ***)&this->field_0x4;
  _Vector_const_iterator<GameObjectClass_*,std::allocator<GameObjectClass_*>_>::operator+=
            (&local_c,in_stack_00000008);
  *(int *)param_1 = local_c._padding_;
  *(GameObjectClass ***)(param_1 + 4) = local_c._Myptr;
  _Var1._4_4_ = extraout_EDX;
  _Var1._0_4_ = param_1;
  return _Var1;
}
