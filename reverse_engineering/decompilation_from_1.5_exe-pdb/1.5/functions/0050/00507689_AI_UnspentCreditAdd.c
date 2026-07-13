/*
 * Entry: 00507689
 * Name: AI_UnspentCreditAdd
 * Namespace: Global
 * Signature: void AI_UnspentCreditAdd(int param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AI_UnspentCreditAdd(int param_1,int param_2)

{
  if (teamdata[param_1].aicontrol != '\0') {
    AIBuild_CreditAdd(param_1,param_2);
    return;
  }
  return;
}
