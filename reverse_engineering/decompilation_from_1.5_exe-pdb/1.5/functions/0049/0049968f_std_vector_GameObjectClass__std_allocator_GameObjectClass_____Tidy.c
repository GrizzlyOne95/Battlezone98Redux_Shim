/*
 * Entry: 0049968f
 * Name: std::vector<GameObjectClass_*,std::allocator<GameObjectClass_*>_>::_Tidy
 * Namespace: std::vector<GameObjectClass_*,std::allocator<GameObjectClass_*>_>
 * Signature: void _Tidy(vector<GameObjectClass_*,std::allocator<GameObjectClass_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::vector<GameObjectClass_*,std::allocator<GameObjectClass_*>_>::_Tidy
          (vector<GameObjectClass_*,std::allocator<GameObjectClass_*>_> *this)

{
  if (this->_Myfirst != (GameObjectClass **)0x0) {
    operator_delete(this->_Myfirst);
  }
  this->_Myfirst = (GameObjectClass **)0x0;
  this->_Mylast = (GameObjectClass **)0x0;
  this->_Myend = (GameObjectClass **)0x0;
  return;
}
