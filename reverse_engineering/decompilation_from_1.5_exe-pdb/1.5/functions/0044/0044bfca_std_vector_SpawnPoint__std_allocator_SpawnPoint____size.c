/*
 * Entry: 0044bfca
 * Name: std::vector<SpawnPoint_*,std::allocator<SpawnPoint_*>_>::size
 * Namespace: std::vector<SpawnPoint_*,std::allocator<SpawnPoint_*>_>
 * Signature: uint size(vector<SpawnPoint_*,std::allocator<SpawnPoint_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uint __thiscall
std::vector<SpawnPoint_*,std::allocator<SpawnPoint_*>_>::size
          (vector<SpawnPoint_*,std::allocator<SpawnPoint_*>_> *this)

{
  return (int)this->_Mylast - (int)this->_Myfirst >> 2;
}
