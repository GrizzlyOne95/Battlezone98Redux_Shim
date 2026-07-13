/*
 * Entry: 0055766f
 * Name: std::vector<Session_*,std::allocator<Session_*>_>::empty
 * Namespace: std::vector<Session_*,std::allocator<Session_*>_>
 * Signature: bool empty(vector<Session_*,std::allocator<Session_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall
std::vector<Session_*,std::allocator<Session_*>_>::empty
          (vector<Session_*,std::allocator<Session_*>_> *this)

{
  return (bool)('\x01' - (((int)this->_Mylast - (int)this->_Myfirst & 0xfffffffcU) != 0));
}
