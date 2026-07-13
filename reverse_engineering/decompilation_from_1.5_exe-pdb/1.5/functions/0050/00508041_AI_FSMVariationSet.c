/*
 * Entry: 00508041
 * Name: AI_FSMVariationSet
 * Namespace: Global
 * Signature: void AI_FSMVariationSet(int param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AI_FSMVariationSet(int param_1,int param_2)

{
  Debug_Assert((uint)(-1 < param_2),0x805,".\\Schedule\\Ai.cpp","variation >= 0");
  Debug_Assert((uint)(param_2 < 3),0x806,".\\Schedule\\Ai.cpp","variation < AI_MAX_FSMS");
  fsm[param_1].variation = param_2;
  return;
}
