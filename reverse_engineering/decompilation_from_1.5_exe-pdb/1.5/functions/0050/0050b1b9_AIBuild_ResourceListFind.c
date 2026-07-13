/*
 * Entry: 0050b1b9
 * Name: AIBuild_ResourceListFind
 * Namespace: Global
 * Signature: int AIBuild_ResourceListFind(int param_1, int param_2, int * param_3, int * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl AIBuild_ResourceListFind(int param_1,int param_2,int *param_3,int *param_4)

{
  int *piVar1;
  
  piVar1 = C_Linked_List_Return_Data_By_Number(resource_list[param_1],param_2);
  if (piVar1 == (int *)0x0) {
    return 0;
  }
  *param_3 = *piVar1;
  *param_4 = piVar1[1];
  return 1;
}
