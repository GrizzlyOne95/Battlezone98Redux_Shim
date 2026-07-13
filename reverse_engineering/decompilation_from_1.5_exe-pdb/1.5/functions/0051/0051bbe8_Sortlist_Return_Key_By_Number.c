/*
 * Entry: 0051bbe8
 * Name: Sortlist_Return_Key_By_Number
 * Namespace: Global
 * Signature: double Sortlist_Return_Key_By_Number(tag_sortlist * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

double __cdecl Sortlist_Return_Key_By_Number(tag_sortlist *param_1,int param_2)

{
  return param_1->key_list[param_2];
}
