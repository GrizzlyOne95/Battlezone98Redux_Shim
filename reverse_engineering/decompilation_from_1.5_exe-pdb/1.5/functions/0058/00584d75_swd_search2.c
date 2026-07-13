/*
 * Entry: 00584d75
 * Name: swd_search2
 * Namespace: Global
 * Signature: int swd_search2(lzo1y_999_swd_t * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl swd_search2(lzo1y_999_swd_t *param_1)

{
  int in_EAX;
  uint uVar1;
  
  uVar1 = (uint)*(ushort *)
                 (in_EAX + 0x4f168 +
                 (uint)*(ushort *)(*(int *)(in_EAX + 0x154) + 0x16c + in_EAX) * 2);
  if (uVar1 == 0xffff) {
    return 0;
  }
  if (*(int *)(in_EAX + 0xc4) == 0) {
    *(int *)(in_EAX + 0xc4) = uVar1 + 1;
  }
  if (*(uint *)(in_EAX + 0x1c) < 2) {
    *(undefined4 *)(in_EAX + 0x1c) = 2;
    *(uint *)(in_EAX + 0xb8) = uVar1;
  }
  return 1;
}
