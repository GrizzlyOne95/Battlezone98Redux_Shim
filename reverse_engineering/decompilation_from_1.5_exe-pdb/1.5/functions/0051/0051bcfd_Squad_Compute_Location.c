/*
 * Entry: 0051bcfd
 * Name: Squad_Compute_Location
 * Namespace: Global
 * Signature: void Squad_Compute_Location(tag_squad * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Squad_Compute_Location(tag_squad *param_1)

{
  int iVar1;
  void *pvVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  iVar1 = (param_1->my_units).count;
  param_1->x = -1;
  param_1->y = -1;
  iVar5 = 0;
  iVar3 = 0;
  if (iVar1 != 0) {
    iVar4 = 0;
    if (0 < iVar1) {
      do {
        pvVar2 = C_Linked_List_Return_Data_By_Number(&param_1->my_units,iVar4);
        iVar5 = iVar5 + *(int *)((int)pvVar2 + 0x14);
        iVar3 = iVar3 + *(int *)((int)pvVar2 + 0x18);
        iVar4 = iVar4 + 1;
      } while (iVar4 < (param_1->my_units).count);
    }
    iVar1 = (param_1->my_units).count;
    param_1->x = iVar5 / iVar1;
    param_1->y = iVar3 / iVar1;
  }
  return;
}
