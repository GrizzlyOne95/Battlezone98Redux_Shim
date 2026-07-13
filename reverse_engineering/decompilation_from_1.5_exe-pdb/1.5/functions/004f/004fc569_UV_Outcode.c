/*
 * Entry: 004fc569
 * Name: UV_Outcode
 * Namespace: Global
 * Signature: void UV_Outcode(long * param_1, long * param_2, POINT_3D * param_3, long param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl UV_Outcode(long *param_1,long *param_2,POINT_3D *param_3,long param_4)

{
  double dVar1;
  double dVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  
  uVar3 = 0xff;
  uVar5 = 0;
  do {
    dVar2 = (double)(param_3->Texel).u;
    dVar1 = (double)(param_3->Texel).v;
    param_3 = param_3 + 1;
    uVar4 = (((uint)(dVar2 < zero) * 2 + (uint)(dVar2 < one)) * 2 + (uint)(dVar1 < zero)) * 2 +
            (uint)(dVar1 < one) ^ 5;
    uVar3 = uVar3 & uVar4;
    uVar5 = uVar5 | uVar4;
    param_4 = param_4 + -1;
  } while (param_4 != 0);
  *param_1 = uVar3;
  *param_2 = uVar5;
  return;
}
