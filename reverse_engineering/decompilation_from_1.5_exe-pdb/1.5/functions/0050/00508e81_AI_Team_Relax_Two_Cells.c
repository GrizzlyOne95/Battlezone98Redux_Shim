/*
 * Entry: 00508e81
 * Name: AI_Team_Relax_Two_Cells
 * Namespace: Global
 * Signature: void AI_Team_Relax_Two_Cells(tag_team * param_1, Mapgrid_Goal * param_2, int param_3, int param_4, float param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
AI_Team_Relax_Two_Cells
          (tag_team *param_1,Mapgrid_Goal *param_2,int param_3,int param_4,float param_5)

{
  int extraout_EAX;
  
  if ((((-1 < param_3) && (-1 < param_4)) && (param_3 < (param_1->strategic_targets).grid_rows)) &&
     (param_4 < (param_1->strategic_targets).grid_columns)) {
    _ftol2_sse();
    param_2->new_threat = param_2->new_threat + extraout_EAX;
    if ((param_1->strategic_targets).max_threat < param_2->new_threat) {
      (param_1->strategic_targets).max_threat = param_2->new_threat;
    }
  }
  return;
}
