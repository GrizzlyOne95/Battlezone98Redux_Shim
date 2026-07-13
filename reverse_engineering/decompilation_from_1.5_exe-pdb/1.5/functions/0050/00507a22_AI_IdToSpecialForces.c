/*
 * Entry: 00507a22
 * Name: AI_IdToSpecialForces
 * Namespace: Global
 * Signature: tagSPECIAL_FORCES_BODY * AI_IdToSpecialForces(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

tagSPECIAL_FORCES_BODY * __cdecl AI_IdToSpecialForces(int param_1)

{
  tagSPECIAL_FORCES_BODY *ptVar1;
  int iVar2;
  tagSPECIAL_FORCES_BODY *ptVar3;
  
  Debug_Assert(special_forces_initialised,0x5a7,".\\Schedule\\Ai.cpp","special_forces_initialised");
  iVar2 = 0;
  ptVar3 = (tagSPECIAL_FORCES_BODY *)0x0;
  if (0 < special_forces_groups.count) {
    do {
      if (ptVar3 != (tagSPECIAL_FORCES_BODY *)0x0) {
        return ptVar3;
      }
      ptVar1 = C_Linked_List_Return_Data_By_Number(&special_forces_groups,iVar2);
      Debug_Assert((int)ptVar1,0x5b2,".\\Schedule\\Ai.cpp","sf");
      if (ptVar1->id == param_1) {
        ptVar3 = ptVar1;
      }
      iVar2 = iVar2 + 1;
    } while (iVar2 < special_forces_groups.count);
  }
  return ptVar3;
}
