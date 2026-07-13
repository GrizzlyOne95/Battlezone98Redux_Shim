/*
 * Entry: 005587b6
 * Name: SessionList::FormatItem
 * Namespace: SessionList
 * Signature: void FormatItem(SessionList * this, char * param_1, Session * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall SessionList::FormatItem(SessionList *this,char *param_1,Session *param_2)

{
  sprintf(param_1,"%c %s %d %d",(((param_2->dp_session).szPassword[0] == '\0') - 1 & 0x30) + 0x20,
          &(param_2->dp_session).field8_0x17,(int)(param_2->dp_session).field6_0x13.currentPlayers,
          (int)(param_2->dp_session).field5_0x11.maxPlayers);
  return;
}
