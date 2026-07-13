/*
 * Entry: 00509133
 * Name: AI_Team_Compute_Explored_Areas
 * Namespace: Global
 * Signature: void AI_Team_Compute_Explored_Areas(tag_team * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AI_Team_Compute_Explored_Areas(tag_team *param_1)

{
  Grassfire_Xform((param_1->strategic_targets).scouted,
                  (param_1->strategic_targets).distance_from_scouted,1,0,0,8,
                  (param_1->strategic_targets).grid_rows,(param_1->strategic_targets).grid_columns);
  return;
}
