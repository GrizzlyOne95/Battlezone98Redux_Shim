/*
 * Entry: 0051bbf7
 * Name: Squad_Check_Squad_List_Valid_Body
 * Namespace: Global
 * Signature: int Squad_Check_Squad_List_Valid_Body(tag_c_linked_list * param_1, char * param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl Squad_Check_Squad_List_Valid_Body(tag_c_linked_list *param_1,char *param_2,int param_3)

{
  bool bVar1;
  void *pvVar2;
  void *pvVar3;
  int iVar4;
  int iVar5;
  
  iVar5 = 0;
  if (0 < param_1->count) {
    do {
      C_Linked_List_Return_Data_By_Number(param_1,iVar5);
      iVar5 = iVar5 + 1;
    } while (iVar5 < param_1->count);
  }
  do {
    bVar1 = true;
    iVar5 = 0;
    do {
      if (param_1->count <= iVar5) break;
      for (iVar4 = iVar5 + 1; (bVar1 && (iVar4 < param_1->count)); iVar4 = iVar4 + 1) {
        pvVar2 = C_Linked_List_Return_Data_By_Number(param_1,iVar5);
        pvVar3 = C_Linked_List_Return_Data_By_Number(param_1,iVar4);
        if (pvVar2 == pvVar3) {
          C_Linked_List_Remove_Data(param_1,pvVar2);
          bVar1 = false;
        }
      }
      iVar5 = iVar5 + 1;
    } while (bVar1);
    if (bVar1) {
      return 1;
    }
  } while( true );
}
