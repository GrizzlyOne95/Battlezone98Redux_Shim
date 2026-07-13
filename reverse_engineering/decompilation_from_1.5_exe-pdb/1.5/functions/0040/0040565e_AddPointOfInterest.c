/*
 * Entry: 0040565e
 * Name: AddPointOfInterest
 * Namespace: Global
 * Signature: void AddPointOfInterest(float param_1, float param_2, ushort * param_3, ushort * param_4, ushort * param_5, uint * param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
AddPointOfInterest(float param_1,float param_2,ushort *param_3,ushort *param_4,ushort *param_5,
                  uint *param_6)

{
  uint uVar1;
  ushort uVar2;
  int extraout_EAX;
  int extraout_EAX_00;
  int iVar3;
  uint uVar4;
  ushort uVar5;
  int unaff_EBX;
  uint *unaff_ESI;
  int iVar6;
  
  floor((double)(Terrain.Grid_Scale * param_2));
  _ftol2_sse();
  iVar6 = extraout_EAX - GridMinZ;
  if ((-1 < iVar6) && (iVar6 < GridMaxZ - GridMinZ)) {
    floor((double)(Terrain.Grid_Scale * param_1));
    _ftol2_sse();
    iVar3 = extraout_EAX_00 - GridMinX;
    if ((-1 < iVar3) &&
       ((iVar3 < GridMaxX - GridMinX && (param_3[(GridMaxX - GridMinX) * iVar6 + iVar3] != 0)))) {
      uVar2 = Find(param_4,param_3[(GridMaxX - GridMinX) * iVar6 + iVar3]);
      uVar1 = *unaff_ESI;
      uVar4 = 0;
      if (uVar1 != 0) {
        do {
          uVar5 = *(ushort *)(unaff_EBX + uVar4 * 2);
          if (uVar2 == uVar5) {
            return;
          }
        } while ((uVar5 <= uVar2) && (uVar4 = uVar4 + 1, uVar4 < uVar1));
      }
      uVar5 = uVar2;
      if (uVar4 < uVar1) {
        do {
          uVar2 = *(ushort *)(unaff_EBX + uVar4 * 2);
          *(ushort *)(unaff_EBX + uVar4 * 2) = uVar5;
          uVar4 = uVar4 + 1;
          uVar5 = uVar2;
        } while (uVar4 < *unaff_ESI);
      }
      *(ushort *)(unaff_EBX + *unaff_ESI * 2) = uVar2;
      *unaff_ESI = *unaff_ESI + 1;
    }
  }
  return;
}
