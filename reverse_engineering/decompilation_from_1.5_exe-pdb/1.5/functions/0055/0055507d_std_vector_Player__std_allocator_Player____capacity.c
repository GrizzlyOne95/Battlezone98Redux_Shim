/*
 * Entry: 0055507d
 * Name: std::vector<Player_*,std::allocator<Player_*>_>::capacity
 * Namespace: std::vector<Player_*,std::allocator<Player_*>_>
 * Signature: uint capacity(vector<Player_*,std::allocator<Player_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uint __thiscall
std::vector<Player_*,std::allocator<Player_*>_>::capacity
          (vector<Player_*,std::allocator<Player_*>_> *this)

{
  if (this->_Myfirst == (Player **)0x0) {
    return 0;
  }
  return (int)this->_Myend - (int)this->_Myfirst >> 2;
}
