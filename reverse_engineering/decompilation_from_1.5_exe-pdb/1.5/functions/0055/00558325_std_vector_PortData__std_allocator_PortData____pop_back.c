/*
 * Entry: 00558325
 * Name: std::vector<PortData_*,std::allocator<PortData_*>_>::pop_back
 * Namespace: std::vector<PortData_*,std::allocator<PortData_*>_>
 * Signature: void pop_back(vector<PortData_*,std::allocator<PortData_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::vector<PortData_*,std::allocator<PortData_*>_>::pop_back
          (vector<PortData_*,std::allocator<PortData_*>_> *this)

{
  if (((int)this->_Mylast - (int)this->_Myfirst & 0xfffffffcU) != 0) {
    this->_Mylast = this->_Mylast + -1;
  }
  return;
}
