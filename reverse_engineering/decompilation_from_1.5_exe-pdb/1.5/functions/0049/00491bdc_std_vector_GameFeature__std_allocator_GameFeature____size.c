/*
 * Entry: 00491bdc
 * Name: std::vector<GameFeature_*,std::allocator<GameFeature_*>_>::size
 * Namespace: std::vector<GameFeature_*,std::allocator<GameFeature_*>_>
 * Signature: uint size(vector<GameFeature_*,std::allocator<GameFeature_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uint __thiscall
std::vector<GameFeature_*,std::allocator<GameFeature_*>_>::size
          (vector<GameFeature_*,std::allocator<GameFeature_*>_> *this)

{
  return (int)this->_Mylast - (int)this->_Myfirst >> 2;
}
