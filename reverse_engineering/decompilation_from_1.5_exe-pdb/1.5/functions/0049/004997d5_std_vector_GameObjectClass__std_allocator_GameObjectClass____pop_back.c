/*
 * Entry: 004997d5
 * Name: std::vector<GameObjectClass_*,std::allocator<GameObjectClass_*>_>::pop_back
 * Namespace: std::vector<GameObjectClass_*,std::allocator<GameObjectClass_*>_>
 * Signature: void pop_back(vector<GameObjectClass_*,std::allocator<GameObjectClass_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::vector<GameObjectClass_*,std::allocator<GameObjectClass_*>_>::pop_back
          (vector<GameObjectClass_*,std::allocator<GameObjectClass_*>_> *this)

{
  if (((int)this->_Mylast - (int)this->_Myfirst & 0xfffffffcU) != 0) {
    this->_Mylast = this->_Mylast + -1;
  }
  return;
}
