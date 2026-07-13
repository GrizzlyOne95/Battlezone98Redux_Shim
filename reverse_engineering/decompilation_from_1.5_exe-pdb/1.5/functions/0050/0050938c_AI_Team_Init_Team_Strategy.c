/*
 * Entry: 0050938c
 * Name: AI_Team_Init_Team_Strategy
 * Namespace: Global
 * Signature: void AI_Team_Init_Team_Strategy(tag_strategy_map * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AI_Team_Init_Team_Strategy(tag_strategy_map *param_1,int param_2)

{
  tlog_gdm("AI_Team::Init_All_Teams_Strategies    Begins\n");
  AI_Team_Update_Squads(param_1,param_1->team[param_2]);
  tlog_gdm("AI_Team::Init_All_Teams_Strategies    Ends\n");
  return;
}
