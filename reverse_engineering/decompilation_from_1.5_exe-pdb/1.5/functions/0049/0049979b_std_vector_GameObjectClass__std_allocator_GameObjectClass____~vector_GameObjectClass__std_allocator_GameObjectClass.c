/*
 * Entry: 0049979b
 * Name: std::vector<GameObjectClass_*,std::allocator<GameObjectClass_*>_>::~vector<GameObjectClass_*,std::allocator<GameObjectClass_*>_>
 * Namespace: std::vector<GameObjectClass_*,std::allocator<GameObjectClass_*>_>
 * Signature: void ~vector<GameObjectClass_*,std::allocator<GameObjectClass_*>_>(vector<GameObjectClass_*,std::allocator<GameObjectClass_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::vector<GameObjectClass_*,std::allocator<GameObjectClass_*>_>::
~vector<GameObjectClass_*,std::allocator<GameObjectClass_*>_>
          (vector<GameObjectClass_*,std::allocator<GameObjectClass_*>_> *this)

{
  _Tidy(this);
  operator_delete((void *)this->_padding_);
  return;
}
