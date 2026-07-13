/*
 * Entry: 0050c2d8
 * Name: AIBuild_Close
 * Namespace: Global
 * Signature: void AIBuild_Close(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AIBuild_Close(void)

{
  tag_c_linked_list *ptVar1;
  void *_Memory;
  int iVar2;
  tag_c_linked_list **pptVar3;
  
  tlog_gdm("in RLD\n");
  pptVar3 = resource_list;
  do {
    ptVar1 = *pptVar3;
    iVar2 = 0;
    if (0 < ptVar1->count) {
      do {
        _Memory = C_Linked_List_Return_Data_By_Number(ptVar1,iVar2);
        tlog_gdm("RLD about to free resource %d node %d ptr %08x\n");
        free(_Memory);
        ptVar1 = *pptVar3;
        iVar2 = iVar2 + 1;
      } while (iVar2 < ptVar1->count);
    }
    tlog_gdm("About to free list resource %d\n");
    C_Linked_List_Delete(*pptVar3);
    pptVar3 = pptVar3 + 1;
  } while ((int)pptVar3 < 0xc27db8);
  tlog_gdm("leaving RLD\n");
  return;
}
