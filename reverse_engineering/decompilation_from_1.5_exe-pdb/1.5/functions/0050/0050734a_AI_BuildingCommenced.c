/*
 * Entry: 0050734a
 * Name: AI_BuildingCommenced
 * Namespace: Global
 * Signature: void AI_BuildingCommenced(tagBUILDING * param_1, tagUNIT * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AI_BuildingCommenced(tagBUILDING *param_1,tagUNIT *param_2)

{
  if (teamdata[param_1->team].aicontrol != '\0') {
    tlog_gdm("AI_BuildingCommenced Team %d Building %d\n");
    (param_1->ai).account = (param_2->ai).cc_account;
    (param_1->ai).refundable = (param_2->ai).cc_construct_cost;
  }
  return;
}
