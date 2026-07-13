/*
 * Entry: 005cc901
 * Name: `dynamic_atexit_destructor_for_'queuedState''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'queuedState''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__queuedState__(void)

{
  std::deque<BASE_STRUCT,std::allocator<BASE_STRUCT>_>::_Tidy(&queuedState);
  operator_delete((void *)queuedState._padding_);
  return;
}
