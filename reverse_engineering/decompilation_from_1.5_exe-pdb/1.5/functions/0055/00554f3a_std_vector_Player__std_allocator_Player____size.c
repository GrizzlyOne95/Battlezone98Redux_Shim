/*
 * Entry: 00554f3a
 * Name: std::vector<Player_*,std::allocator<Player_*>_>::size
 * Namespace: std::vector<Player_*,std::allocator<Player_*>_>
 * Signature: uint size(vector<Player_*,std::allocator<Player_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uint __thiscall
std::vector<Player_*,std::allocator<Player_*>_>::size
          (vector<Player_*,std::allocator<Player_*>_> *this)

{
  return (int)this->_Mylast - (int)this->_Myfirst >> 2;
}
