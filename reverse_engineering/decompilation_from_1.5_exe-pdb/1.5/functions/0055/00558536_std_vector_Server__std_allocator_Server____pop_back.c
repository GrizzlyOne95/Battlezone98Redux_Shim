/*
 * Entry: 00558536
 * Name: std::vector<Server_*,std::allocator<Server_*>_>::pop_back
 * Namespace: std::vector<Server_*,std::allocator<Server_*>_>
 * Signature: void pop_back(vector<Server_*,std::allocator<Server_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::vector<Server_*,std::allocator<Server_*>_>::pop_back
          (vector<Server_*,std::allocator<Server_*>_> *this)

{
  if (((int)this->_Mylast - (int)this->_Myfirst & 0xfffffffcU) != 0) {
    this->_Mylast = this->_Mylast + -1;
  }
  return;
}
