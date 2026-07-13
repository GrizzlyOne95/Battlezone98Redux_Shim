/*
 * Entry: 00476761
 * Name: Compute_Outcode_Z
 * Namespace: Global
 * Signature: void Compute_Outcode_Z(long * param_1, long * param_2, POINT_3D * param_3, long param_4, float param_5, float param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
Compute_Outcode_Z(long *param_1,long *param_2,POINT_3D *param_3,long param_4,float param_5,
                 float param_6)

{
  float fVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  
  uVar2 = 0xff;
  uVar4 = 0;
  do {
    fVar1 = (param_3->Vector).z;
    param_3 = param_3 + 1;
    uVar3 = (uint)(fVar1 < param_5) * 2 + (uint)(fVar1 < param_6) ^ 1;
    uVar2 = uVar2 & uVar3;
    uVar4 = uVar4 | uVar3;
    param_4 = param_4 + -1;
  } while (param_4 != 0);
  *param_1 = uVar2;
  *param_2 = uVar4;
  return;
}
