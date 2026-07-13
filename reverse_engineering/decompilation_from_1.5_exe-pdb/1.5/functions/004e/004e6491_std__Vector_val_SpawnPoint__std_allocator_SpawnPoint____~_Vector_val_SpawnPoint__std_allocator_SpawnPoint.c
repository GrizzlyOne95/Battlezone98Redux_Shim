/*
 * Entry: 004e6491
 * Name: std::_Vector_val<SpawnPoint_*,std::allocator<SpawnPoint_*>_>::~_Vector_val<SpawnPoint_*,std::allocator<SpawnPoint_*>_>
 * Namespace: std::_Vector_val<SpawnPoint_*,std::allocator<SpawnPoint_*>_>
 * Signature: void ~_Vector_val<SpawnPoint_*,std::allocator<SpawnPoint_*>_>(_Vector_val<SpawnPoint_*,std::allocator<SpawnPoint_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::_Vector_val<SpawnPoint_*,std::allocator<SpawnPoint_*>_>::
~_Vector_val<SpawnPoint_*,std::allocator<SpawnPoint_*>_>
          (_Vector_val<SpawnPoint_*,std::allocator<SpawnPoint_*>_> *this)

{
  operator_delete((void *)this->_padding_);
  return;
}
