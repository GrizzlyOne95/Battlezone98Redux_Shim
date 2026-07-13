/*
 * Entry: 004055bb
 * Name: Union
 * Namespace: Global
 * Signature: void Union(ushort * param_1, ushort param_2, ushort param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Union(ushort *param_1,ushort param_2,ushort param_3)

{
  ushort uVar1;
  ushort extraout_DX;
  ushort *unaff_ESI;
  
  Find(unaff_ESI,(ushort)param_1);
  uVar1 = Find(unaff_ESI,param_2);
  if (extraout_DX != uVar1) {
    if (extraout_DX < uVar1) {
      unaff_ESI[uVar1] = extraout_DX;
      return;
    }
    unaff_ESI[extraout_DX] = uVar1;
  }
  return;
}
