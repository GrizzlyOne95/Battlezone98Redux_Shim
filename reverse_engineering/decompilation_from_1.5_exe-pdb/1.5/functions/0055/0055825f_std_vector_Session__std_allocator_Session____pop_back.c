/*
 * Entry: 0055825f
 * Name: std::vector<Session_*,std::allocator<Session_*>_>::pop_back
 * Namespace: std::vector<Session_*,std::allocator<Session_*>_>
 * Signature: void pop_back(vector<Session_*,std::allocator<Session_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::vector<Session_*,std::allocator<Session_*>_>::pop_back
          (vector<Session_*,std::allocator<Session_*>_> *this)

{
  if (((int)this->_Mylast - (int)this->_Myfirst & 0xfffffffcU) != 0) {
    this->_Mylast = this->_Mylast + -1;
  }
  return;
}
