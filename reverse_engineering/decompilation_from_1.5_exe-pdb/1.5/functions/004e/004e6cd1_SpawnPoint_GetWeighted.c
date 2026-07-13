/*
 * Entry: 004e6cd1
 * Name: SpawnPoint::GetWeighted
 * Namespace: SpawnPoint
 * Signature: SpawnPoint * GetWeighted(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: _alloca_probe_16 replaced with injection: alloca_probe */
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Unable to track spacebase fully for stack */

SpawnPoint * __cdecl SpawnPoint::GetWeighted(int param_1)

{
  SpawnPoint *pSVar1;
  bool bVar2;
  int iVar3;
  int iVar4;
  SpawnPoint **ppSVar5;
  undefined4 extraout_ECX;
  float *pfVar6;
  float *pfVar7;
  float fVar8;
  float fVar9;
  float fStack_4c;
  undefined1 auStack_48 [16];
  undefined4 uStack_38;
  _Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_> local_1c;
  _Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_> local_14;
  float local_c;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  if (spawnPointList != (vector<SpawnPoint_*,std::allocator<SpawnPoint_*>_> *)0x0) {
    iVar3 = (int)spawnPointList->_Mylast - (int)spawnPointList->_Myfirst >> 2;
    uStack_38 = 0x4e6d07;
    iVar4 = iVar3 * -4;
    pfVar7 = (float *)(&stack0xffffffcc + iVar4);
    pfVar6 = (float *)(&stack0xffffffcc + iVar4);
    local_c = 0.0;
    *(vector<SpawnPoint_*,std::allocator<SpawnPoint_*>_> **)(auStack_48 + (2 - iVar3) * 4 + 8) =
         spawnPointList;
    *(SpawnPoint ***)(auStack_48 + (1 - iVar3) * 4 + 8) = spawnPointList->_Myfirst;
    *(undefined4 *)(auStack_48 + iVar3 * -4 + 8) = 0x4e6d1d;
    std::_Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>::
    _Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>
              (&local_1c,*(SpawnPoint ***)(auStack_48 + (1 - iVar3) * 4 + 8),
               *(_Container_base_aux **)(auStack_48 + (2 - iVar3) * 4 + 8));
    local_14._padding_ = local_1c._padding_;
    local_14._Myptr = local_1c._Myptr;
    while( true ) {
      *(vector<SpawnPoint_*,std::allocator<SpawnPoint_*>_> **)(auStack_48 + (2 - iVar3) * 4 + 8) =
           spawnPointList;
      *(SpawnPoint ***)(auStack_48 + (1 - iVar3) * 4 + 8) = spawnPointList->_Mylast;
      *(undefined4 *)(auStack_48 + iVar3 * -4 + 8) = 0x4e6df0;
      std::_Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>::
      _Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>
                (&local_1c,*(SpawnPoint ***)(auStack_48 + (1 - iVar3) * 4 + 8),
                 *(_Container_base_aux **)(auStack_48 + (2 - iVar3) * 4 + 8));
      *(_Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_> **)
       (auStack_48 + (2 - iVar3) * 4 + 8) = &local_1c;
      *(undefined4 *)(auStack_48 + (1 - iVar3) * 4 + 8) = 0x4e6dfc;
      bVar2 = std::_Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>::operator==
                        (&local_14,
                         *(_Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_> **)
                          (auStack_48 + (2 - iVar3) * 4 + 8));
      if (bVar2) break;
      *(undefined4 *)(auStack_48 + (2 - iVar3) * 4 + 8) = 0x4e6d36;
      ppSVar5 = std::_Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>::operator*
                          (&local_14);
      if ((*ppSVar5)[1].location.x == 0.0) {
        *(undefined4 *)(auStack_48 + (2 - iVar3) * 4 + 8) = 0x4e6d4a;
        ppSVar5 = std::_Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>::operator*
                            (&local_14);
        if ((*ppSVar5)->netPlayer != (NetPlayer *)0x0) {
          *(undefined4 *)(auStack_48 + (2 - iVar3) * 4 + 8) = 0x4e6d5a;
          ppSVar5 = std::_Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>::
                    operator*(&local_14);
          if ((*ppSVar5)->netPlayer != (NetPlayer *)param_1) goto LAB_004e6dd0;
        }
        *(undefined4 *)(auStack_48 + (2 - iVar3) * 4 + 8) = 0x4e6d6c;
        ppSVar5 = std::_Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>::operator*
                            (&local_14);
        pSVar1 = *ppSVar5;
        *(undefined4 *)(auStack_48 + (2 - iVar3) * 4 + 8) = extraout_ECX;
        *(undefined4 *)(auStack_48 + (2 - iVar3) * 4 + 8) = 0x47afc800;
        *(int *)(auStack_48 + (1 - iVar3) * 4 + 8) = param_1;
        *(float *)(auStack_48 + iVar4) = (pSVar1->location).x;
        *(float *)(auStack_48 + (-1 - iVar3) * 4 + 8) = (pSVar1->location).y;
        *(float *)(auStack_48 + iVar3 * -4 + 8) = (pSVar1->location).z;
        (&fStack_4c)[-iVar3] = 7.202464e-39;
        fVar8 = GetClosestEnemy(*(VECTOR_3D *)(auStack_48 + iVar4),
                                *(int *)(auStack_48 + (1 - iVar3) * 4 + 8),
                                *(float *)(auStack_48 + (2 - iVar3) * 4 + 8));
        *(undefined4 *)(auStack_48 + (2 - iVar3) * 4 + 8) = 0x4e6d98;
        ppSVar5 = std::_Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>::operator*
                            (&local_14);
        pSVar1 = *ppSVar5;
        *(undefined4 *)(auStack_48 + (2 - iVar3) * 4 + 8) = 0x47afc800;
        *(float *)(auStack_48 + (-1 - iVar3) * 4 + 8) = (pSVar1->location).x;
        *(float *)(auStack_48 + iVar3 * -4 + 8) = (pSVar1->location).y;
        *(float *)(auStack_48 + (1 - iVar3) * 4 + 8) = (pSVar1->location).z;
        *(undefined4 *)(auStack_48 + iVar4) = 0x4e6db3;
        fVar9 = GetClosestFullSpawnPoint
                          (*(VECTOR_3D *)(auStack_48 + (-1 - iVar3) * 4 + 8),
                           *(float *)(auStack_48 + (2 - iVar3) * 4 + 8));
        *(float *)(auStack_48 + (2 - iVar3) * 4 + 8) = fVar9;
        *(float *)(auStack_48 + (1 - iVar3) * 4 + 8) = fVar8;
        *(undefined4 *)(auStack_48 + iVar3 * -4 + 8) = 0x4e6dc4;
        fVar8 = Min(*(float *)(auStack_48 + (1 - iVar3) * 4 + 8),
                    *(float *)(auStack_48 + (2 - iVar3) * 4 + 8));
        *pfVar6 = fVar8;
        local_c = fVar8 + local_c;
      }
      else {
LAB_004e6dd0:
        *pfVar6 = 0.0;
      }
      *(undefined4 *)(auStack_48 + (2 - iVar3) * 4 + 8) = 0x4e6ddc;
      std::_Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>::operator++(&local_14)
      ;
      pfVar6 = pfVar6 + 1;
    }
    *(undefined4 *)(auStack_48 + (2 - iVar3) * 4 + 8) = 0x4e6e0a;
    iVar4 = rand();
    *(vector<SpawnPoint_*,std::allocator<SpawnPoint_*>_> **)(auStack_48 + (2 - iVar3) * 4 + 8) =
         spawnPointList;
    *(SpawnPoint ***)(auStack_48 + (1 - iVar3) * 4 + 8) = spawnPointList->_Myfirst;
    local_c = (float)iVar4 * local_c * 3.051851e-05;
    *(undefined4 *)(auStack_48 + iVar3 * -4 + 8) = 0x4e6e2d;
    std::_Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>::
    _Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>
              (&local_1c,*(SpawnPoint ***)(auStack_48 + (1 - iVar3) * 4 + 8),
               *(_Container_base_aux **)(auStack_48 + (2 - iVar3) * 4 + 8));
    local_14._padding_ = local_1c._padding_;
    local_14._Myptr = local_1c._Myptr;
    *(vector<SpawnPoint_*,std::allocator<SpawnPoint_*>_> **)(auStack_48 + (2 - iVar3) * 4 + 8) =
         spawnPointList;
    *(SpawnPoint ***)(auStack_48 + (1 - iVar3) * 4 + 8) = spawnPointList->_Mylast;
    *(undefined4 *)(auStack_48 + iVar3 * -4 + 8) = 0x4e6e4a;
    std::_Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>::
    _Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>
              (&local_1c,*(SpawnPoint ***)(auStack_48 + (1 - iVar3) * 4 + 8),
               *(_Container_base_aux **)(auStack_48 + (2 - iVar3) * 4 + 8));
    *(_Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_> **)
     (auStack_48 + (2 - iVar3) * 4 + 8) = &local_1c;
    *(undefined4 *)(auStack_48 + (1 - iVar3) * 4 + 8) = 0x4e6e56;
    bVar2 = std::_Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>::operator==
                      (&local_14,
                       *(_Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_> **)
                        (auStack_48 + (2 - iVar3) * 4 + 8));
    while (!bVar2) {
      local_c = local_c - *pfVar7;
      if (local_c < 0.0) {
        *(undefined4 *)(auStack_48 + (2 - iVar3) * 4 + 8) = 0x4e6ea4;
        ppSVar5 = std::_Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>::operator*
                            (&local_14);
        return *ppSVar5;
      }
      *(undefined4 *)(auStack_48 + (2 - iVar3) * 4 + 8) = 0x4e6e79;
      std::_Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>::operator++(&local_14)
      ;
      *(vector<SpawnPoint_*,std::allocator<SpawnPoint_*>_> **)(auStack_48 + (2 - iVar3) * 4 + 8) =
           spawnPointList;
      *(SpawnPoint ***)(auStack_48 + (1 - iVar3) * 4 + 8) = spawnPointList->_Mylast;
      pfVar7 = pfVar7 + 1;
      *(undefined4 *)(auStack_48 + iVar3 * -4 + 8) = 0x4e6e8d;
      std::_Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>::
      _Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>
                (&local_1c,*(SpawnPoint ***)(auStack_48 + (1 - iVar3) * 4 + 8),
                 *(_Container_base_aux **)(auStack_48 + (2 - iVar3) * 4 + 8));
      *(_Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_> **)
       (auStack_48 + (2 - iVar3) * 4 + 8) = &local_1c;
      *(undefined4 *)(auStack_48 + (1 - iVar3) * 4 + 8) = 0x4e6e99;
      bVar2 = std::_Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>::operator==
                        (&local_14,
                         *(_Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_> **)
                          (auStack_48 + (2 - iVar3) * 4 + 8));
    }
  }
  return (SpawnPoint *)0x0;
}
