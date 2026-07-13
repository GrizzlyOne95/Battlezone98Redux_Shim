/*
 * Entry: 0055cecf
 * Name: dpCreateRoomOpenCallback
 * Namespace: Global
 * Signature: int dpCreateRoomOpenCallback(dp_session_t * param_1, long * param_2, long param_3, void * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl dpCreateRoomOpenCallback(dp_session_t *param_1,long *param_2,long param_3,void *param_4)

{
  int iVar1;
  Chat *this;
  char *pcVar2;
  char *pcVar3;
  char local_108 [28];
  undefined1 local_ec [228];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  if (param_4 != (void *)0x0) {
    if (param_1 == (dp_session_t *)0x0) {
      SessionList::JoinLobby(param_4);
    }
    else {
      chat_state = 6;
      SessionList::CreateRoom(param_4,param_1);
      if ((param_1->dwUser1 & 2) != 0) {
        *(undefined4 *)((int)param_4 + 0x38) = 1;
        *(undefined2 *)((int)param_4 + 0x30) = 0;
        *(undefined4 *)((int)param_4 + 0x34) = 0x7fff;
        *(undefined1 *)((int)param_4 + 0x3d) = 1;
      }
      if (((ushort)param_1->field7_0x15 & 8) != 0) {
        pcVar2 = "<system> You are on server ";
        pcVar3 = local_108;
        for (iVar1 = 7; iVar1 != 0; iVar1 = iVar1 + -1) {
          *(undefined4 *)pcVar3 = *(undefined4 *)pcVar2;
          pcVar2 = pcVar2 + 4;
          pcVar3 = pcVar3 + 4;
        }
        memset(local_ec,0,0xe4);
        read_text_label("multi_message","system_server",local_108);
        Chat::Append(this,(char *)&chatRoom);
      }
    }
  }
  return 0;
}
