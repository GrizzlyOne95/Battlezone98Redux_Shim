/*
 * Entry: 00558980
 * Name: GameSessionList::FormatItem
 * Namespace: GameSessionList
 * Signature: void FormatItem(GameSessionList * this, char * param_1, Session * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall GameSessionList::FormatItem(GameSessionList *this,char *param_1,Session *param_2)

{
  sprintf(param_1,"%c %c %s %d %d",(((param_2->dp_session).szPassword[0] == '\0') - 1 & 0x30) + 0x20
          ,(-(uint)(((param_2->dp_session).szUserField[0] & 0x80U) != 0) & 0x33) + 0x20,
          &(param_2->dp_session).field8_0x17,(int)(param_2->dp_session).field6_0x13.currentPlayers,
          (int)(param_2->dp_session).field5_0x11.maxPlayers);
  return;
}
