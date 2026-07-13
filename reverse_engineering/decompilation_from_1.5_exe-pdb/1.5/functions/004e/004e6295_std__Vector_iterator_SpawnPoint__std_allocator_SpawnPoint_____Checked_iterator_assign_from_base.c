/*
 * Entry: 004e6295
 * Name: std::_Vector_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>::_Checked_iterator_assign_from_base
 * Namespace: std::_Vector_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>
 * Signature: void _Checked_iterator_assign_from_base(_Vector_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_> * this, SpawnPoint * * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::_Vector_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>::
_Checked_iterator_assign_from_base
          (_Vector_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_> *this,SpawnPoint **param_1)

{
  *(SpawnPoint ***)&this->field_0x4 = param_1;
  return;
}
