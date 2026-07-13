/*
 * Entry: 0055829c
 * Name: std::vector<Player_*,std::allocator<Player_*>_>::~vector<Player_*,std::allocator<Player_*>_>
 * Namespace: std::vector<Player_*,std::allocator<Player_*>_>
 * Signature: void ~vector<Player_*,std::allocator<Player_*>_>(vector<Player_*,std::allocator<Player_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::vector<Player_*,std::allocator<Player_*>_>::~vector<Player_*,std::allocator<Player_*>_>
          (vector<Player_*,std::allocator<Player_*>_> *this)

{
  _Tidy(this);
  operator_delete((void *)this->_padding_);
  return;
}
