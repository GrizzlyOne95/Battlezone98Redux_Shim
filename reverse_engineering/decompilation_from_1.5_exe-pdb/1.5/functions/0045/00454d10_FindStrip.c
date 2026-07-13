/*
 * Entry: 00454d10
 * Name: FindStrip
 * Namespace: Global
 * Signature: Strip * FindStrip(VECTOR_3D * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Strip * __cdecl FindStrip(VECTOR_3D *param_1)

{
  float *in_EAX;
  int extraout_EAX;
  int extraout_EAX_00;
  int iVar1;
  uint uVar2;
  Strip **ppSVar3;
  int iVar4;
  int unaff_ESI;
  PathZone *pPVar5;
  int unaff_EDI;
  
  floor((double)(in_EAX[2] * Terrain.Grid_Scale));
  _ftol2_sse();
  floor((double)(*in_EAX * Terrain.Grid_Scale));
  _ftol2_sse();
  iVar4 = (int)((extraout_EAX - GridMinZ) + (extraout_EAX - GridMinZ >> 0x1f & 0xfU)) >> 4;
  iVar1 = (int)((extraout_EAX_00 - GridMinX) + (extraout_EAX_00 - GridMinX >> 0x1f & 0xfU)) >> 4;
  if ((((-1 < iVar4) && (iVar4 <= sBuiltZoneHeight)) && (-1 < iVar1)) && (iVar1 <= sBuiltZoneWidth))
  {
    pPVar5 = zones + zoneWidth * iVar4 + iVar1;
    if (pPVar5->built == false) {
      BuildZone(unaff_EDI,unaff_ESI);
    }
    iVar1 = pPVar5->x0;
    if (((iVar1 <= extraout_EAX_00) && (extraout_EAX_00 < iVar1 + 0x10)) &&
       ((iVar4 = pPVar5->z0, iVar4 <= extraout_EAX && (extraout_EAX < iVar4 + 0x10)))) {
      uVar2 = (uint)*(byte *)((int)pPVar5 +
                             extraout_EAX_00 + ((extraout_EAX - iVar4) * 0x10 - iVar1) + 0x24);
      if (uVar2 < (uint)((int)(pPVar5->terrainStrips)._Mylast -
                         (int)(pPVar5->terrainStrips)._Myfirst >> 2)) {
        ppSVar3 = std::vector<Strip_*,std::allocator<Strip_*>_>::operator[]
                            (&pPVar5->terrainStrips,uVar2);
        return *ppSVar3;
      }
    }
  }
  return (Strip *)0x0;
}
