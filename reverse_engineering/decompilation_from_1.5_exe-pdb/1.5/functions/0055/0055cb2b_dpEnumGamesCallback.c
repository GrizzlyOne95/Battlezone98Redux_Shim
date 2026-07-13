/*
 * Entry: 0055cb2b
 * Name: dpEnumGamesCallback
 * Namespace: Global
 * Signature: int dpEnumGamesCallback(dp_session_t * param_1, long * param_2, long param_3, void * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl dpEnumGamesCallback(dp_session_t *param_1,long *param_2,long param_3,void *param_4)

{
  GameSessionList *this;
  
  this = &gameList;
  if (param_1 == (dp_session_t *)0x0) {
    GameSessionList::EndEnum(&gameList);
    SessionList::EndEnum(&roomList);
    state = 0xc9;
  }
  else {
    if (((ushort)param_1->field7_0x15 & 0x10) != 0) {
      this = (GameSessionList *)&roomList;
    }
    SessionList::Enum((SessionList *)this,param_1);
  }
  return 0;
}
