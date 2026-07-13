/*
 * Entry: 005550ca
 * Name: std::vector<PortData_*,std::allocator<PortData_*>_>::capacity
 * Namespace: std::vector<PortData_*,std::allocator<PortData_*>_>
 * Signature: uint capacity(vector<PortData_*,std::allocator<PortData_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uint __thiscall
std::vector<PortData_*,std::allocator<PortData_*>_>::capacity
          (vector<PortData_*,std::allocator<PortData_*>_> *this)

{
  if (this->_Myfirst == (PortData **)0x0) {
    return 0;
  }
  return (int)this->_Myend - (int)this->_Myfirst >> 2;
}
