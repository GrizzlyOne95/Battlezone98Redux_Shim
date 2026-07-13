/*
 * Entry: 0049950a
 * Name: std::vector<GameObjectClass_*,std::allocator<GameObjectClass_*>_>::empty
 * Namespace: std::vector<GameObjectClass_*,std::allocator<GameObjectClass_*>_>
 * Signature: bool empty(vector<GameObjectClass_*,std::allocator<GameObjectClass_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall
std::vector<GameObjectClass_*,std::allocator<GameObjectClass_*>_>::empty
          (vector<GameObjectClass_*,std::allocator<GameObjectClass_*>_> *this)

{
  return (bool)('\x01' - (((int)this->_Mylast - (int)this->_Myfirst & 0xfffffffcU) != 0));
}
