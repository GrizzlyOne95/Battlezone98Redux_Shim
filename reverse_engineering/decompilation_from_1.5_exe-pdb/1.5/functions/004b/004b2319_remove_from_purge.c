/*
 * Entry: 004b2319
 * Name: remove_from_purge
 * Namespace: Global
 * Signature: void remove_from_purge(_texcache * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl remove_from_purge(_texcache *param_1)

{
  _texcache *in_EAX;
  
  if (purge_head == in_EAX) {
    purge_head = in_EAX->next_purge;
  }
  if (purge_tail == in_EAX) {
    purge_tail = in_EAX->last_purge;
  }
  if (in_EAX->last_purge != (_texcache *)0x0) {
    in_EAX->last_purge->next_purge = in_EAX->next_purge;
  }
  if (in_EAX->next_purge != (_texcache *)0x0) {
    in_EAX->next_purge->last_purge = in_EAX->last_purge;
  }
  in_EAX->next_purge = (_texcache *)0x0;
  in_EAX->last_purge = (_texcache *)0x0;
  in_EAX->flags = in_EAX->flags & 0xfffc;
  return;
}
