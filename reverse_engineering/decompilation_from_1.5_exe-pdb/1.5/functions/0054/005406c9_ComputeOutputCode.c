/*
 * Entry: 005406c9
 * Name: ComputeOutputCode
 * Namespace: Global
 * Signature: long ComputeOutputCode(long param_1, long param_2, PANE * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl ComputeOutputCode(long param_1,long param_2,PANE *param_3)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  
  uVar1 = param_1 - param_3->x0;
  uVar3 = (param_1 + -1) - param_3->x1;
  uVar2 = param_2 - param_3->y0;
  uVar4 = (param_2 + -1) - param_3->y1;
  return (((uint)CARRY4(uVar1,uVar1) * 2 + (uint)CARRY4(uVar3,uVar3)) * 2 +
         (uint)CARRY4(uVar2,uVar2)) * 2 + (uint)CARRY4(uVar4,uVar4) ^ 5;
}
