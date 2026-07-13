/*
 * Entry: 00508c37
 * Name: AI_Team_Planning_Status_Reset
 * Namespace: Global
 * Signature: void AI_Team_Planning_Status_Reset(tag_team * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AI_Team_Planning_Status_Reset(tag_team *param_1)

{
  (param_1->strategic_targets).squad_update_done = 0;
  (param_1->strategic_targets).compute_mapgrid = 0;
  (param_1->strategic_targets).updated_resources = 0;
  return;
}
