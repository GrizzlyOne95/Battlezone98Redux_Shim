/*
 * Entry: 004717ee
 * Name: QueueCB
 * Namespace: Global
 * Signature: int QueueCB(char * param_1, _OBJ76 * param_2, long param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl QueueCB(char *param_1,_OBJ76 *param_2,long param_3)

{
  int iVar1;
  _cb_queue *_Dest;
  DWORD DVar2;
  _cb_queue *p_Var3;
  _gas_object *p_Var4;
  _cb_queue *unaff_ESI;
  
  if (NoMoreCB != 0) {
    return 0;
  }
  iVar1 = _stricmp(param_1,"STOPCBXX");
  if (iVar1 == 0) {
    NoMoreCB = 1;
    return 0;
  }
  iVar1 = IsObj76Destroyed(param_2);
  if (iVar1 != 0) {
    return 0;
  }
  if ((UserProfilePtr->audioControl).channels == '\0') {
    return 1;
  }
  if ((UserProfilePtr->audioControl).voice == '\0') {
    return 1;
  }
  if (q_list != (_cb_queue *)0x0) {
    if (param_3 == 5) {
      return 0;
    }
    if (param_3 == 6) {
      if (q_list->pri < 5) {
        return 0;
      }
    }
    else if ((param_3 == 1) || ((param_3 < 5 && (4 < q_list->pri)))) {
      KillCBQueue(0);
    }
  }
  _Dest = malloc(0x24);
  if (_Dest == (_cb_queue *)0x0) {
    return 0;
  }
  p_Var3 = _Dest;
  for (iVar1 = 9; iVar1 != 0; iVar1 = iVar1 + -1) {
    p_Var3->name[0] = '\0';
    p_Var3->name[1] = '\0';
    p_Var3->name[2] = '\0';
    p_Var3->name[3] = '\0';
    p_Var3 = (_cb_queue *)(p_Var3->name + 4);
  }
  strncpy(_Dest->name,param_1,0x10);
  _Dest->pri = param_3;
  _Dest->obj76 = param_2;
  DVar2 = Get_TimeNow();
  p_Var3 = q_list;
  _Dest->time = DVar2;
  if (p_Var3 != (_cb_queue *)0x0) {
    if (_Dest->pri != 2) {
      for (; p_Var3->next != (_cb_queue *)0x0; p_Var3 = p_Var3->next) {
      }
      p_Var3->next = _Dest;
      _Dest = (_cb_queue *)0x0;
      p_Var3 = q_list;
      goto LAB_004718f8;
    }
    p_Var3 = DeleteCBQueueItem(unaff_ESI);
    q_list = (_cb_queue *)0x0;
    _Dest->next = p_Var3;
  }
  do {
    p_Var4 = StartCB(_Dest);
    _Dest->go = p_Var4;
    p_Var3 = _Dest;
    if (p_Var4 != (_gas_object *)0x0) break;
    _Dest = DeleteCBQueueItem(unaff_ESI);
    p_Var3 = _Dest;
  } while (_Dest != (_cb_queue *)0x0);
LAB_004718f8:
  q_list = p_Var3;
  return (uint)(_Dest != (_cb_queue *)0x0);
}
