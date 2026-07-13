/*
 * Entry: 00415309
 * Name: std::vector<GameObject_*,std::allocator<GameObject_*>_>::size
 * Namespace: std::vector<GameObject_*,std::allocator<GameObject_*>_>
 * Signature: uint size(vector<GameObject_*,std::allocator<GameObject_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uint __thiscall
std::vector<GameObject_*,std::allocator<GameObject_*>_>::size
          (vector<GameObject_*,std::allocator<GameObject_*>_> *this)

{
  return (int)this->_Mylast - (int)this->_Myfirst >> 2;
}
