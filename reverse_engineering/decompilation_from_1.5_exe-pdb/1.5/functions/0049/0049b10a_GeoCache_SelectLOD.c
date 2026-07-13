/*
 * Entry: 0049b10a
 * Name: GeoCache_SelectLOD
 * Namespace: Global
 * Signature: int GeoCache_SelectLOD(_OBJ76 * param_1, long param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GeoCache_SelectLOD(_OBJ76 *param_1,long param_2)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  long unaff_ESI;
  long unaff_EDI;
  
  uVar1 = (param_1->reps).repNum;
  uVar2 = ((int)uVar1 >> 0x10) << 0x10 | param_2;
  if (uVar2 != uVar1) {
    (param_1->reps).repNum = uVar2;
    iVar3 = GeoCache_Select((_OBJ76 *)param_2,unaff_EDI,unaff_ESI);
    if ((iVar3 == 0) &&
       ((param_2 == 1 || (iVar3 = GeoCache_Select((_OBJ76 *)0x0,unaff_EDI,unaff_ESI), iVar3 == 0))))
    {
      param_1->geom = (_GEOMETRY *)0x0;
      Texture_Purge(param_1);
      iVar3 = 0;
    }
    else {
      iVar3 = 1;
    }
    return iVar3;
  }
  return (uint)(param_1->geom != (_GEOMETRY *)0x0);
}
