/*
 * Entry: 00507f02
 * Name: AI_SquadCalculateWaits
 * Namespace: Global
 * Signature: void AI_SquadCalculateWaits(tag_squad * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AI_SquadCalculateWaits(tag_squad *param_1)

{
  void *pvVar1;
  int iVar2;
  int iVar3;
  int unaff_EDI;
  
  iVar3 = 0;
  if (0 < *(int *)(unaff_EDI + 0x14)) {
    do {
      pvVar1 = C_Linked_List_Return_Data_By_Number((tag_c_linked_list *)(unaff_EDI + 0xc),iVar3);
      Debug_Assert((int)pvVar1,0x752,".\\Schedule\\Ai.cpp","unit");
      iVar2 = *(int *)(unaff_EDI + 0x2c) - *(int *)((int)pvVar1 + 0x28);
      if (0 < iVar2) {
        *(ulong *)((int)pvVar1 + 0x4c) = unitcycles + iVar2;
        *(undefined4 *)((int)pvVar1 + 0x44) = 4;
      }
      iVar3 = iVar3 + 1;
      *(undefined1 *)((int)pvVar1 + 0x48) = 1;
    } while (iVar3 < *(int *)(unaff_EDI + 0x14));
  }
  return;
}
