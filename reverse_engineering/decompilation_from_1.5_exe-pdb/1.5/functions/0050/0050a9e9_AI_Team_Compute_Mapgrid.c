/*
 * Entry: 0050a9e9
 * Name: AI_Team_Compute_Mapgrid
 * Namespace: Global
 * Signature: void AI_Team_Compute_Mapgrid(tag_strategy_map * param_1, tag_team * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AI_Team_Compute_Mapgrid(tag_strategy_map *param_1,tag_team *param_2)

{
  AI_Team_Zero_Priorities(param_2);
  AI_Team_Compute_Enemy_Units(param_2,param_1);
  AI_Team_Compute_Houses(param_2,param_1);
  AI_Team_Compute_Threats(param_2,param_1);
  AI_Team_Compute_Other(param_1,param_2);
  AI_Team_Relax_Threats(param_2);
  AI_Team_Compute_Risky_Areas(param_2);
  AI_Team_Compute_Explored_Areas(param_2);
  AI_Team_Add_Mapgrid_Goals(param_2);
  return;
}
