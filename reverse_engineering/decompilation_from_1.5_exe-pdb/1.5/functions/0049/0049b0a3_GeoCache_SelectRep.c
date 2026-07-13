/*
 * Entry: 0049b0a3
 * Name: GeoCache_SelectRep
 * Namespace: Global
 * Signature: int GeoCache_SelectRep(_OBJ76 * param_1, long param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GeoCache_SelectRep(_OBJ76 *param_1,long param_2)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  long unaff_ESI;
  _OBJ76 *p_Var4;
  long unaff_EDI;
  
  uVar1 = (param_1->reps).repNum;
  p_Var4 = (_OBJ76 *)(uVar1 & 0xffff);
  uVar2 = param_2 << 0x10 | (uint)p_Var4;
  if (uVar2 != uVar1) {
    (param_1->reps).repNum = uVar2;
    iVar3 = GeoCache_Select(p_Var4,unaff_EDI,unaff_ESI);
    if ((iVar3 == 0) &&
       ((p_Var4 == (_OBJ76 *)0x1 ||
        (iVar3 = GeoCache_Select((_OBJ76 *)0x0,unaff_EDI,unaff_ESI), iVar3 == 0)))) {
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
