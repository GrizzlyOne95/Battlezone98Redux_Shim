/*
 * Entry: 005576bd
 * Name: std::_Vector_val<PortData_*,std::allocator<PortData_*>_>::~_Vector_val<PortData_*,std::allocator<PortData_*>_>
 * Namespace: std::_Vector_val<PortData_*,std::allocator<PortData_*>_>
 * Signature: void ~_Vector_val<PortData_*,std::allocator<PortData_*>_>(_Vector_val<PortData_*,std::allocator<PortData_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::_Vector_val<PortData_*,std::allocator<PortData_*>_>::
~_Vector_val<PortData_*,std::allocator<PortData_*>_>
          (_Vector_val<PortData_*,std::allocator<PortData_*>_> *this)

{
  operator_delete((void *)this->_padding_);
  return;
}
