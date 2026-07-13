/*
 * Entry: 0047191b
 * Name: DeadMenDontUseCBs
 * Namespace: Global
 * Signature: void DeadMenDontUseCBs(_OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl DeadMenDontUseCBs(_OBJ76 *param_1)

{
  _cb_queue *p_Var1;
  _cb_queue *p_Var2;
  _cb_queue *p_Var3;
  _cb_queue *unaff_EBX;
  _cb_queue *p_Var4;
  
  p_Var3 = q_list;
  p_Var2 = q_list;
  p_Var4 = q_list;
  while (p_Var1 = p_Var2, p_Var1 != (_cb_queue *)0x0) {
    if (p_Var1->obj76 == param_1) {
      if (p_Var1 == p_Var3) {
        QueueCB("cmike.wav",param_1,2);
        p_Var4 = q_list;
      }
      else {
        p_Var3 = DeleteCBQueueItem(unaff_EBX);
        p_Var4->next = p_Var3;
      }
      p_Var3 = q_list;
      if (p_Var4 == (_cb_queue *)0x0) {
        p_Var2 = (_cb_queue *)0x0;
      }
      else {
        p_Var2 = p_Var4->next;
      }
    }
    else {
      p_Var2 = p_Var1->next;
      p_Var4 = p_Var1;
    }
  }
  return;
}
