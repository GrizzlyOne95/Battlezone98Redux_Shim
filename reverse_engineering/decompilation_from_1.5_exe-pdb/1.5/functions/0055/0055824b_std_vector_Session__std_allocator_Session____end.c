/*
 * Entry: 0055824b
 * Name: std::vector<Session_*,std::allocator<Session_*>_>::end
 * Namespace: std::vector<Session_*,std::allocator<Session_*>_>
 * Signature: _Vector_iterator<Session_*,std::allocator<Session_*>_> end(vector<Session_*,std::allocator<Session_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<Session_*,std::allocator<Session_*>_> __thiscall
std::vector<Session_*,std::allocator<Session_*>_>::end
          (vector<Session_*,std::allocator<Session_*>_> *this)

{
  undefined4 extraout_EDX;
  _Vector_iterator<Session_*,std::allocator<Session_*>_> _Var1;
  _Vector_const_iterator<Session_*,std::allocator<Session_*>_> *in_stack_00000004;
  
  _Vector_const_iterator<Session_*,std::allocator<Session_*>_>::
  _Vector_const_iterator<Session_*,std::allocator<Session_*>_>
            (in_stack_00000004,this->_Mylast,(_Container_base_aux *)this);
  _Var1._4_4_ = extraout_EDX;
  _Var1._0_4_ = in_stack_00000004;
  return _Var1;
}
