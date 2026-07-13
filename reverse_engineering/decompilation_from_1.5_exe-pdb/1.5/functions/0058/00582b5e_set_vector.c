/*
 * Entry: 00582b5e
 * Name: set_vector
 * Namespace: Global
 * Signature: void set_vector(uchar * param_1, ulong param_2, ulong param_3, ulong param_4, PVECTOR * param_5, ushort param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Type propagation algorithm not settling */

void __cdecl
set_vector(uchar *param_1,ulong param_2,ulong param_3,ulong param_4,PVECTOR *param_5,ushort param_6)

{
  uint uVar1;
  uchar *in_ECX;
  ushort in_DX;
  uint uVar2;
  
  uVar2 = 0;
  if (param_3 != 0) {
    do {
      uVar1 = 0;
      if (param_2 != 0) {
        do {
          if ((in_DX & 0x8000) == 0) {
            in_ECX[uVar1] = *(uchar *)(uVar1 + (uVar2 + (uint)in_DX * 4) * 4 + param_4);
          }
          else {
            in_ECX[uVar1] = (uchar)in_DX;
          }
          uVar1 = uVar1 + 1;
        } while (uVar1 < param_2);
      }
      in_ECX = in_ECX + (int)param_1;
      uVar2 = uVar2 + 1;
    } while (uVar2 < param_3);
  }
  return;
}
