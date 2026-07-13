/*
 * Entry: 00508d48
 * Name: AI_Team_Trash_Regions_Of_Control
 * Namespace: Global
 * Signature: void AI_Team_Trash_Regions_Of_Control(tag_team * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AI_Team_Trash_Regions_Of_Control(tag_team *param_1)

{
  NR_Free_Imatrix((param_1->strategic_targets).base_location,0,
                  (param_1->strategic_targets).grid_rows,0,(param_1->strategic_targets).grid_columns
                 );
  NR_Free_Imatrix((param_1->strategic_targets).distance_from_base,0,
                  (param_1->strategic_targets).grid_rows,0,(param_1->strategic_targets).grid_columns
                 );
  NR_Free_Imatrix((param_1->strategic_targets).scouted,0,(param_1->strategic_targets).grid_rows,0,
                  (param_1->strategic_targets).grid_columns);
  NR_Free_Imatrix((param_1->strategic_targets).distance_from_scouted,0,
                  (param_1->strategic_targets).grid_rows,0,(param_1->strategic_targets).grid_columns
                 );
  return;
}
