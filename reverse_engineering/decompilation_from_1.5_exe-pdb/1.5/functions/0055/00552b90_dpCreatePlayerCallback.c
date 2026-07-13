/*
 * Entry: 00552b90
 * Name: dpCreatePlayerCallback
 * Namespace: Global
 * Signature: void dpCreatePlayerCallback(ushort param_1, char * param_2, long param_3, void * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl dpCreatePlayerCallback(ushort param_1,char *param_2,long param_3,void *param_4)

{
  char *pcVar1;
  undefined2 in_stack_00000006;
  
  Net::myPlayerID = param_1;
  chat_state = 8;
  if (param_1 == 0xfa01) {
    SessionList::JoinLobby(&roomList);
  }
  else {
    pcVar1 = playerInfo->packt;
    if (pcVar1 != (char *)0x0) {
      dpSetPlayerData(Net::dp,_param_1,0xe,pcVar1,*(undefined4 *)pcVar1,0);
    }
  }
  return;
}
