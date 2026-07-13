/*
 * Entry: 00408a05
 * Name: std::_Vector_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>::operator++
 * Namespace: std::_Vector_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>
 * Signature: _Vector_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_> * operator++(_Vector_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_> * __thiscall
std::_Vector_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>::operator++
          (_Vector_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_> *this)

{
  _Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>::operator++
            ((_Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_> *)this);
  return this;
}
