/*
 * Entry: 004e6431
 * Name: std::_Checked_assign_from_base<std::_Vector_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>,SpawnPoint_*_*>
 * Namespace: std
 * Signature: void _Checked_assign_from_base<std::_Vector_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>,SpawnPoint_*_*>(_Vector_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_> * param_1, SpawnPoint * * * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::
_Checked_assign_from_base<std::_Vector_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>,SpawnPoint_*_*>
          (_Vector_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_> *param_1,
          SpawnPoint ***param_2)

{
  *(SpawnPoint ***)&param_1->field_0x4 = *param_2;
  return;
}
