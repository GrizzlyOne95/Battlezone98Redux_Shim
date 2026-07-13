/*
 * Entry: 00507737
 * Name: AI_SpecialForcesNew
 * Namespace: Global
 * Signature: tagSPECIAL_FORCES_BODY * AI_SpecialForcesNew(int param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

tagSPECIAL_FORCES_BODY * __cdecl AI_SpecialForcesNew(int param_1,int param_2)

{
  tagSPECIAL_FORCES_BODY *ptVar1;
  
  Debug_Assert(special_forces_initialised,0x4a7,".\\Schedule\\Ai.cpp","special_forces_initialised");
  ptVar1 = calloc(1,0x1c);
  Debug_Assert((int)ptVar1,0x4ab,".\\Schedule\\Ai.cpp","sf");
  if (param_2 == -1) {
    param_2 = Id_New();
  }
  else {
    Id_Claim(param_2);
  }
  ptVar1->team = param_1;
  ptVar1->id = param_2;
  C_Linked_List_Init(&ptVar1->units);
  C_Linked_List_Add_Data(&special_forces_groups,ptVar1);
  return ptVar1;
}
