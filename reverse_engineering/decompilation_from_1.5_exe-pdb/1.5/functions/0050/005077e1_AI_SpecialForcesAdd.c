/*
 * Entry: 005077e1
 * Name: AI_SpecialForcesAdd
 * Namespace: Global
 * Signature: void AI_SpecialForcesAdd(tagSPECIAL_FORCES_BODY * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AI_SpecialForcesAdd(tagSPECIAL_FORCES_BODY *param_1,int param_2)

{
  Debug_Assert(special_forces_initialised,0x4dd,".\\Schedule\\Ai.cpp","special_forces_initialised");
  Debug_Assert((int)param_1,0x4de,".\\Schedule\\Ai.cpp","sf");
  C_Linked_List_Add_Data(&param_1->units,(void *)param_2);
  return;
}
