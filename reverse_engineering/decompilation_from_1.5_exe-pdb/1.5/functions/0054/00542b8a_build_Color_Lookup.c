/*
 * Entry: 00542b8a
 * Name: build_Color_Lookup
 * Namespace: Global
 * Signature: void build_Color_Lookup(ulong param_1, ulong * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl build_Color_Lookup(ulong param_1,ulong *param_2)

{
  byte bVar1;
  uint in_EAX;
  byte bVar2;
  uint uVar3;
  uint uVar4;
  undefined4 local_c;
  
  uVar4 = 0;
  bVar1 = 0;
  for (; (in_EAX & 1) == 0; in_EAX = in_EAX >> 1) {
    bVar1 = bVar1 + 1;
  }
  bVar2 = 0;
  for (; in_EAX != 0; in_EAX = in_EAX >> 1) {
    bVar2 = bVar2 + 1;
  }
  local_c = 0;
  uVar3 = 0;
  do {
    uVar4 = uVar4 + (1 << (bVar2 & 0x1f));
    *(int *)(param_1 + uVar3 * 4) = local_c << (bVar1 & 0x1f);
    if (0xff < uVar4) {
      uVar4 = uVar4 - 0x100;
      local_c = local_c + 1;
    }
    uVar3 = uVar3 + 1;
  } while (uVar3 < 0x100);
  return;
}
