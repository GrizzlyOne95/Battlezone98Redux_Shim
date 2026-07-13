/*
 * Entry: 00508917
 * Name: AI_Match_Team_Init
 * Namespace: Global
 * Signature: void AI_Match_Team_Init(tag_team * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AI_Match_Team_Init(tag_team *param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = 0;
  do {
    iVar2 = iVar1 + 1;
    team_unit_type_strength[param_1->team_ID][iVar1] = 1.0;
    iVar1 = iVar2;
  } while (iVar2 < 100);
  return;
}
