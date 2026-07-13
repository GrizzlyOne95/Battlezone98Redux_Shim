/*
 * Entry: 00558501
 * Name: ServerList::FormatItem
 * Namespace: ServerList
 * Signature: void FormatItem(ServerList * this, char * param_1, Server * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ServerList::FormatItem(ServerList *this,char *param_1,Server *param_2)

{
  sprintf(param_1,"%s   %ld ms",param_2,param_2->avg_ms);
  return;
}
