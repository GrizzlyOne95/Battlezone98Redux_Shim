/*
 * Entry: 0055c1e1
 * Name: GamePlayerList::FormatItem
 * Namespace: GamePlayerList
 * Signature: void FormatItem(GamePlayerList * this, char * param_1, Player * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall GamePlayerList::FormatItem(GamePlayerList *this,char *param_1,Player *param_2)

{
  sprintf(param_1,"%s",param_2);
  return;
}
