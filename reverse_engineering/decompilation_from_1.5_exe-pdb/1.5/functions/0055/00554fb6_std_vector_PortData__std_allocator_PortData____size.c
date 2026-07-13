/*
 * Entry: 00554fb6
 * Name: std::vector<PortData_*,std::allocator<PortData_*>_>::size
 * Namespace: std::vector<PortData_*,std::allocator<PortData_*>_>
 * Signature: uint size(vector<PortData_*,std::allocator<PortData_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uint __thiscall
std::vector<PortData_*,std::allocator<PortData_*>_>::size
          (vector<PortData_*,std::allocator<PortData_*>_> *this)

{
  return (int)this->_Mylast - (int)this->_Myfirst >> 2;
}
