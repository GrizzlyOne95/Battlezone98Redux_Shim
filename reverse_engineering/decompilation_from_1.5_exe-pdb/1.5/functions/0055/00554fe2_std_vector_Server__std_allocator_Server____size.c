/*
 * Entry: 00554fe2
 * Name: std::vector<Server_*,std::allocator<Server_*>_>::size
 * Namespace: std::vector<Server_*,std::allocator<Server_*>_>
 * Signature: uint size(vector<Server_*,std::allocator<Server_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uint __thiscall
std::vector<Server_*,std::allocator<Server_*>_>::size
          (vector<Server_*,std::allocator<Server_*>_> *this)

{
  return (int)this->_Mylast - (int)this->_Myfirst >> 2;
}
