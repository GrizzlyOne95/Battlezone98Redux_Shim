/*
 * Entry: 0047170d
 * Name: NextCBInQueue
 * Namespace: Global
 * Signature: int NextCBInQueue(_gas_object * param_1, long param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl NextCBInQueue(_gas_object *param_1,long param_2)

{
  _cb_queue *p_Var1;
  int iVar2;
  _gas_object *p_Var3;
  _cb_queue *unaff_ESI;
  
  if (q_list != (_cb_queue *)0x0) {
    do {
      do {
        p_Var1 = DeleteCBQueueItem(unaff_ESI);
        if (p_Var1 == (_cb_queue *)0x0) {
          q_list = p_Var1;
          return 0;
        }
        q_list = p_Var1;
        iVar2 = IsObj76Destroyed(p_Var1->obj76);
      } while (iVar2 != 0);
      p_Var3 = StartCB(p_Var1);
      q_list->go = p_Var3;
    } while (p_Var3 == (_gas_object *)0x0);
  }
  return 0;
}
