/*
 * Entry: 004716da
 * Name: DeleteCBQueueItem
 * Namespace: Global
 * Signature: _cb_queue * DeleteCBQueueItem(_cb_queue * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_cb_queue * __cdecl DeleteCBQueueItem(_cb_queue *param_1)

{
  _cb_queue *p_Var1;
  void *unaff_ESI;
  
  p_Var1 = *(_cb_queue **)((int)unaff_ESI + 0x20);
  if (*(_gas_object **)((int)unaff_ESI + 0x14) != (_gas_object *)0x0) {
    StopGASEvent(*(_gas_object **)((int)unaff_ESI + 0x14));
  }
  if (hDefaultHeap != (void *)0x0) {
    free(unaff_ESI);
  }
  return p_Var1;
}
