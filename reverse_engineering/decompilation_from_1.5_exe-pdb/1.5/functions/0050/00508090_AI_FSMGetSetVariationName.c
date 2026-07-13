/*
 * Entry: 00508090
 * Name: AI_FSMGetSetVariationName
 * Namespace: Global
 * Signature: char * AI_FSMGetSetVariationName(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

char * __cdecl AI_FSMGetSetVariationName(int param_1)

{
  return fsm[param_1].filename[fsm[param_1].variation];
}
