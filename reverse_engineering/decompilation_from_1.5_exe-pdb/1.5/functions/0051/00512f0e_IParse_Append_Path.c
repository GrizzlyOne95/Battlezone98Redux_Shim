/*
 * Entry: 00512f0e
 * Name: IParse_Append_Path
 * Namespace: Global
 * Signature: void IParse_Append_Path(void * param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl IParse_Append_Path(void *param_1,char *param_2)

{
  char cVar1;
  char *pcVar2;
  int iVar3;
  void *pvVar4;
  char *pcVar5;
  int iVar6;
  
  pcVar5 = param_2;
  pcVar2 = param_2;
  do {
    cVar1 = *pcVar2;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  iVar3 = (int)pcVar2 - (int)(param_2 + 1);
  if (param_2[iVar3 + -1] != '\\') {
    iVar3 = iVar3 + 1;
    param_2 = (char *)0x1;
  }
  pvVar4 = calloc(1,iVar3 + 1);
  iVar6 = (int)pvVar4 - (int)pcVar5;
  do {
    cVar1 = *pcVar5;
    pcVar5[iVar6] = cVar1;
    pcVar5 = pcVar5 + 1;
  } while (cVar1 != '\0');
  if (param_2 != (char *)0x0) {
    ((undefined1 *)((int)pvVar4 + iVar3))[-1] = 0x5c;
    *(undefined1 *)((int)pvVar4 + iVar3) = 0;
  }
  C_Linked_List_Append_Data((tag_c_linked_list *)((int)param_1 + 0x10),pvVar4);
  return;
}
