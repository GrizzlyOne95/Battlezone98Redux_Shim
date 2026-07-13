/*
 * Entry: 0050b0a1
 * Name: AIBuild_ResourceListOverlayIteration
 * Namespace: Global
 * Signature: void AIBuild_ResourceListOverlayIteration(tagOVERLAY * param_1, void * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AIBuild_ResourceListOverlayIteration(tagOVERLAY *param_1,void *param_2)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  
  iVar1 = param_1->type;
  iVar3 = 0;
  if (-1 < iVar1) {
    if ((char)overlaytypes[iVar1].field_0x1 < '\x01') {
      if (*(char *)(overlaytypes + iVar1) < '\x01') {
        return;
      }
      iVar3 = 1;
    }
    piVar2 = calloc(1,8);
    *piVar2 = param_1->tilecentrex;
    piVar2[1] = param_1->tilecentrey;
    C_Linked_List_Add_Data(resource_list[iVar3],piVar2);
    tlog_gdm("resource #%d found at (%d, %d) id number %d type %d addr %08x\n");
  }
  return;
}
