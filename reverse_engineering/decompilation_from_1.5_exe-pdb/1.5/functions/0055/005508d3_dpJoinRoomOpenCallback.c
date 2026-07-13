/*
 * Entry: 005508d3
 * Name: dpJoinRoomOpenCallback
 * Namespace: Global
 * Signature: int dpJoinRoomOpenCallback(dp_session_t * param_1, long * param_2, long param_3, void * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl dpJoinRoomOpenCallback(dp_session_t *param_1,long *param_2,long param_3,void *param_4)

{
  if (param_1 == (dp_session_t *)0x0) {
    SessionList::JoinLobby(&roomList);
  }
  else {
    chat_state = 6;
  }
  return 0;
}
