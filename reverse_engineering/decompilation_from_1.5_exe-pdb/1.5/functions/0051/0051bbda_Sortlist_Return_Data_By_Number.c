/*
 * Entry: 0051bbda
 * Name: Sortlist_Return_Data_By_Number
 * Namespace: Global
 * Signature: void * Sortlist_Return_Data_By_Number(tag_sortlist * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __cdecl Sortlist_Return_Data_By_Number(tag_sortlist *param_1,int param_2)

{
  return param_1->data_list[param_2];
}
