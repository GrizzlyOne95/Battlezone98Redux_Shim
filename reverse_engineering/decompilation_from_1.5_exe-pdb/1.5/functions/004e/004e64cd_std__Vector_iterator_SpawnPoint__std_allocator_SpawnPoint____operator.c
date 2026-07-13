/*
 * Entry: 004e64cd
 * Name: std::_Vector_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>::operator+=
 * Namespace: std::_Vector_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>
 * Signature: _Vector_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_> * operator+=(_Vector_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_> * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_> * __thiscall
std::_Vector_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>::operator+=
          (_Vector_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_> *this,int param_1)

{
  _Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>::operator+=
            ((_Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_> *)this,param_1);
  return this;
}
