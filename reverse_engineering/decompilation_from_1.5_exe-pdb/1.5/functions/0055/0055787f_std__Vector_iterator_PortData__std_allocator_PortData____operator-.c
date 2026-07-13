/*
 * Entry: 0055787f
 * Name: std::_Vector_iterator<PortData_*,std::allocator<PortData_*>_>::operator-=
 * Namespace: std::_Vector_iterator<PortData_*,std::allocator<PortData_*>_>
 * Signature: _Vector_iterator<PortData_*,std::allocator<PortData_*>_> * operator-=(_Vector_iterator<PortData_*,std::allocator<PortData_*>_> * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<PortData_*,std::allocator<PortData_*>_> * __thiscall
std::_Vector_iterator<PortData_*,std::allocator<PortData_*>_>::operator-=
          (_Vector_iterator<PortData_*,std::allocator<PortData_*>_> *this,int param_1)

{
  _Vector_const_iterator<PortData_*,std::allocator<PortData_*>_>::operator+=
            ((_Vector_const_iterator<PortData_*,std::allocator<PortData_*>_> *)this,-param_1);
  return this;
}
