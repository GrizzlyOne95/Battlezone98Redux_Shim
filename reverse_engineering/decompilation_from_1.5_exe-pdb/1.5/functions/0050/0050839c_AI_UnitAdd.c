/*
 * Entry: 0050839c
 * Name: AI_UnitAdd
 * Namespace: Global
 * Signature: void AI_UnitAdd(tagUNIT * param_1, tagBUILDING * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AI_UnitAdd(tagUNIT *param_1,tagBUILDING *param_2)

{
  if (teamdata[param_1->team].aicontrol != '\0') {
    AIBuild_ConstructionEnd
              (AI_map->team[param_1->team]->team_ID,(uint)(param_1->type->prereq).prereqtype);
    AI_UnitAppeared(param_1);
  }
  return;
}
