/*
 * Entry: 004717c2
 * Name: KillCBQueue
 * Namespace: Global
 * Signature: void KillCBQueue(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl KillCBQueue(int param_1)

{
  _cb_queue *p_Var1;
  _cb_queue *unaff_ESI;
  
  if (q_list != (_cb_queue *)0x0) {
    p_Var1 = q_list;
    if (param_1 != 0) {
      p_Var1 = q_list->next;
    }
    while (p_Var1 != (_cb_queue *)0x0) {
      p_Var1 = DeleteCBQueueItem(unaff_ESI);
    }
  }
  q_list = (_cb_queue *)0x0;
  return;
}
