/*
 * Entry: 00453760
 * Name: BuildZone
 * Namespace: Global
 * Signature: void BuildZone(int param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl BuildZone(int param_1,int param_2)

{
  float *pfVar1;
  vector<Strip_*,std::allocator<Strip_*>_> *this;
  uchar uVar2;
  byte bVar3;
  ushort uVar4;
  int in_EAX;
  int iVar5;
  uint uVar6;
  Strip **ppSVar7;
  Strip *pSVar8;
  int iVar9;
  int in_ECX;
  Strip *pSVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  int unaff_ESI;
  uint uVar14;
  short *psVar15;
  PathZone *pPVar16;
  vector<Strip_*,std::allocator<Strip_*>_> *this_00;
  int iVar17;
  int local_8;
  Strip *local_4;
  
  if ((((-1 < in_ECX) && (in_ECX <= sBuiltZoneHeight)) && (-1 < in_EAX)) &&
     ((in_EAX <= sBuiltZoneWidth &&
      (pPVar16 = zones + zoneWidth * in_ECX + in_EAX, pPVar16->built == false)))) {
    iVar5 = in_EAX * 0x10 + GridMinX;
    pSVar10 = (Strip *)(in_ECX * 0x10 + GridMinZ);
    pfVar1 = &pSVar10->z1;
    xSlabMax = ((int)pfVar1 - (int)pSVar10) * 2;
    xSlabSize = 0;
    xSlab = operator_new__(-(uint)((int)((ulonglong)(uint)xSlabMax * 4 >> 0x20) != 0) |
                           (uint)((ulonglong)(uint)xSlabMax * 4));
    for (iVar13 = iVar5; pSVar8 = pSVar10, iVar13 < iVar5 + 0x10; iVar13 = iVar13 + 1) {
      while ((int)pSVar8 < (int)pfVar1) {
        local_4 = pSVar8;
        uVar6 = MaterialBuildZone(iVar13,(int)pSVar8);
        do {
          pSVar8 = (Strip *)((int)&pSVar8->_padding_ + 1);
          if ((int)pfVar1 <= (int)pSVar8) break;
          uVar2 = CellRegion(iVar13,(int)pSVar8);
          if (uVar2 == '\0') {
            uVar14 = 6;
          }
          else {
            bVar3 = CellType(iVar13,(int)pSVar8);
            uVar14 = sMaterial[bVar3 & 0xf];
            if ((uVar14 == 0) || (uVar14 == 1)) {
              uVar4 = CellTeam(iVar13,(int)pSVar8);
              uVar14 = uVar14 | (uint)uVar4 << 0x10;
            }
          }
        } while (uVar14 == uVar6);
        ProcessStrip(iVar13,iVar13 + 1,(int)local_4,uVar6,unaff_ESI);
      }
      UpdateSlab(iVar13);
    }
    operator_delete__(xSlab);
    this_00 = &pPVar16->terrainStrips;
    if ((int)(pPVar16->terrainStrips)._Mylast - (int)(pPVar16->terrainStrips)._Myfirst >> 2 == 0) {
      _invalid_parameter_noinfo();
    }
    if (*(pPVar16->terrainStrips)._Myfirst != (Strip *)0x0) {
      std::vector<Strip_*,std::allocator<Strip_*>_>::operator[](this_00,0);
      ppSVar7 = std::vector<Strip_*,std::allocator<Strip_*>_>::operator[](this_00,0);
      this = freeStrips;
      local_4 = *ppSVar7;
      local_4->seqNo = 0;
      std::vector<Strip_*,std::allocator<Strip_*>_>::push_back(this,&local_4);
      ppSVar7 = (pPVar16->terrainStrips)._Mylast;
      if (((int)ppSVar7 - (int)(pPVar16->terrainStrips)._Myfirst & 0xfffffffcU) != 0) {
        (pPVar16->terrainStrips)._Mylast = ppSVar7 + -1;
      }
    }
    std::vector<Strip_*,std::allocator<Strip_*>_>::reserve
              (this_00,((int)(pPVar16->terrainStrips)._Mylast -
                        (int)(pPVar16->terrainStrips)._Myfirst >> 2) + 4 + stripListSize);
    iVar13 = stripListSize;
    pPVar16->x0 = iVar5;
    pPVar16->z0 = (int)pSVar10;
    if (0 < iVar13) {
      local_8 = 0;
      iVar13 = 0;
      do {
        psVar15 = (short *)((int)&stripList->x0 + local_8);
        pSVar8 = AllocStrip(true);
        local_4 = pSVar8;
        std::vector<Strip_*,std::allocator<Strip_*>_>::push_back(&pPVar16->terrainStrips,&local_4);
        pSVar8->x0 = (float)(int)*psVar15;
        pSVar8->x1 = (float)(int)psVar15[2];
        pSVar8->z0 = (float)(int)psVar15[1];
        local_4 = (Strip *)(int)psVar15[3];
        pSVar8->z1 = (float)(int)local_4;
        pSVar8->material = *(uint *)(psVar15 + 4) & 0xffff7fff;
        pSVar8->neighbor = -2;
        pSVar8->edge = '\0';
        iVar12 = (int)psVar15[1] - (int)pSVar10;
        if (iVar12 < (int)psVar15[3] - (int)pSVar10) {
          iVar11 = psVar15[2] - iVar5;
          iVar17 = iVar12 * 0x10 + 0x24 + (int)pPVar16;
          do {
            iVar9 = *psVar15 - iVar5;
            if (iVar9 < iVar11) {
              do {
                *(char *)(iVar17 + iVar9) = (char)iVar13;
                iVar9 = iVar9 + 1;
                iVar11 = psVar15[2] - iVar5;
              } while (iVar9 < iVar11);
            }
            iVar12 = iVar12 + 1;
            iVar17 = iVar17 + 0x10;
          } while (iVar12 < (int)psVar15[3] - (int)pSVar10);
        }
        iVar13 = iVar13 + 1;
        local_8 = local_8 + 0xc;
      } while (iVar13 < stripListSize);
    }
    stripListSize = 0;
    pPVar16->built = true;
  }
  return;
}
