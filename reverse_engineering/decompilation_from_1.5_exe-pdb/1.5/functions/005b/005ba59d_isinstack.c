/*
 * Entry: 005ba59d
 * Name: isinstack
 * Namespace: Global
 * Signature: int isinstack(CallInfo * param_1, lua_TValue * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl isinstack(CallInfo *param_1,lua_TValue *param_2)

{
  uint *in_EAX;
  CallInfo *pCVar1;
  
  pCVar1 = (CallInfo *)*in_EAX;
  while( true ) {
    if ((CallInfo *)in_EAX[2] <= pCVar1) {
      return 0;
    }
    if (param_1 == pCVar1) break;
    pCVar1 = (CallInfo *)&pCVar1->nresults;
  }
  return 1;
}
