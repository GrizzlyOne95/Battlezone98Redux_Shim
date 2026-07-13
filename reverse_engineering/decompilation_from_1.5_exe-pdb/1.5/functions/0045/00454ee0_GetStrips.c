/*
 * Entry: 00454ee0
 * Name: GetStrips
 * Namespace: Global
 * Signature: void GetStrips(float param_1, float param_2, float param_3, float param_4, int * param_5, Strip * * * param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
GetStrips(float param_1,float param_2,float param_3,float param_4,int *param_5,Strip ***param_6)

{
  int *piVar1;
  Strip **ppSVar2;
  Strip *pSVar3;
  longlong lVar4;
  uint uVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  int iVar10;
  int extraout_EAX;
  int extraout_EAX_00;
  int iVar11;
  int extraout_EAX_01;
  int extraout_EAX_02;
  int iVar12;
  int iVar13;
  Strip **ppSVar14;
  int iVar15;
  int unaff_ESI;
  int iVar16;
  Strip **ppSVar17;
  int unaff_EDI;
  PathZone *pPVar18;
  int local_14;
  
  ppSVar17 = getStrips;
  *param_5 = 0;
  *param_6 = ppSVar17;
  pathMem = pathMem + 0x3c;
  fVar6 = param_1 * Terrain.Grid_Scale;
  fVar7 = param_2 * Terrain.Grid_Scale;
  fVar8 = Terrain.Grid_Scale * param_3;
  fVar9 = Terrain.Grid_Scale * param_4;
  floor((double)fVar7);
  _ftol2_sse();
  iVar11 = GridMinZ;
  iVar16 = (int)((extraout_EAX - GridMinZ) + (extraout_EAX - GridMinZ >> 0x1f & 0xfU)) >> 4;
  floor((double)fVar9);
  _ftol2_sse();
  iVar11 = (extraout_EAX_00 - iVar11) + 0xf;
  iVar15 = (int)(iVar11 + (iVar11 >> 0x1f & 0xfU)) >> 4;
  floor((double)fVar6);
  _ftol2_sse();
  iVar11 = GridMinX;
  local_14 = (int)((extraout_EAX_01 - GridMinX) + (extraout_EAX_01 - GridMinX >> 0x1f & 0xfU)) >> 4;
  floor((double)fVar8);
  _ftol2_sse();
  iVar11 = (extraout_EAX_02 - iVar11) + 0xf;
  iVar11 = (int)(iVar11 + (iVar11 >> 0x1f & 0xfU)) >> 4;
  if ((((-1 < iVar15) && (-1 < iVar11)) && (iVar16 < zoneHeight)) && (local_14 < zoneWidth)) {
    if (iVar16 < 0) {
      iVar16 = 0;
    }
    if (local_14 < 0) {
      local_14 = 0;
    }
    if (zoneHeight < iVar15) {
      iVar15 = zoneHeight;
    }
    if (zoneWidth < iVar11) {
      iVar11 = zoneWidth;
    }
    for (; iVar10 = local_14, iVar16 < iVar15; iVar16 = iVar16 + 1) {
      for (; iVar10 < iVar11; iVar10 = iVar10 + 1) {
        if (iVar10 < 0) {
          iVar13 = 0;
        }
        else {
          iVar13 = sBuiltZoneWidth;
          if (iVar10 <= sBuiltZoneWidth) {
            iVar13 = iVar10;
          }
        }
        iVar12 = Clamp(iVar16,0,sBuiltZoneHeight);
        pPVar18 = zones + iVar12 * zoneWidth + iVar13;
        if (pPVar18->built == false) {
          BuildZone(unaff_EDI,unaff_ESI);
        }
        ppSVar17 = (pPVar18->terrainStrips)._Myfirst;
        if ((pPVar18->terrainStrips)._Mylast < ppSVar17) {
          _invalid_parameter_noinfo();
        }
        piVar1 = (int *)(pPVar18->terrainStrips)._padding_;
        while( true ) {
          ppSVar2 = (pPVar18->terrainStrips)._Mylast;
          if (ppSVar2 < (pPVar18->terrainStrips)._Myfirst) {
            _invalid_parameter_noinfo();
          }
          if ((piVar1 == (int *)0x0) || (piVar1 != (int *)(pPVar18->terrainStrips)._padding_)) {
            _invalid_parameter_noinfo();
          }
          if (ppSVar17 == ppSVar2) break;
          if (piVar1 == (int *)0x0) {
            _invalid_parameter_noinfo();
            iVar13 = 0;
          }
          else {
            iVar13 = *piVar1;
          }
          if (*(Strip ***)(iVar13 + 0x10) <= ppSVar17) {
            _invalid_parameter_noinfo();
          }
          pSVar3 = *ppSVar17;
          if (((fVar6 < pSVar3->x1) && (fVar8 < pSVar3->x0 == (fVar8 == pSVar3->x0))) &&
             ((fVar7 < pSVar3->z1 && (fVar9 < pSVar3->z0 == (fVar9 == pSVar3->z0))))) {
            if (*param_5 == maxStrips) {
              if (maxStrips == 0) {
                getStrips = operator_new__(0x80);
                maxStrips = 0x20;
              }
              else {
                uVar5 = maxStrips * 2;
                lVar4 = (ulonglong)uVar5 * 4;
                ppSVar14 = operator_new__(-(uint)((int)((ulonglong)lVar4 >> 0x20) != 0) |
                                          (uint)lVar4);
                ppSVar2 = getStrips;
                memcpy(ppSVar14,getStrips,maxStrips * 4);
                operator_delete__(ppSVar2);
                maxStrips = uVar5;
                getStrips = ppSVar14;
              }
            }
            getStrips[*param_5] = pSVar3;
            *param_5 = *param_5 + 1;
          }
          if (piVar1 == (int *)0x0) {
            _invalid_parameter_noinfo();
            iVar13 = 0;
          }
          else {
            iVar13 = *piVar1;
          }
          if (*(Strip ***)(iVar13 + 0x10) <= ppSVar17) {
            _invalid_parameter_noinfo();
          }
          ppSVar17 = ppSVar17 + 1;
        }
      }
    }
    *param_6 = getStrips;
  }
  pathMem = pathMem + -0x3c;
  return;
}
