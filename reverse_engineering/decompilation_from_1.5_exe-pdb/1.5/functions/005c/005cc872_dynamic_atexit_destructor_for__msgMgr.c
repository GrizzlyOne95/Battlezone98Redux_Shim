/*
 * Entry: 005cc872
 * Name: `dynamic_atexit_destructor_for_'msgMgr''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'msgMgr''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__msgMgr__(void)

{
  std::list<AudMsgInfo_*,std::allocator<AudMsgInfo_*>_>::_Tidy(&msgMgr.msgList);
  operator_delete((void *)msgMgr.msgList._padding_);
  return;
}
