/*
 * Entry: 004055fa
 * Name: InsertUnique
 * Namespace: Global
 * Signature: void InsertUnique(ushort * param_1, uint * param_2, ushort param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl InsertUnique(ushort *param_1,uint *param_2,ushort param_3)

{
  uint uVar1;
  uint uVar2;
  uint *in_ECX;
  ushort in_DX;
  ushort uVar3;
  int unaff_ESI;
  
  uVar1 = *in_ECX;
  uVar2 = 0;
  if (uVar1 != 0) {
    do {
      uVar3 = *(ushort *)(unaff_ESI + uVar2 * 2);
      if (in_DX == uVar3) {
        return;
      }
    } while ((uVar3 <= in_DX) && (uVar2 = uVar2 + 1, uVar2 < uVar1));
  }
  uVar3 = in_DX;
  if (uVar2 < uVar1) {
    do {
      in_DX = *(ushort *)(unaff_ESI + uVar2 * 2);
      *(ushort *)(unaff_ESI + uVar2 * 2) = uVar3;
      uVar2 = uVar2 + 1;
      uVar3 = in_DX;
    } while (uVar2 < *in_ECX);
  }
  *(ushort *)(unaff_ESI + *in_ECX * 2) = in_DX;
  *in_ECX = *in_ECX + 1;
  return;
}
