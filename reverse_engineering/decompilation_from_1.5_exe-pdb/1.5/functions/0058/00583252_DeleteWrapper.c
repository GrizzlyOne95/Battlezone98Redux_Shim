/*
 * Entry: 00583252
 * Name: DeleteWrapper
 * Namespace: Global
 * Signature: void DeleteWrapper(wrap_struct * * param_1, wrap_struct * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl DeleteWrapper(wrap_struct **param_1,wrap_struct *param_2)

{
  if (param_2->next != (wrap_struct *)0x0) {
    param_2->next->prev = param_2->prev;
  }
  if (param_2->prev == (wrap_struct *)0x0) {
    *param_1 = param_2->next;
  }
  else {
    param_2->prev->next = param_2->next;
  }
  free(param_2);
  return;
}
