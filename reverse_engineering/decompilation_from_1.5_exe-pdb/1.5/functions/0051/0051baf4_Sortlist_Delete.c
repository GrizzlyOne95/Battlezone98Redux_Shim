/*
 * Entry: 0051baf4
 * Name: Sortlist_Delete
 * Namespace: Global
 * Signature: void Sortlist_Delete(tag_sortlist * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Sortlist_Delete(tag_sortlist *param_1)

{
  free(param_1->data_list);
  free(param_1->key_list);
  free(param_1);
  return;
}
