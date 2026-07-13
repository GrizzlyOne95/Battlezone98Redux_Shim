/*
 * Entry: 005077b2
 * Name: AI_SpecialForcesDelete
 * Namespace: Global
 * Signature: void AI_SpecialForcesDelete(tagSPECIAL_FORCES_BODY * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AI_SpecialForcesDelete(tagSPECIAL_FORCES_BODY *param_1)

{
  Debug_Assert((int)param_1,0x4cc,".\\Schedule\\Ai.cpp","sf");
  C_Linked_List_Empty(&param_1->units);
  free(param_1);
  return;
}
