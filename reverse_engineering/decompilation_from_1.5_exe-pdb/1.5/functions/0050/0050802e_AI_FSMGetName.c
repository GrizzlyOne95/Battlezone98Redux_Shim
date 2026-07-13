/*
 * Entry: 0050802e
 * Name: AI_FSMGetName
 * Namespace: Global
 * Signature: char * AI_FSMGetName(int param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

char * __cdecl AI_FSMGetName(int param_1,int param_2)

{
  return fsm[param_1].filename[param_2];
}
