/*
 * Entry: 004501c0
 * Name: MakeBetterNode
 * Namespace: Global
 * Signature: Strip * MakeBetterNode(float param_1, float param_2, Strip * param_3, Strip * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

Strip * __cdecl MakeBetterNode(float param_1,float param_2,Strip *param_3,Strip *param_4)

{
  float fVar1;
  float fVar2;
  Strip *in_EDX;
  Strip *extraout_EDX;
  Strip *pSVar3;
  Strip *unaff_ESI;
  float fVar4;
  
  fVar4 = materialCost[unaff_ESI->material & 0xff];
  if ((ushort)((ushort)((uint)unaff_ESI->material >> 0x10) & (ushort)_curPathingEnemies) != 0) {
    fVar4 = fVar4 + 2.0;
  }
  if (fVar4 == 99999.0) {
    return (Strip *)0x0;
  }
  fVar1 = in_EDX->x;
  fVar2 = in_EDX->z;
  in_EDX->x = param_1;
  in_EDX->z = param_2;
  fVar4 = ActualCost(unaff_ESI,in_EDX,fVar4);
  pSVar3 = extraout_EDX;
  if (extraout_EDX->g < fVar4 + unaff_ESI->g) {
    extraout_EDX->x = fVar1;
    extraout_EDX->z = fVar2;
    pSVar3 = (Strip *)0x0;
  }
  return pSVar3;
}
