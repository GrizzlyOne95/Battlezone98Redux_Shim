/*
 * Entry: 00554fcf
 * Name: std::vector<Server_*,std::allocator<Server_*>_>::capacity
 * Namespace: std::vector<Server_*,std::allocator<Server_*>_>
 * Signature: uint capacity(vector<Server_*,std::allocator<Server_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uint __thiscall
std::vector<Server_*,std::allocator<Server_*>_>::capacity
          (vector<Server_*,std::allocator<Server_*>_> *this)

{
  if (this->_Myfirst == (Server **)0x0) {
    return 0;
  }
  return (int)this->_Myend - (int)this->_Myfirst >> 2;
}
