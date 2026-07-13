/*
 * Entry: 00554f44
 * Name: std::vector<Player_*,std::allocator<Player_*>_>::empty
 * Namespace: std::vector<Player_*,std::allocator<Player_*>_>
 * Signature: bool empty(vector<Player_*,std::allocator<Player_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall
std::vector<Player_*,std::allocator<Player_*>_>::empty
          (vector<Player_*,std::allocator<Player_*>_> *this)

{
  return (bool)('\x01' - (((int)this->_Mylast - (int)this->_Myfirst & 0xfffffffcU) != 0));
}
