/*
 * Entry: 00555039
 * Name: std::vector<Session_*,std::allocator<Session_*>_>::size
 * Namespace: std::vector<Session_*,std::allocator<Session_*>_>
 * Signature: uint size(vector<Session_*,std::allocator<Session_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uint __thiscall
std::vector<Session_*,std::allocator<Session_*>_>::size
          (vector<Session_*,std::allocator<Session_*>_> *this)

{
  return (int)this->_Mylast - (int)this->_Myfirst >> 2;
}
