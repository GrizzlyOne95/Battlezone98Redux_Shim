/*
 * Entry: 00540c23
 * Name: Compute_Outcode
 * Namespace: Global
 * Signature: void Compute_Outcode(long * param_1, long * param_2, POINT_3D * param_3, long param_4, CAMERA * param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
Compute_Outcode(long *param_1,long *param_2,POINT_3D *param_3,long param_4,CAMERA *param_5)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  
  uVar3 = 0xff;
  uVar5 = 0;
  do {
    fVar1 = (param_3->Vector).x;
    fVar2 = (param_3->Vector).y;
    param_3 = param_3 + 1;
    uVar4 = (((uint)(fVar1 < param_5->Left) * 2 + (uint)(fVar1 < param_5->Right)) * 2 +
            (uint)(fVar2 < param_5->Bottom)) * 2 + (uint)(fVar2 < param_5->Top) ^ 5;
    uVar3 = uVar3 & uVar4;
    uVar5 = uVar5 | uVar4;
    param_4 = param_4 + -1;
  } while (param_4 != 0);
  *param_1 = uVar3;
  *param_2 = uVar5;
  return;
}
