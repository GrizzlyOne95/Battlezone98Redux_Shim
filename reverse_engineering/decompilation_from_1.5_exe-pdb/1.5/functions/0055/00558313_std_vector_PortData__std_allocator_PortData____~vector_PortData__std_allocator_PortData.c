/*
 * Entry: 00558313
 * Name: std::vector<PortData_*,std::allocator<PortData_*>_>::~vector<PortData_*,std::allocator<PortData_*>_>
 * Namespace: std::vector<PortData_*,std::allocator<PortData_*>_>
 * Signature: void ~vector<PortData_*,std::allocator<PortData_*>_>(vector<PortData_*,std::allocator<PortData_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::vector<PortData_*,std::allocator<PortData_*>_>::~vector<PortData_*,std::allocator<PortData_*>_>
          (vector<PortData_*,std::allocator<PortData_*>_> *this)

{
  _Tidy(this);
  operator_delete((void *)this->_padding_);
  return;
}
