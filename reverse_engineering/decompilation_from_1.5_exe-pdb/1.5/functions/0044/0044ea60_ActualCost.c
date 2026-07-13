/*
 * Entry: 0044ea60
 * Name: ActualCost
 * Namespace: Global
 * Signature: float ActualCost(Strip * param_1, Strip * param_2, float param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __cdecl ActualCost(Strip *param_1,Strip *param_2,float param_3)

{
  float fVar1;
  float fVar2;
  
  if ((param_1 != (Strip *)0x0) && (param_2 != (Strip *)0x0)) {
    fVar1 = param_2->x - param_1->x;
    fVar2 = param_2->z - param_1->z;
    fVar1 = SQRT(fVar2 * fVar2 + fVar1 * fVar1);
    if (randomizeCost) {
      Rand_Counter = Rand_Counter + 1U & 0xff;
      fVar1 = Pseudo_Rand_Number[Rand_Counter] * fVar1 * 0.2 + fVar1;
    }
    return fVar1 * param_3;
  }
  return 1e+30;
}
