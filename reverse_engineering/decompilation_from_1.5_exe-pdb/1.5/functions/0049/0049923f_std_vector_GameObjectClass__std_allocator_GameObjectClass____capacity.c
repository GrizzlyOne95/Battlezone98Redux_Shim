/*
 * Entry: 0049923f
 * Name: std::vector<GameObjectClass_*,std::allocator<GameObjectClass_*>_>::capacity
 * Namespace: std::vector<GameObjectClass_*,std::allocator<GameObjectClass_*>_>
 * Signature: uint capacity(vector<GameObjectClass_*,std::allocator<GameObjectClass_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uint __thiscall
std::vector<GameObjectClass_*,std::allocator<GameObjectClass_*>_>::capacity
          (vector<GameObjectClass_*,std::allocator<GameObjectClass_*>_> *this)

{
  if (this->_Myfirst == (GameObjectClass **)0x0) {
    return 0;
  }
  return (int)this->_Myend - (int)this->_Myfirst >> 2;
}
