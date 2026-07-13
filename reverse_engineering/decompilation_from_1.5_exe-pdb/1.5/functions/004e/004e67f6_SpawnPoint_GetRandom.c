/*
 * Entry: 004e67f6
 * Name: SpawnPoint::GetRandom
 * Namespace: SpawnPoint
 * Signature: SpawnPoint * GetRandom(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: _alloca_probe_16 replaced with injection: alloca_probe */
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Unable to track spacebase fully for stack */

SpawnPoint * __cdecl SpawnPoint::GetRandom(int param_1)

{
  bool bVar1;
  int iVar2;
  SpawnPoint **ppSVar3;
  int iVar4;
  int iVar5;
  int aiStack_34 [3];
  SpawnPoint *local_1c;
  _Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_> local_18;
  _Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_> local_10;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  iVar5 = 0;
  local_1c = (SpawnPoint *)0x0;
  if ((spawnPointList != (vector<SpawnPoint_*,std::allocator<SpawnPoint_*>_> *)0x0) &&
     (iVar2 = (int)spawnPointList->_Mylast - (int)spawnPointList->_Myfirst >> 2, iVar2 != 0)) {
    aiStack_34[2] = 0x4e6835;
    aiStack_34[2 - iVar2] = (int)spawnPointList;
    aiStack_34[1 - iVar2] = (int)spawnPointList->_Myfirst;
    aiStack_34[-iVar2] = 0x4e6843;
    std::_Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>::
    _Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>
              (&local_18,(SpawnPoint **)aiStack_34[1 - iVar2],
               (_Container_base_aux *)aiStack_34[2 - iVar2]);
    local_10._padding_ = local_18._padding_;
    local_10._Myptr = local_18._Myptr;
    aiStack_34[2 - iVar2] = (int)spawnPointList;
    aiStack_34[1 - iVar2] = (int)spawnPointList->_Mylast;
    aiStack_34[-iVar2] = 0x4e6860;
    std::_Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>::
    _Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>
              (&local_18,(SpawnPoint **)aiStack_34[1 - iVar2],
               (_Container_base_aux *)aiStack_34[2 - iVar2]);
    aiStack_34[2 - iVar2] = (int)&local_18;
    aiStack_34[1 - iVar2] = 0x4e686c;
    bVar1 = std::_Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>::operator==
                      (&local_10,
                       (_Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_> *)
                       aiStack_34[2 - iVar2]);
    if (!bVar1) {
      do {
        aiStack_34[2 - iVar2] = 0x4e687c;
        ppSVar3 = std::_Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>::operator*
                            (&local_10);
        if ((*ppSVar3)[1].location.x == 0.0) {
          aiStack_34[2 - iVar2] = 0x4e688c;
          ppSVar3 = std::_Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>::
                    operator*(&local_10);
          if ((*ppSVar3)->netPlayer != (NetPlayer *)0x0) {
            aiStack_34[2 - iVar2] = 0x4e689c;
            ppSVar3 = std::_Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>::
                      operator*(&local_10);
            if ((*ppSVar3)->netPlayer != (NetPlayer *)param_1) goto LAB_004e68b4;
          }
          aiStack_34[2 - iVar2] = 0x4e68ae;
          ppSVar3 = std::_Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>::
                    operator*(&local_10);
          *(SpawnPoint **)(&stack0xffffffd8 + iVar5 * 4 + iVar2 * -4) = *ppSVar3;
          iVar5 = iVar5 + 1;
        }
LAB_004e68b4:
        aiStack_34[2 - iVar2] = 0x4e68bc;
        std::_Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>::operator++
                  (&local_10);
        aiStack_34[2 - iVar2] = (int)spawnPointList;
        aiStack_34[1 - iVar2] = (int)spawnPointList->_Mylast;
        aiStack_34[-iVar2] = 0x4e68cd;
        std::_Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>::
        _Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>
                  (&local_18,(SpawnPoint **)aiStack_34[1 - iVar2],
                   (_Container_base_aux *)aiStack_34[2 - iVar2]);
        aiStack_34[2 - iVar2] = (int)&local_18;
        aiStack_34[1 - iVar2] = 0x4e68d9;
        bVar1 = std::_Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>::operator==
                          (&local_10,
                           (_Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_> *)
                           aiStack_34[2 - iVar2]);
      } while (!bVar1);
      if (0 < iVar5) {
        aiStack_34[2 - iVar2] = 0x4e68e7;
        iVar4 = rand();
        local_1c = *(SpawnPoint **)(&stack0xffffffd8 + ((iVar4 * iVar5) / 0x7fff) * 4 + iVar2 * -4);
      }
    }
  }
  return local_1c;
}
