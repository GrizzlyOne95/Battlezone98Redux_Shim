/*
 * Entry: 0055765b
 * Name: std::vector<Server_*,std::allocator<Server_*>_>::empty
 * Namespace: std::vector<Server_*,std::allocator<Server_*>_>
 * Signature: bool empty(vector<Server_*,std::allocator<Server_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall
std::vector<Server_*,std::allocator<Server_*>_>::empty
          (vector<Server_*,std::allocator<Server_*>_> *this)

{
  return (bool)('\x01' - (((int)this->_Mylast - (int)this->_Myfirst & 0xfffffffcU) != 0));
}
