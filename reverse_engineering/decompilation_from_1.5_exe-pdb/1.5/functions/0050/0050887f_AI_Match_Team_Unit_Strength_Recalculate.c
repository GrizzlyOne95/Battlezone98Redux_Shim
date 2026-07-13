/*
 * Entry: 0050887f
 * Name: AI_Match_Team_Unit_Strength_Recalculate
 * Namespace: Global
 * Signature: void AI_Match_Team_Unit_Strength_Recalculate(tag_team * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AI_Match_Team_Unit_Strength_Recalculate(tag_team *param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = 0;
  do {
    iVar2 = iVar1 + 1;
    team_unit_type_strength[param_1->team_ID][iVar1] =
         param_1->AIP->unit_multiplier[iVar1] * unit_type_strength[iVar1];
    iVar1 = iVar2;
  } while (iVar2 < 100);
  return;
}
