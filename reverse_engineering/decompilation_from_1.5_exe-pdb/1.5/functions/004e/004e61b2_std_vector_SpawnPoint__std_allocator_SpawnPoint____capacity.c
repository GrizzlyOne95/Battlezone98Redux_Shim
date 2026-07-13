/*
 * Entry: 004e61b2
 * Name: std::vector<SpawnPoint_*,std::allocator<SpawnPoint_*>_>::capacity
 * Namespace: std::vector<SpawnPoint_*,std::allocator<SpawnPoint_*>_>
 * Signature: uint capacity(vector<SpawnPoint_*,std::allocator<SpawnPoint_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uint __thiscall
std::vector<SpawnPoint_*,std::allocator<SpawnPoint_*>_>::capacity
          (vector<SpawnPoint_*,std::allocator<SpawnPoint_*>_> *this)

{
  if (this->_Myfirst == (SpawnPoint **)0x0) {
    return 0;
  }
  return (int)this->_Myend - (int)this->_Myfirst >> 2;
}
