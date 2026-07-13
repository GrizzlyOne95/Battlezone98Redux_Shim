/*
 * Entry: 0044c348
 * Name: std::vector<SpawnPoint_*,std::allocator<SpawnPoint_*>_>::empty
 * Namespace: std::vector<SpawnPoint_*,std::allocator<SpawnPoint_*>_>
 * Signature: bool empty(vector<SpawnPoint_*,std::allocator<SpawnPoint_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall
std::vector<SpawnPoint_*,std::allocator<SpawnPoint_*>_>::empty
          (vector<SpawnPoint_*,std::allocator<SpawnPoint_*>_> *this)

{
  return (bool)('\x01' - (((int)this->_Mylast - (int)this->_Myfirst & 0xfffffffcU) != 0));
}
