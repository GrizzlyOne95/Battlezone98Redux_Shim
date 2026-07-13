/*
 * Entry: 00583e3a
 * Name: better_match
 * Namespace: Global
 * Signature: void better_match(lzo1x_999_swd_t * param_1, ulong * param_2, ulong * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl better_match(lzo1x_999_swd_t *param_1,ulong *param_2,ulong *param_3)

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
  if (*in_EDX < 0x801) {
    return;
  }
  if ((((uVar2 < 4) || (9 < uVar2)) || (uVar1 = *(uint *)(in_ECX + 0x28 + uVar2 * 4), uVar1 == 0))
     || (0x800 < uVar1)) {
    if (*in_EDX < 0x4001) {
      return;
    }
    if (uVar2 < 10) {
      return;
    }
    if (((uVar2 < 0xb) && (uVar1 = *(uint *)(in_ECX + 0x24 + uVar2 * 4), uVar1 != 0)) &&
       (uVar1 < 0x801)) {
      uVar2 = uVar2 - 2;
      goto LAB_00583e9f;
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
LAB_00583e9f:
  *unaff_ESI = uVar2;
  *in_EDX = *(uint *)(in_ECX + 0x2c + uVar2 * 4);
  return;
}
