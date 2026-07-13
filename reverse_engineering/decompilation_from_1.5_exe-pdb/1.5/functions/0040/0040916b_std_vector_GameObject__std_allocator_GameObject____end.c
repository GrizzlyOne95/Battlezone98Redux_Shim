/*
 * Entry: 0040916b
 * Name: std::vector<GameObject_*,std::allocator<GameObject_*>_>::end
 * Namespace: std::vector<GameObject_*,std::allocator<GameObject_*>_>
 * Signature: _Vector_iterator<GameObject_*,std::allocator<GameObject_*>_> end(vector<GameObject_*,std::allocator<GameObject_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<GameObject_*,std::allocator<GameObject_*>_> __thiscall
std::vector<GameObject_*,std::allocator<GameObject_*>_>::end
          (vector<GameObject_*,std::allocator<GameObject_*>_> *this)

{
  undefined4 extraout_EDX;
  _Vector_iterator<GameObject_*,std::allocator<GameObject_*>_> _Var1;
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> *in_stack_00000004;
  
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
            (in_stack_00000004,this->_Mylast,(_Container_base_aux *)this);
  _Var1._4_4_ = extraout_EDX;
  _Var1._0_4_ = in_stack_00000004;
  return _Var1;
}
