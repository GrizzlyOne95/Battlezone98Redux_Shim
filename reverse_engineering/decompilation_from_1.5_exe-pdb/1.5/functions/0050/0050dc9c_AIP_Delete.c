/*
 * Entry: 0050dc9c
 * Name: AIP_Delete
 * Namespace: Global
 * Signature: void AIP_Delete(tagAIP_struct * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AIP_Delete(tagAIP_struct *param_1)

{
  Debug_Assert((int)param_1,0x340,".\\Schedule\\aip.cpp","the_AIP");
  tlog_gdm("AIP_Delete: Deleting aip\'s construction program\n");
  AIBuild_ConstructionProgramDelete(param_1->the_construction_program);
  free(param_1->budget);
  free(param_1->max_reserve);
  tlog_gdm("    Done\n");
  free(param_1);
  return;
}
