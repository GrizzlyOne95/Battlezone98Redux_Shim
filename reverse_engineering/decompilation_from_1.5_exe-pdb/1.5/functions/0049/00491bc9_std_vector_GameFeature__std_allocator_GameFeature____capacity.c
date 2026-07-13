/*
 * Entry: 00491bc9
 * Name: std::vector<GameFeature_*,std::allocator<GameFeature_*>_>::capacity
 * Namespace: std::vector<GameFeature_*,std::allocator<GameFeature_*>_>
 * Signature: uint capacity(vector<GameFeature_*,std::allocator<GameFeature_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uint __thiscall
std::vector<GameFeature_*,std::allocator<GameFeature_*>_>::capacity
          (vector<GameFeature_*,std::allocator<GameFeature_*>_> *this)

{
  if (this->_Myfirst == (GameFeature **)0x0) {
    return 0;
  }
  return (int)this->_Myend - (int)this->_Myfirst >> 2;
}
