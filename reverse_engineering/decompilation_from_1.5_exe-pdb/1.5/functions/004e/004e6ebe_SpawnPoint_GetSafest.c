/*
 * Entry: 004e6ebe
 * Name: SpawnPoint::GetSafest
 * Namespace: SpawnPoint
 * Signature: SpawnPoint * GetSafest(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SpawnPoint * __cdecl SpawnPoint::GetSafest(int param_1)

{
  bool bVar1;
  SpawnPoint **ppSVar2;
  float fVar3;
  _Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_> local_20;
  _Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_> local_18;
  float local_10;
  SpawnPoint *local_c;
  float local_8;
  
  local_c = (SpawnPoint *)0x0;
  local_8 = -1.0;
  if (spawnPointList != (vector<SpawnPoint_*,std::allocator<SpawnPoint_*>_> *)0x0) {
    std::_Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>::
    _Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>
              (&local_20,spawnPointList->_Myfirst,(_Container_base_aux *)spawnPointList);
    local_18._padding_ = local_20._padding_;
    local_18._Myptr = local_20._Myptr;
    std::_Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>::
    _Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>
              (&local_20,spawnPointList->_Mylast,(_Container_base_aux *)spawnPointList);
    bVar1 = std::_Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>::operator==
                      (&local_18,&local_20);
    while (!bVar1) {
      ppSVar2 = std::_Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>::operator*
                          (&local_18);
      if (((*ppSVar2)[1].location.x == 0.0) &&
         ((ppSVar2 = std::_Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>::
                     operator*(&local_18), (*ppSVar2)->netPlayer == (NetPlayer *)0x0 ||
          (ppSVar2 = std::_Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>::
                     operator*(&local_18), (*ppSVar2)->netPlayer == (NetPlayer *)param_1)))) {
        ppSVar2 = std::_Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>::operator*
                            (&local_18);
        local_10 = GetClosestEnemy((*ppSVar2)->location,param_1,1e+30);
        ppSVar2 = std::_Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>::operator*
                            (&local_18);
        fVar3 = GetClosestFullSpawnPoint((*ppSVar2)->location,1e+30);
        fVar3 = Min(local_10,fVar3);
        if (local_8 < fVar3) {
          local_8 = fVar3;
          ppSVar2 = std::_Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>::
                    operator*(&local_18);
          local_c = *ppSVar2;
        }
      }
      std::_Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>::operator++(&local_18)
      ;
      std::_Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>::
      _Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>
                (&local_20,spawnPointList->_Mylast,(_Container_base_aux *)spawnPointList);
      bVar1 = std::_Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>::operator==
                        (&local_18,&local_20);
    }
  }
  return local_c;
}
