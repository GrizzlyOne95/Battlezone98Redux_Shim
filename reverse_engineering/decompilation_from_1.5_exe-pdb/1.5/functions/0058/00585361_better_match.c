/*
 * Entry: 00585361
 * Name: better_match
 * Namespace: Global
 * Signature: void better_match(lzo1y_999_swd_t * param_1, ulong * param_2, ulong * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl better_match(lzo1y_999_swd_t *param_1,ulong *param_2,ulong *param_3)

{
  uint uVar1;
  uint uVar2;
  int in_ECX;
  uint *in_EDX;
  uint *unaff_ESI;
  
  uVar2 = *unaff_ESI;
  if (uVar2 < 4) {
    return;
  }
  if (*in_EDX < 0x401) {
    return;
  }
  if ((((uVar2 < 4) || (0xf < uVar2)) || (uVar1 = *(uint *)(in_ECX + 0x28 + uVar2 * 4), uVar1 == 0))
     || (0x400 < uVar1)) {
    if (*in_EDX < 0x4001) {
      return;
    }
    if (uVar2 < 10) {
      return;
    }
    if (((uVar2 < 0x11) && (uVar1 = *(uint *)(in_ECX + 0x24 + uVar2 * 4), uVar1 != 0)) &&
       (uVar1 < 0x401)) {
      uVar2 = uVar2 - 2;
      goto LAB_005853c9;
    }
    if (uVar2 < 10) {
      return;
    }
    if (0x22 < uVar2) {
      return;
    }
    uVar1 = *(uint *)(in_ECX + 0x28 + uVar2 * 4);
    if (uVar1 == 0) {
      return;
    }
    if (0x4000 < uVar1) {
      return;
    }
  }
  uVar2 = uVar2 - 1;
LAB_005853c9:
  *unaff_ESI = uVar2;
  *in_EDX = *(uint *)(in_ECX + 0x2c + uVar2 * 4);
  return;
}
