/*
 * Entry: 0050afb5
 * Name: AIBuild_ReservedAreaIsAreaReserved
 * Namespace: Global
 * Signature: int AIBuild_ReservedAreaIsAreaReserved(int param_1, int param_2, int param_3, int param_4, int param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
AIBuild_ReservedAreaIsAreaReserved(int param_1,int param_2,int param_3,int param_4,int param_5)

{
  RESERVED_AREA *pRVar1;
  int iVar2;
  int local_c;
  int local_8;
  
  local_c = 0;
  local_8 = 0;
  pRVar1 = reserved_area[param_1];
  do {
    if ((((reserved_used[param_1][local_8] != '\0') &&
         (iVar2 = (int)((RESERVED_AREA *)&pRVar1->x)->x, iVar2 <= param_2 + -1 + param_4)) &&
        ((int)pRVar1->y <= param_3 + -1 + param_5)) &&
       ((param_2 < pRVar1->width + iVar2 && (param_3 < (int)pRVar1->height + (int)pRVar1->y)))) {
      local_c = 1;
    }
    local_8 = local_8 + 1;
    pRVar1 = pRVar1 + 1;
  } while ((local_c == 0) && (local_8 < 0x20));
  return local_c;
}
