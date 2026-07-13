/*
 * Entry: 00409d25
 * Name: LabelConnectedRegions
 * Namespace: Global
 * Signature: void LabelConnectedRegions(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: _chkstk replaced with injection: alloca_probe */
/* WARNING: Function: _alloca_probe_16 replaced with injection: alloca_probe */
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Unable to track spacebase fully for stack */

void __cdecl LabelConnectedRegions(void)

{
  AiPath *pAVar1;
  bool bVar2;
  ushort uVar3;
  int iVar4;
  Geizer **ppGVar5;
  Team *this;
  GameObject *pGVar6;
  float *pfVar7;
  SpawnPoint **ppSVar8;
  VECTOR_3D *pVVar9;
  Craft **ppCVar10;
  AiPath **ppAVar11;
  uint uVar12;
  ushort uVar13;
  ushort *puVar14;
  undefined1 *extraout_EDX;
  undefined1 *puVar15;
  ushort *puVar16;
  uint *unaff_ESI;
  int iVar17;
  uint uVar18;
  ushort *unaff_EDI;
  int iVar19;
  uint uVar20;
  _Const_iterator<1> _Stack_2022c;
  uint uStack_20224;
  _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_> _Stack_20220;
  ushort *puStack_20218;
  uint uStack_20214;
  _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_> _Stack_20210;
  ushort auStack_20208 [46];
  undefined1 auStack_201ac [130980];
  ushort local_208 [256];
  uint local_8;
  
  iVar4 = cellCount;
  local_8 = __security_cookie ^ (uint)auStack_201ac;
  iVar17 = GridMaxX - GridMinX;
  uStack_20224 = 1;
  puStack_20218 = malloc(cellCount * 2);
  uStack_20214 = GridMinX;
  iVar19 = 0;
  _Stack_20210._Myptr = (Craft **)GridMinZ;
  if (0 < iVar4) {
    puVar16 = puStack_20218 + -iVar17;
    do {
      iVar4 = Material((uint)cellType[iVar19]);
      if (iVar4 == 6) {
        puStack_20218[iVar19] = 0;
      }
      else {
        if (GridMinX < (int)uStack_20214) {
          puVar14 = (ushort *)(uint)puStack_20218[iVar19 + -1];
        }
        else {
          puVar14 = (ushort *)0x0;
        }
        if (GridMinZ < (int)_Stack_20210._Myptr) {
          uVar3 = *puVar16;
        }
        else {
          uVar3 = 0;
        }
        uVar13 = (ushort)puVar14;
        if (uVar13 == 0) {
          if (uVar3 == 0) {
            puStack_20218[iVar19] = (ushort)uStack_20224;
            auStack_20208[uStack_20224 & 0xffff] = (ushort)uStack_20224;
            uStack_20224 = uStack_20224 + 1;
          }
          else {
            puStack_20218[iVar19] = uVar3;
          }
        }
        else if ((uVar3 == 0) || (uVar13 == uVar3)) {
          puStack_20218[iVar19] = uVar13;
        }
        else {
          if (uVar13 < uVar3) {
            puStack_20218[iVar19] = uVar13;
          }
          else {
            puStack_20218[iVar19] = uVar3;
          }
          Union(puVar14,uVar3,(ushort)unaff_EDI);
        }
      }
      uStack_20214 = uStack_20214 + 1;
      if (GridMaxX <= (int)uStack_20214) {
        _Stack_20210._Myptr = (Craft **)((int)_Stack_20210._Myptr + 1);
        uStack_20214 = GridMinX;
        if (GridMaxZ <= (int)_Stack_20210._Myptr) {
          _Stack_20210._Myptr = (Craft **)GridMinZ;
        }
      }
      iVar19 = iVar19 + 1;
      puVar16 = puVar16 + 1;
    } while (iVar19 < cellCount);
  }
  uStack_20214 = 0;
  std::_Vector_const_iterator<Geizer_*,std::allocator<Geizer_*>_>::
  _Vector_const_iterator<Geizer_*,std::allocator<Geizer_*>_>
            ((_Vector_const_iterator<Geizer_*,std::allocator<Geizer_*>_> *)&_Stack_20210,
             Geizer::geizerList._Myfirst,(_Container_base_aux *)&Geizer::geizerList);
  while( true ) {
    std::_Vector_const_iterator<Geizer_*,std::allocator<Geizer_*>_>::
    _Vector_const_iterator<Geizer_*,std::allocator<Geizer_*>_>
              ((_Vector_const_iterator<Geizer_*,std::allocator<Geizer_*>_> *)&_Stack_20220,
               Geizer::geizerList._Mylast,(_Container_base_aux *)&Geizer::geizerList);
    bVar2 = std::_Vector_const_iterator<Geizer_*,std::allocator<Geizer_*>_>::operator==
                      ((_Vector_const_iterator<Geizer_*,std::allocator<Geizer_*>_> *)&_Stack_20210,
                       (_Vector_const_iterator<Geizer_*,std::allocator<Geizer_*>_> *)&_Stack_20220);
    if (bVar2) break;
    ppGVar5 = std::_Vector_const_iterator<Geizer_*,std::allocator<Geizer_*>_>::operator*
                        ((_Vector_const_iterator<Geizer_*,std::allocator<Geizer_*>_> *)&_Stack_20210
                        );
    pfVar7 = (float *)(**(code **)((*ppGVar5)->_padding_ + 0xc))();
    AddPointOfInterest(*pfVar7,pfVar7[2],puStack_20218,auStack_20208,unaff_EDI,unaff_ESI);
    std::_Vector_const_iterator<Geizer_*,std::allocator<Geizer_*>_>::operator++
              ((_Vector_const_iterator<Geizer_*,std::allocator<Geizer_*>_> *)&_Stack_20210);
  }
  _Stack_20210._Myptr = (Craft **)0x0;
  do {
    iVar4 = 0x23;
    do {
      iVar17 = iVar4;
      this = Team::GetTeam((int)_Stack_20210._Myptr);
      pGVar6 = Team::GetSlot(this,iVar17);
      if (pGVar6 != (GameObject *)0x0) {
        pfVar7 = (float *)(**(code **)(pGVar6->_padding_ + 0xc))();
        AddPointOfInterest(*pfVar7,pfVar7[2],puStack_20218,auStack_20208,unaff_EDI,unaff_ESI);
      }
      iVar4 = iVar4 + 1;
    } while (iVar4 < 0x2d);
    _Stack_20210._Myptr = (Craft **)((int)_Stack_20210._Myptr + 1);
  } while ((int)_Stack_20210._Myptr < 0x10);
  if (SpawnPoint::spawnPointList == (vector<SpawnPoint_*,std::allocator<SpawnPoint_*>_> *)0x0) {
    std::_Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>::
    _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>
              (&_Stack_20210,Craft::craftList._Myfirst,(_Container_base_aux *)&Craft::craftList);
    while( true ) {
      std::_Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>::
      _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>
                (&_Stack_20220,Craft::craftList._Mylast,(_Container_base_aux *)&Craft::craftList);
      bVar2 = std::_Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>::operator==
                        (&_Stack_20210,&_Stack_20220);
      if (bVar2) break;
      ppCVar10 = std::_Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>::operator*
                           (&_Stack_20210);
      pfVar7 = (float *)(**(code **)((*ppCVar10)->_padding_ + 0xc))();
      AddPointOfInterest(*pfVar7,pfVar7[2],puStack_20218,auStack_20208,unaff_EDI,unaff_ESI);
      std::_Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>::operator++(&_Stack_20210);
    }
  }
  else {
    std::_Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>::
    _Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>
              ((_Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_> *)&_Stack_20210,
               SpawnPoint::spawnPointList->_Myfirst,
               (_Container_base_aux *)SpawnPoint::spawnPointList);
    while( true ) {
      std::_Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>::
      _Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>
                ((_Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_> *)&_Stack_20220
                 ,SpawnPoint::spawnPointList->_Mylast,
                 (_Container_base_aux *)SpawnPoint::spawnPointList);
      bVar2 = std::_Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>::operator==
                        ((_Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_> *)
                         &_Stack_20210,
                         (_Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_> *)
                         &_Stack_20220);
      if (bVar2) break;
      ppSVar8 = std::_Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>::operator*
                          ((_Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_> *)
                           &_Stack_20210);
      pVVar9 = SpawnPoint::GetLocation(*ppSVar8);
      AddPointOfInterest(pVVar9->x,pVVar9->z,puStack_20218,auStack_20208,unaff_EDI,unaff_ESI);
      std::_Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>::operator++
                ((_Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_> *)&_Stack_20210
                );
    }
  }
  std::list<AiPath_*,std::allocator<AiPath_*>_>::_Const_iterator<1>::_Const_iterator<1>
            ((_Const_iterator<1> *)&_Stack_20220,(AiPath::pathList._Myhead)->_Next,&AiPath::pathList
            );
  while( true ) {
    std::list<AiPath_*,std::allocator<AiPath_*>_>::_Const_iterator<1>::_Const_iterator<1>
              (&_Stack_2022c,AiPath::pathList._Myhead,&AiPath::pathList);
    bVar2 = std::list<AiPath_*,std::allocator<AiPath_*>_>::_Const_iterator<1>::operator==
                      ((_Const_iterator<1> *)&_Stack_20220,&_Stack_2022c);
    if (bVar2) break;
    ppAVar11 = std::list<AiPath_*,std::allocator<AiPath_*>_>::_Const_iterator<1>::operator*
                         ((_Const_iterator<1> *)&_Stack_20220);
    pAVar1 = *ppAVar11;
    if (((pAVar1->label != (char *)0x0) && (iVar4 = _stricmp(pAVar1->label,"edge_path"), iVar4 != 0)
        ) && (_Stack_20210._Myptr = (Craft **)0x0, 0 < pAVar1->pointCount)) {
      do {
        AddPointOfInterest(pAVar1->points[(int)_Stack_20210._Myptr].x,
                           pAVar1->points[(int)_Stack_20210._Myptr].z,puStack_20218,auStack_20208,
                           unaff_EDI,unaff_ESI);
        _Stack_20210._Myptr = (Craft **)((int)_Stack_20210._Myptr + 1);
      } while ((int)_Stack_20210._Myptr < pAVar1->pointCount);
    }
    std::list<AiPath_*,std::allocator<AiPath_*>_>::_Const_iterator<1>::operator++
              ((_Const_iterator<1> *)&_Stack_20220);
  }
  Trace("Found %d interesting regions\n");
  uVar20 = uStack_20224 & 0xffff;
  iVar4 = -uVar20;
  puVar15 = &stack0xfffdfdc8 + iVar4;
  uVar18 = 1;
  (&stack0xfffdfdc8)[iVar4] = 0;
  if (1 < uVar20) {
    do {
      *(uint *)(&stack0xfffdfdc4 + iVar4) = uVar18;
      *(ushort **)(&stack0xfffdfdc0 + iVar4) = auStack_20208;
      *(undefined4 *)(&stack0xfffdfdbc + iVar4) = 0x40a0fa;
      uVar3 = Find(*(ushort **)(&stack0xfffdfdc0 + iVar4),*(ushort *)(&stack0xfffdfdc4 + iVar4));
      uVar12 = 0;
      extraout_EDX[uVar18] = 0;
      if (uStack_20214 != 0) {
        do {
          if (uVar3 == local_208[uVar12]) {
            extraout_EDX[uVar18] = (char)uVar12 + '\x01';
            break;
          }
          uVar12 = uVar12 + 1;
        } while (uVar12 < uStack_20214);
      }
      uVar18 = uVar18 + 1;
      puVar15 = extraout_EDX;
    } while (uVar18 < uVar20);
  }
  iVar17 = cellCount;
  iVar19 = 0;
  if (0 < cellCount) {
    do {
      cellRegion[iVar19] = puVar15[puStack_20218[iVar19]];
      iVar19 = iVar19 + 1;
    } while (iVar19 < iVar17);
  }
  *(ushort **)(&stack0xfffdfdc4 + iVar4) = puStack_20218;
  *(undefined4 *)(&stack0xfffdfdc0 + iVar4) = 0x40a153;
  free(*(void **)(&stack0xfffdfdc4 + iVar4));
  return;
}
