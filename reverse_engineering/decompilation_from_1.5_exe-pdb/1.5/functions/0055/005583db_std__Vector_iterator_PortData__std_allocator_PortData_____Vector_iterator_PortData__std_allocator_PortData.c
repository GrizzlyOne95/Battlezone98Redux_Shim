/*
 * Entry: 005583db
 * Name: std::_Vector_iterator<PortData_*,std::allocator<PortData_*>_>::_Vector_iterator<PortData_*,std::allocator<PortData_*>_>
 * Namespace: std::_Vector_iterator<PortData_*,std::allocator<PortData_*>_>
 * Signature: _Vector_iterator<PortData_*,std::allocator<PortData_*>_> * _Vector_iterator<PortData_*,std::allocator<PortData_*>_>(_Vector_iterator<PortData_*,std::allocator<PortData_*>_> * this, PortData * * param_1, _Container_base_aux * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<PortData_*,std::allocator<PortData_*>_> * __thiscall
std::_Vector_iterator<PortData_*,std::allocator<PortData_*>_>::
_Vector_iterator<PortData_*,std::allocator<PortData_*>_>
          (_Vector_iterator<PortData_*,std::allocator<PortData_*>_> *this,PortData **param_1,
          _Container_base_aux *param_2)

{
  _Vector_const_iterator<PortData_*,std::allocator<PortData_*>_>::
  _Vector_const_iterator<PortData_*,std::allocator<PortData_*>_>
            ((_Vector_const_iterator<PortData_*,std::allocator<PortData_*>_> *)this,param_1,param_2)
  ;
  return this;
}
