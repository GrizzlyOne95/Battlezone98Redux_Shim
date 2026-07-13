/*
 * Entry: 00583df9
 * Name: min_gain
 * Namespace: Global
 * Signature: ulong min_gain(ulong param_1, ulong param_2, ulong param_3, ulong param_4, ulong param_5, ulong param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ulong __cdecl
min_gain(ulong param_1,ulong param_2,ulong param_3,ulong param_4,ulong param_5,ulong param_6)

{
  uint uVar1;
  int iVar2;
  ulong uVar3;
  int in_ECX;
  int in_EDX;
  int unaff_ESI;
  
  if (param_1 < 4) {
    uVar1 = -(uint)(3 < param_2) & 2;
  }
  else {
    iVar2 = unaff_ESI;
    if (0x12 < param_1) goto LAB_00583e23;
    uVar1 = (uint)(0x12 < param_2);
  }
  iVar2 = uVar1 + unaff_ESI;
LAB_00583e23:
  uVar3 = iVar2 + (in_ECX - param_3) * 2;
  if (in_EDX != 0) {
    uVar3 = uVar3 + (in_EDX - unaff_ESI) * 2;
  }
  if ((int)uVar3 < 0) {
    uVar3 = 0;
  }
  return uVar3;
}
