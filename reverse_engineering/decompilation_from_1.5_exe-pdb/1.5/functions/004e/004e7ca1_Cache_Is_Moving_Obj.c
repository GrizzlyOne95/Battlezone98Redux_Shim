/*
 * Entry: 004e7ca1
 * Name: Cache_Is_Moving_Obj
 * Namespace: Global
 * Signature: int Cache_Is_Moving_Obj(_OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl Cache_Is_Moving_Obj(_OBJ76 *param_1)

{
  int in_ECX;
  uint uVar1;
  
  uVar1 = 0;
  while (*(int *)(in_ECX + 0xac) != *(int *)((int)Obj76_Moving_Objects_ID + uVar1)) {
    uVar1 = uVar1 + 4;
    if (0x13 < uVar1) {
      return 0;
    }
  }
  if ((*(int *)(in_ECX + 0xac) == 0x3f) && ((*(uint *)(in_ECX + 0x14) & 0x200000) == 0)) {
    return 0;
  }
  return 1;
}
