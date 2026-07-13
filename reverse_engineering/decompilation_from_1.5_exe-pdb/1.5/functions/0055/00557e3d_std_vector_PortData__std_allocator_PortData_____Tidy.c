/*
 * Entry: 00557e3d
 * Name: std::vector<PortData_*,std::allocator<PortData_*>_>::_Tidy
 * Namespace: std::vector<PortData_*,std::allocator<PortData_*>_>
 * Signature: void _Tidy(vector<PortData_*,std::allocator<PortData_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::vector<PortData_*,std::allocator<PortData_*>_>::_Tidy
          (vector<PortData_*,std::allocator<PortData_*>_> *this)

{
  if (this->_Myfirst != (PortData **)0x0) {
    operator_delete(this->_Myfirst);
  }
  this->_Myfirst = (PortData **)0x0;
  this->_Mylast = (PortData **)0x0;
  this->_Myend = (PortData **)0x0;
  return;
}
