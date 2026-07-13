/*
 * Entry: 0055ac15
 * Name: std::vector<PortData_*,std::allocator<PortData_*>_>::end
 * Namespace: std::vector<PortData_*,std::allocator<PortData_*>_>
 * Signature: _Vector_iterator<PortData_*,std::allocator<PortData_*>_> end(vector<PortData_*,std::allocator<PortData_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<PortData_*,std::allocator<PortData_*>_> __thiscall
std::vector<PortData_*,std::allocator<PortData_*>_>::end
          (vector<PortData_*,std::allocator<PortData_*>_> *this)

{
  undefined4 extraout_EDX;
  _Vector_iterator<PortData_*,std::allocator<PortData_*>_> _Var1;
  _Vector_const_iterator<PortData_*,std::allocator<PortData_*>_> *in_stack_00000004;
  
  _Vector_const_iterator<PortData_*,std::allocator<PortData_*>_>::
  _Vector_const_iterator<PortData_*,std::allocator<PortData_*>_>
            (in_stack_00000004,this->_Mylast,(_Container_base_aux *)this);
  _Var1._4_4_ = extraout_EDX;
  _Var1._0_4_ = in_stack_00000004;
  return _Var1;
}
