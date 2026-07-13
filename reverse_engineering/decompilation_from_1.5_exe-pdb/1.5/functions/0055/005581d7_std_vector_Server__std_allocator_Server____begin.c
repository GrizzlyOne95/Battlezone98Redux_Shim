/*
 * Entry: 005581d7
 * Name: std::vector<Server_*,std::allocator<Server_*>_>::begin
 * Namespace: std::vector<Server_*,std::allocator<Server_*>_>
 * Signature: _Vector_iterator<Server_*,std::allocator<Server_*>_> begin(vector<Server_*,std::allocator<Server_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<Server_*,std::allocator<Server_*>_> __thiscall
std::vector<Server_*,std::allocator<Server_*>_>::begin
          (vector<Server_*,std::allocator<Server_*>_> *this)

{
  undefined4 extraout_EDX;
  _Vector_iterator<Server_*,std::allocator<Server_*>_> _Var1;
  _Vector_const_iterator<Server_*,std::allocator<Server_*>_> *in_stack_00000004;
  
  _Vector_const_iterator<Server_*,std::allocator<Server_*>_>::
  _Vector_const_iterator<Server_*,std::allocator<Server_*>_>
            (in_stack_00000004,this->_Myfirst,(_Container_base_aux *)this);
  _Var1._4_4_ = extraout_EDX;
  _Var1._0_4_ = in_stack_00000004;
  return _Var1;
}
