/*
 * Entry: 0050af49
 * Name: AIBuild_ReservedAreaIsCellReserved
 * Namespace: Global
 * Signature: int AIBuild_ReservedAreaIsCellReserved(int param_1, int param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl AIBuild_ReservedAreaIsCellReserved(int param_1,int param_2,int param_3)

{
  RESERVED_AREA *pRVar1;
  int iVar2;
  int iVar3;
  int local_8;
  
  iVar2 = 0;
  pRVar1 = reserved_area[param_1];
  local_8 = 0;
  do {
    if ((((reserved_used[param_1][iVar2] != '\0') &&
         (iVar3 = (int)((RESERVED_AREA *)&pRVar1->x)->x, iVar3 <= param_2)) &&
        (pRVar1->y <= param_3)) &&
       ((param_2 < pRVar1->width + iVar3 && (param_3 < (int)pRVar1->height + (int)pRVar1->y)))) {
      local_8 = 1;
    }
    iVar2 = iVar2 + 1;
    pRVar1 = pRVar1 + 1;
  } while ((local_8 == 0) && (iVar2 < 0x20));
  return local_8;
}
