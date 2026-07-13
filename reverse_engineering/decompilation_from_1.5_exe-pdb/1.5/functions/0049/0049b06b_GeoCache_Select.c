/*
 * Entry: 0049b06b
 * Name: GeoCache_Select
 * Namespace: Global
 * Signature: int GeoCache_Select(_OBJ76 * param_1, long param_2, long param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GeoCache_Select(_OBJ76 *param_1,long param_2,long param_3)

{
  int iVar1;
  int in_EAX;
  _OBJ76 *in_ECX;
  _REP_INFO *p_Var2;
  int iVar3;
  
  iVar1 = (in_ECX->reps).repCount;
  iVar3 = 0;
  if (0 < iVar1) {
    p_Var2 = (in_ECX->reps).reps;
    do {
      if (p_Var2->repNum == (in_EAX << 0x10 | (uint)param_1)) {
        in_ECX->geom = p_Var2->geom;
        Texture_Purge(in_ECX);
        return 1;
      }
      iVar3 = iVar3 + 1;
      p_Var2 = p_Var2 + 1;
    } while (iVar3 < iVar1);
  }
  return 0;
}
