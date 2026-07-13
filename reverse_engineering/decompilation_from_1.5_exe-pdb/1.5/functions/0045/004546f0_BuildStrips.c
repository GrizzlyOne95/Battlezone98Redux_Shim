/*
 * Entry: 004546f0
 * Name: BuildStrips
 * Namespace: Global
 * Signature: void BuildStrips(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl BuildStrips(void)

{
  Strip **ppSVar1;
  Strip **ppSVar2;
  int *piVar3;
  _Vector_const_iterator<Strip_*,std::allocator<Strip_*>_> _Var4;
  _Vector_const_iterator<Strip_*,std::allocator<Strip_*>_> _Var5;
  _Vector_const_iterator<Strip_*,std::allocator<Strip_*>_> _Var6;
  _Vector_const_iterator<Strip_*,std::allocator<Strip_*>_> _Var7;
  vector<Strip_*,std::allocator<Strip_*>_> *pvVar8;
  Strip ***pppSVar9;
  int iVar10;
  uint *puVar11;
  undefined4 *puVar12;
  uint uVar13;
  Strip ***pppSVar14;
  Strip **ppSVar15;
  int unaff_ESI;
  uint uVar16;
  Strip **unaff_EDI;
  Strip *pSVar17;
  PathZone *local_38;
  int local_34;
  int local_30;
  undefined1 local_2c [4];
  Strip ***local_28;
  Strip ***local_24;
  Strip *local_20;
  undefined1 local_1c [4];
  Strip *local_18;
  Strip *local_14;
  undefined1 auStack_10 [12];
  
  if (zones != (PathZone *)0x0) {
    local_38 = (PathZone *)(zoneHeight * zoneWidth);
    if (local_38 != (PathZone *)0x0) {
      pppSVar14 = &(zones->terrainStrips)._Myfirst;
      do {
        ppSVar15 = *pppSVar14;
        local_38 = (PathZone *)((int)local_38 + -1);
        local_28 = pppSVar14;
        if (pppSVar14[1] < ppSVar15) {
          _invalid_parameter_noinfo();
        }
        pSVar17 = (Strip *)((vector<Strip_*,std::allocator<Strip_*>_> *)(pppSVar14 + -3))->_padding_
        ;
        local_18 = pSVar17;
        while( true ) {
          ppSVar1 = pppSVar14[1];
          if (ppSVar1 < *pppSVar14) {
            _invalid_parameter_noinfo();
          }
          if ((pSVar17 == (Strip *)0x0) ||
             (pSVar17 !=
              (Strip *)((vector<Strip_*,std::allocator<Strip_*>_> *)(pppSVar14 + -3))->_padding_)) {
            _invalid_parameter_noinfo();
          }
          if (ppSVar15 == ppSVar1) break;
          if (pSVar17 == (Strip *)0x0) {
            _invalid_parameter_noinfo();
            iVar10 = 0;
          }
          else {
            iVar10 = pSVar17->_padding_;
          }
          if (*(Strip ***)(iVar10 + 0x10) <= ppSVar15) {
            _invalid_parameter_noinfo();
          }
          pvVar8 = freeStrips;
          local_20 = *ppSVar15;
          uVar13 = 0;
          local_20->seqNo = 0;
          ppSVar1 = pvVar8->_Myfirst;
          if (ppSVar1 != (Strip **)0x0) {
            uVar13 = (int)pvVar8->_Myend - (int)ppSVar1 >> 2;
          }
          ppSVar2 = freeStrips->_Mylast;
          if ((uint)((int)ppSVar2 - (int)ppSVar1 >> 2) < uVar13) {
            *ppSVar2 = local_20;
            freeStrips->_Mylast = ppSVar2 + 1;
          }
          else {
            if (ppSVar2 < ppSVar1) {
              _invalid_parameter_noinfo();
            }
            _Var6._Myptr = (Strip **)pvVar8->_padding_;
            _Var6._padding_ = (int)local_1c;
            std::vector<Strip_*,std::allocator<Strip_*>_>::insert(pvVar8,_Var6,ppSVar2);
          }
          pSVar17 = local_14;
          if (local_14 == (Strip *)0x0) {
            _invalid_parameter_noinfo();
            iVar10 = 0;
          }
          else {
            iVar10 = local_14->_padding_;
          }
          if (*(Strip ***)(iVar10 + 0x10) <= ppSVar15) {
            _invalid_parameter_noinfo();
          }
          ppSVar15 = ppSVar15 + 1;
          pppSVar14 = local_24;
        }
        unaff_EDI = pppSVar14[1];
        if (unaff_EDI < *pppSVar14) {
          _invalid_parameter_noinfo();
        }
        ppSVar15 = *pppSVar14;
        ppSVar1 = (Strip **)
                  ((vector<Strip_*,std::allocator<Strip_*>_> *)(pppSVar14 + -3))->_padding_;
        if (pppSVar14[1] < ppSVar15) {
          _invalid_parameter_noinfo();
        }
        _Var4._Myptr = (Strip **)
                       ((vector<Strip_*,std::allocator<Strip_*>_> *)(pppSVar14 + -3))->_padding_;
        _Var4._padding_ = (int)local_2c;
        _Var7._Myptr = ppSVar1;
        _Var7._padding_ = (int)ppSVar15;
        std::vector<Strip_*,std::allocator<Strip_*>_>::erase
                  ((vector<Strip_*,std::allocator<Strip_*>_> *)(pppSVar14 + -3),_Var4,_Var7);
        pppSVar14 = pppSVar14 + 0x49;
        local_28 = pppSVar14;
      } while (local_38 != (PathZone *)0x0);
    }
    if (zones != (PathZone *)0x0) {
      PathZone::_vector_deleting_destructor_(zones,3);
    }
    pathMem = pathMem + zoneHeight * zoneWidth * -0x124;
  }
  lavaMat = GetLavaMat();
  cellHeight = GridMaxZ - GridMinZ;
  cellWidth = GridMaxX - GridMinX;
  zoneHeight = (int)(cellHeight + 0xf + (cellHeight + 0xf >> 0x1f & 0xfU)) >> 4;
  zoneWidth = (int)(cellWidth + 0xf + (cellWidth + 0xf >> 0x1f & 0xfU)) >> 4;
  uVar16 = zoneHeight * zoneWidth;
  sBuiltZoneWidth = zoneWidth + -1;
  sBuiltZoneHeight = zoneHeight + -1;
  uVar13 = -(uint)((int)((ulonglong)uVar16 * 0x124 >> 0x20) != 0) |
           (uint)((ulonglong)uVar16 * 0x124);
  sBuiltZoneMax2D = uVar16;
  puVar11 = operator_new__(-(uint)(0xfffffffb < uVar13) | uVar13 + 4);
  if (puVar11 == (uint *)0x0) {
    local_38 = (PathZone *)0x0;
  }
  else {
    iVar10 = uVar16 - 1;
    *puVar11 = uVar16;
    local_38 = (PathZone *)(puVar11 + 1);
    if (-1 < iVar10) {
      puVar11 = puVar11 + 6;
      do {
        puVar12 = operator_new(4);
        if (puVar12 == (undefined4 *)0x0) {
          puVar12 = (undefined4 *)0x0;
        }
        else {
          *puVar12 = puVar11 + -4;
        }
        puVar11[-4] = (uint)puVar12;
        puVar11[-1] = 0;
        *puVar11 = 0;
        puVar11[1] = 0;
        puVar11 = puVar11 + 0x49;
        iVar10 = iVar10 + -1;
      } while (-1 < iVar10);
    }
  }
  pathMem = pathMem + zoneHeight * zoneWidth * 0x124;
  zones = local_38;
  std::vector<Strip_*,std::allocator<Strip_*>_>::reserve
            (&local_38->terrainStrips,zoneHeight * zoneWidth + 4);
  local_30 = 0;
  if (0 < zoneHeight) {
    local_28 = (Strip ***)0x0;
    iVar10 = zoneWidth;
    do {
      local_24 = (Strip ***)0x0;
      if (0 < iVar10) {
        local_34 = 0;
        pppSVar14 = &(local_38->terrainStrips)._Mylast;
        do {
          pvVar8 = freeStrips;
          pSVar17 = (Strip *)freeStrips->_Mylast;
          if (((int)pSVar17 - (int)freeStrips->_Myfirst & 0xfffffffcU) == 0) {
            if (0xffff < StripCount) {
                    /* WARNING: Subroutine does not return */
              exit(1);
            }
            local_18 = AllStrips + StripCount;
            StripCount = StripCount + 1;
          }
          else {
            if (pSVar17 < (Strip *)freeStrips->_Myfirst) {
              _invalid_parameter_noinfo();
            }
            piVar3 = (int *)pvVar8->_padding_;
            local_14 = pSVar17;
            if (piVar3 == (int *)0x0) {
              _invalid_parameter_noinfo();
              iVar10 = 0;
            }
            else {
              iVar10 = *piVar3;
            }
            if (*(undefined1 **)(iVar10 + 0x10) < &pSVar17[-1].next) {
LAB_00454a5f:
              _invalid_parameter_noinfo();
            }
            else {
              if (piVar3 == (int *)0x0) {
                iVar10 = 0;
              }
              else {
                iVar10 = *piVar3;
              }
              if (&pSVar17[-1].next < *(undefined1 **)(iVar10 + 0xc)) goto LAB_00454a5f;
            }
            if (piVar3 == (int *)0x0) {
              _invalid_parameter_noinfo();
              iVar10 = 0;
            }
            else {
              iVar10 = *piVar3;
            }
            if (*(undefined1 **)(iVar10 + 0x10) <= &pSVar17[-1].next) {
              _invalid_parameter_noinfo();
            }
            local_18 = pSVar17[-1].next;
            if (((int)freeStrips->_Mylast - (int)freeStrips->_Myfirst & 0xfffffffcU) != 0) {
              freeStrips->_Mylast = freeStrips->_Mylast + -1;
            }
          }
          local_18->g = 0.0;
          local_18->link = false;
          local_18->open = false;
          local_18->backward = false;
          local_18->detour = false;
          local_18->visited = false;
          stripSeqNo = stripSeqNo + 1;
          local_18->seqNo = stripSeqNo;
          uVar13 = 0;
          local_18->prev = (Strip *)0x0;
          local_18->next = (Strip *)0x0;
          local_18->material = 7;
          local_18->neighbor = -2;
          iVar10 = local_34 + GridMinX;
          local_18->x0 = (float)iVar10;
          local_18->x1 = (float)iVar10 + 16.0;
          local_20 = (Strip *)((int)local_28 + GridMinZ);
          local_18->z0 = (float)(int)local_20;
          local_18->z1 = (float)(int)local_20 + 16.0;
          ppSVar15 = pppSVar14[-1];
          if (ppSVar15 != (Strip **)0x0) {
            uVar13 = (int)pppSVar14[1] - (int)ppSVar15 >> 2;
          }
          ppSVar1 = *pppSVar14;
          if ((uint)((int)ppSVar1 - (int)ppSVar15 >> 2) < uVar13) {
            *ppSVar1 = local_18;
            *pppSVar14 = ppSVar1 + 1;
          }
          else {
            if (ppSVar1 < ppSVar15) {
              _invalid_parameter_noinfo();
            }
            _Var5._Myptr = (Strip **)
                           ((vector<Strip_*,std::allocator<Strip_*>_> *)(pppSVar14 + -4))->_padding_
            ;
            _Var5._padding_ = (int)auStack_10;
            std::vector<Strip_*,std::allocator<Strip_*>_>::insert
                      ((vector<Strip_*,std::allocator<Strip_*>_> *)(pppSVar14 + -4),_Var5,ppSVar1);
          }
          pppSVar9 = local_24;
          local_38->built = false;
          BuildZone((int)unaff_EDI,unaff_ESI);
          local_34 = local_34 + 0x10;
          local_24 = (Strip ***)((int)pppSVar9 + 1);
          local_38 = local_38 + 1;
          pppSVar14 = pppSVar14 + 0x49;
          iVar10 = zoneWidth;
        } while ((int)local_24 < zoneWidth);
      }
      local_28 = (Strip ***)((int)local_28 + 0x10);
      local_30 = local_30 + 1;
    } while (local_30 < zoneHeight);
  }
  return;
}
