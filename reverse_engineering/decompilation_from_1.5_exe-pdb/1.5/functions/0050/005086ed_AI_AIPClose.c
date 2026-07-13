/*
 * Entry: 005086ed
 * Name: AI_AIPClose
 * Namespace: Global
 * Signature: void AI_AIPClose(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AI_AIPClose(void)

{
  tagAIP_struct *ptVar1;
  int iVar2;
  
  tlog_gdm("AIPClose BEGINS\n");
  if (aip_initialised == 0) {
    tlog(1,"AI_AIPClose called without matching Init\n");
  }
  else {
    iVar2 = 0;
    if (0 < aip_list.count) {
      do {
        ptVar1 = C_Linked_List_Return_Data_By_Number(&aip_list,iVar2);
        Debug_Assert((int)ptVar1,0x698,".\\Schedule\\Ai.cpp","aip");
        tlog_gdm("   deleting aip #%08x\n");
        AIP_Delete(ptVar1);
        iVar2 = iVar2 + 1;
      } while (iVar2 < aip_list.count);
    }
  }
  aip_initialised = 0;
  tlog_gdm("freeing list of pointers to aip\'s\n");
  C_Linked_List_Empty(&aip_list);
  tlog_gdm("AIPClose ENDS\n");
  AI_FSMClose();
  return;
}
