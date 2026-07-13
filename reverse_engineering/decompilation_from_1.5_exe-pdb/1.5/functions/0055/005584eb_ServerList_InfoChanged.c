/*
 * Entry: 005584eb
 * Name: ServerList::InfoChanged
 * Namespace: ServerList
 * Signature: bool InfoChanged(ServerList * this, Server * param_1, long param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall ServerList::InfoChanged(ServerList *this,Server *param_1,long param_2)

{
  return param_1->avg_ms != param_2;
}
