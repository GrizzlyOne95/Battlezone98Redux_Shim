/*
 * Entry: 00508650
 * Name: AI_SpecialForcesClose
 * Namespace: Global
 * Signature: void AI_SpecialForcesClose(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AI_SpecialForcesClose(void)

{
  tagSPECIAL_FORCES_BODY *ptVar1;
  int iVar2;
  
  if (special_forces_initialised != 0) {
    iVar2 = 0;
    if (0 < special_forces_groups.count) {
      do {
        ptVar1 = C_Linked_List_Return_Data_By_Number(&special_forces_groups,iVar2);
        Debug_Assert((int)ptVar1,0x488,".\\Schedule\\Ai.cpp","sf");
        AI_SpecialForcesDelete(ptVar1);
        iVar2 = iVar2 + 1;
      } while (iVar2 < special_forces_groups.count);
    }
    C_Linked_List_Empty(&special_forces_groups);
    special_forces_initialised = 0;
    return;
  }
  tlog(1,"AI_SpecialForcesClose called without matching Open\n");
  return;
}
