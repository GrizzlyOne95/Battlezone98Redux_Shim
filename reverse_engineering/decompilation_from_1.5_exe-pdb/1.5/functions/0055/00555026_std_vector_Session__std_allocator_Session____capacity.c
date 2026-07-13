/*
 * Entry: 00555026
 * Name: std::vector<Session_*,std::allocator<Session_*>_>::capacity
 * Namespace: std::vector<Session_*,std::allocator<Session_*>_>
 * Signature: uint capacity(vector<Session_*,std::allocator<Session_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uint __thiscall
std::vector<Session_*,std::allocator<Session_*>_>::capacity
          (vector<Session_*,std::allocator<Session_*>_> *this)

{
  if (this->_Myfirst == (Session **)0x0) {
    return 0;
  }
  return (int)this->_Myend - (int)this->_Myfirst >> 2;
}
