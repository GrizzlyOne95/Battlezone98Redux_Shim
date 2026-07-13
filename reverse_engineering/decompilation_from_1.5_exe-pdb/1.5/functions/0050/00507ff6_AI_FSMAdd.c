/*
 * Entry: 00507ff6
 * Name: AI_FSMAdd
 * Namespace: Global
 * Signature: void AI_FSMAdd(int param_1, int param_2, char * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AI_FSMAdd(int param_1,int param_2,char *param_3)

{
  char *pcVar1;
  
  Debug_Assert((int)param_3,0x7f6,".\\Schedule\\Ai.cpp","filename");
  pcVar1 = _strdup(param_3);
  fsm[param_1].filename[param_2] = pcVar1;
  return;
}
