/*
 * Entry: 00499252
 * Name: std::vector<GameObjectClass_*,std::allocator<GameObjectClass_*>_>::size
 * Namespace: std::vector<GameObjectClass_*,std::allocator<GameObjectClass_*>_>
 * Signature: uint size(vector<GameObjectClass_*,std::allocator<GameObjectClass_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uint __thiscall
std::vector<GameObjectClass_*,std::allocator<GameObjectClass_*>_>::size
          (vector<GameObjectClass_*,std::allocator<GameObjectClass_*>_> *this)

{
  return (int)this->_Mylast - (int)this->_Myfirst >> 2;
}
