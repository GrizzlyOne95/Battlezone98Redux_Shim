/*
 * Entry: 00409157
 * Name: std::vector<GameObject_*,std::allocator<GameObject_*>_>::begin
 * Namespace: std::vector<GameObject_*,std::allocator<GameObject_*>_>
 * Signature: _Vector_iterator<GameObject_*,std::allocator<GameObject_*>_> begin(vector<GameObject_*,std::allocator<GameObject_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<GameObject_*,std::allocator<GameObject_*>_> __thiscall
std::vector<GameObject_*,std::allocator<GameObject_*>_>::begin
          (vector<GameObject_*,std::allocator<GameObject_*>_> *this)

{
  undefined4 extraout_EDX;
  _Vector_iterator<GameObject_*,std::allocator<GameObject_*>_> _Var1;
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> *in_stack_00000004;
  
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
            (in_stack_00000004,this->_Myfirst,(_Container_base_aux *)this);
  _Var1._4_4_ = extraout_EDX;
  _Var1._0_4_ = in_stack_00000004;
  return _Var1;
}
