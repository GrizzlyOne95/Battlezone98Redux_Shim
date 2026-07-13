/*
 * Entry: 00454180
 * Name: GetZone
 * Namespace: Global
 * Signature: PathZone * GetZone(float param_1, float param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

PathZone * __cdecl GetZone(float param_1,float param_2)

{
  int extraout_EAX;
  int extraout_EAX_00;
  int iVar1;
  int iVar2;
  int unaff_ESI;
  PathZone *pPVar3;
  int unaff_EDI;
  
  floor((double)param_1);
  _ftol2_sse();
  floor((double)param_2);
  _ftol2_sse();
  if ((((GridMinX <= extraout_EAX) && (extraout_EAX < GridMaxX)) && (GridMinZ <= extraout_EAX_00))
     && (extraout_EAX_00 < GridMaxZ)) {
    iVar2 = (int)((extraout_EAX_00 - GridMinZ) + (extraout_EAX_00 - GridMinZ >> 0x1f & 0xfU)) >> 4;
    iVar1 = (int)((extraout_EAX - GridMinX) + (extraout_EAX - GridMinX >> 0x1f & 0xfU)) >> 4;
    if (((-1 < iVar2) && (iVar2 <= sBuiltZoneHeight)) &&
       ((-1 < iVar1 && (iVar1 <= sBuiltZoneWidth)))) {
      pPVar3 = zones + zoneWidth * iVar2 + iVar1;
      if (pPVar3->built == false) {
        BuildZone(unaff_EDI,unaff_ESI);
      }
      return pPVar3;
    }
  }
  return (PathZone *)0x0;
}
