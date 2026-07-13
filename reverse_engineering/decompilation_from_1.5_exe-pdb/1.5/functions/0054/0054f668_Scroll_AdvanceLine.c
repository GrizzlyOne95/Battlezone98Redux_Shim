/*
 * Entry: 0054f668
 * Name: Scroll_AdvanceLine
 * Namespace: Global
 * Signature: void Scroll_AdvanceLine(SCROLL_REGION * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Scroll_AdvanceLine(SCROLL_REGION *param_1)

{
  uint uVar1;
  int in_ECX;
  uint uVar2;
  
  if ((*(byte *)(in_ECX + 0x60) & 8) != 0) {
    *(int *)(in_ECX + 0x20) = *(int *)(in_ECX + 0x20) + 1;
    return;
  }
  uVar1 = *(int *)(in_ECX + 0x10) + 5;
  uVar2 = (*(int *)(in_ECX + 0x20) + 1U) % uVar1;
  *(uint *)(in_ECX + 0x20) = uVar2;
  if (uVar2 == *(uint *)(in_ECX + 0x1c)) {
    *(uint *)(in_ECX + 0x1c) = (*(uint *)(in_ECX + 0x1c) + 1) % uVar1;
    if (3 < *(uint *)(in_ECX + 0x24)) {
      *(uint *)(in_ECX + 0x24) = *(uint *)(in_ECX + 0x24) - 4;
    }
  }
  *(int *)(in_ECX + 0x24) = *(int *)(in_ECX + 0x24) + 4;
  return;
}
