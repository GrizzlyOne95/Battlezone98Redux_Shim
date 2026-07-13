/*
 * Entry: 00554fc0
 * Name: std::vector<PortData_*,std::allocator<PortData_*>_>::empty
 * Namespace: std::vector<PortData_*,std::allocator<PortData_*>_>
 * Signature: bool empty(vector<PortData_*,std::allocator<PortData_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall
std::vector<PortData_*,std::allocator<PortData_*>_>::empty
          (vector<PortData_*,std::allocator<PortData_*>_> *this)

{
  return (bool)('\x01' - (((int)this->_Mylast - (int)this->_Myfirst & 0xfffffffcU) != 0));
}
