/*
 * Entry: 00508577
 * Name: AI_SpentCreditSpend
 * Namespace: Global
 * Signature: void AI_SpentCreditSpend(int param_1, int param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AI_SpentCreditSpend(int param_1,int param_2,int param_3)

{
  int *piVar1;
  tag_team *ptVar2;
  
  ptVar2 = AI_map->team[param_1];
  Debug_Assert((int)ptVar2,0x37e,".\\Schedule\\Ai.cpp","the_team");
  Debug_Assert((uint)(param_3 <= (ptVar2->aibuild).credit[0]),0x37f,".\\Schedule\\Ai.cpp",
               "the_team->aibuild.credit[0] >= credits");
  Debug_Assert((uint)(-1 < param_2),0x380,".\\Schedule\\Ai.cpp","account >= 0");
  Debug_Assert((uint)(param_2 < 0x20),0x381,".\\Schedule\\Ai.cpp","account < AIBUILD_MAX_ACCOUNTS");
  Debug_Assert((uint)(-1 < param_1),0x382,".\\Schedule\\Ai.cpp","team >= 0");
  Debug_Assert((uint)(param_1 < 0x10),899,".\\Schedule\\Ai.cpp","team < TEAM_MAXTEAMS");
  if (param_2 == 0) {
    AI_UnspentCreditRemove(ptVar2->team_ID,param_3);
  }
  else {
    piVar1 = (ptVar2->aibuild).credit + param_2;
    *piVar1 = *piVar1 - param_3;
    piVar1 = (ptVar2->aibuild).credit;
    *piVar1 = *piVar1 - param_3;
  }
  return;
}
