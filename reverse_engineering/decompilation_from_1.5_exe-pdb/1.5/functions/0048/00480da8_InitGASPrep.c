/*
 * Entry: 00480da8
 * Name: InitGASPrep
 * Namespace: Global
 * Signature: void InitGASPrep(GAS_PREP_INFO * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl InitGASPrep(GAS_PREP_INFO *param_1)

{
  param_1->loopMode = 0;
  param_1->random = -1;
  param_1->id = 0x30534147;
  param_1->pri = 0x32;
  param_1->maxCopies = 4;
  param_1->volume = 100;
  param_1->sampleRate = 0x2b11;
  return;
}
