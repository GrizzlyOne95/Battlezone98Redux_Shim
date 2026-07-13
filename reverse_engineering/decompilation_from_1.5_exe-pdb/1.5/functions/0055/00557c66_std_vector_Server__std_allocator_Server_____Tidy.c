/*
 * Entry: 00557c66
 * Name: std::vector<Server_*,std::allocator<Server_*>_>::_Tidy
 * Namespace: std::vector<Server_*,std::allocator<Server_*>_>
 * Signature: void _Tidy(vector<Server_*,std::allocator<Server_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::vector<Server_*,std::allocator<Server_*>_>::_Tidy
          (vector<Server_*,std::allocator<Server_*>_> *this)

{
  if (this->_Myfirst != (Server **)0x0) {
    operator_delete(this->_Myfirst);
  }
  this->_Myfirst = (Server **)0x0;
  this->_Mylast = (Server **)0x0;
  this->_Myend = (Server **)0x0;
  return;
}
