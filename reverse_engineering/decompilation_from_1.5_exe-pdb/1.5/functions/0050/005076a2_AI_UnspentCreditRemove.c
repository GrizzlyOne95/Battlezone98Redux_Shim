/*
 * Entry: 005076a2
 * Name: AI_UnspentCreditRemove
 * Namespace: Global
 * Signature: void AI_UnspentCreditRemove(int param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AI_UnspentCreditRemove(int param_1,int param_2)

{
  if (AI_map->team[param_1] != (tag_team *)0x0) {
    Debug_Assert((uint)(param_2 <= (AI_map->team[param_1]->aibuild).credit[0]),0x425,
                 ".\\Schedule\\Ai.cpp","credits <= the_team->aibuild.credit[0]");
    AIBuild_CreditSubtract(param_1,param_2);
  }
  return;
}
