/*
 * Entry: 0049696a
 * Name: std::vector<GameObject_*,std::allocator<GameObject_*>_>::capacity
 * Namespace: std::vector<GameObject_*,std::allocator<GameObject_*>_>
 * Signature: uint capacity(vector<GameObject_*,std::allocator<GameObject_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uint __thiscall
std::vector<GameObject_*,std::allocator<GameObject_*>_>::capacity
          (vector<GameObject_*,std::allocator<GameObject_*>_> *this)

{
  if (this->_Myfirst == (GameObject **)0x0) {
    return 0;
  }
  return (int)this->_Myend - (int)this->_Myfirst >> 2;
}
