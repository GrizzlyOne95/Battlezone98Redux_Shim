/*
 * Entry: 004dda93
 * Name: dpEnumPlayersCallbackSend
 * Namespace: Global
 * Signature: void dpEnumPlayersCallbackSend(ushort param_1, char * param_2, long param_3, void * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl dpEnumPlayersCallbackSend(ushort param_1,char *param_2,long param_3,void *param_4)

{
  int iVar1;
  undefined2 in_stack_00000006;
  
  if (param_1 != 0xfa01) {
    iVar1 = dpSend(*(undefined4 *)param_4,*(undefined2 *)((int)param_4 + 4),_param_1,
                   *(undefined4 *)((int)param_4 + 8),*(undefined4 *)((int)param_4 + 0xc),
                   *(undefined4 *)((int)param_4 + 0x10));
    if ((broadcastFull != false) || (broadcastFull = false, iVar1 == 3)) {
      broadcastFull = true;
    }
  }
  return;
}
