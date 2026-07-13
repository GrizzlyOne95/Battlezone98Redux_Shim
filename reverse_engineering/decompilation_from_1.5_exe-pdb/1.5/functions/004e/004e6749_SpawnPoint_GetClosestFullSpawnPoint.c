/*
 * Entry: 004e6749
 * Name: SpawnPoint::GetClosestFullSpawnPoint
 * Namespace: SpawnPoint
 * Signature: float GetClosestFullSpawnPoint(VECTOR_3D param_1, float param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __cdecl SpawnPoint::GetClosestFullSpawnPoint(VECTOR_3D param_1,float param_2)

{
  bool bVar1;
  SpawnPoint **ppSVar2;
  float fVar3;
  _Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_> local_14;
  _Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_> local_c;
  
  if (spawnPointList != (vector<SpawnPoint_*,std::allocator<SpawnPoint_*>_> *)0x0) {
    std::_Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>::
    _Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>
              (&local_14,spawnPointList->_Myfirst,(_Container_base_aux *)spawnPointList);
    local_c._padding_ = local_14._padding_;
    local_c._Myptr = local_14._Myptr;
    while( true ) {
      std::_Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>::
      _Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>
                (&local_14,spawnPointList->_Mylast,(_Container_base_aux *)spawnPointList);
      bVar1 = std::_Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>::operator==
                        (&local_c,&local_14);
      if (bVar1) break;
      ppSVar2 = std::_Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>::operator*
                          (&local_c);
      if ((*ppSVar2)[1].location.x != 0.0) {
        ppSVar2 = std::_Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>::operator*
                            (&local_c);
        fVar3 = Dist3D_Squared(param_1,(*ppSVar2)->location);
        if (fVar3 < param_2) {
          param_2 = fVar3;
        }
      }
      std::_Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>::operator++(&local_c);
    }
  }
  return param_2;
}
