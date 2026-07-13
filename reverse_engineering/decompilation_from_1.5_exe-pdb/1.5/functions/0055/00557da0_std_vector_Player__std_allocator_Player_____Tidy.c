/*
 * Entry: 00557da0
 * Name: std::vector<Player_*,std::allocator<Player_*>_>::_Tidy
 * Namespace: std::vector<Player_*,std::allocator<Player_*>_>
 * Signature: void _Tidy(vector<Player_*,std::allocator<Player_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::vector<Player_*,std::allocator<Player_*>_>::_Tidy
          (vector<Player_*,std::allocator<Player_*>_> *this)

{
  if (this->_Myfirst != (Player **)0x0) {
    operator_delete(this->_Myfirst);
  }
  this->_Myfirst = (Player **)0x0;
  this->_Mylast = (Player **)0x0;
  this->_Myend = (Player **)0x0;
  return;
}
