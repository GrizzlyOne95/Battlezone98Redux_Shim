/*
 * Entry: 005caa2b
 * Name: `dynamic_initializer_for_'queuedState''
 * Namespace: Global
 * Signature: void `dynamic_initializer_for_'queuedState''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_initializer_for__queuedState__(void)

{
  std::deque<BASE_STRUCT,std::allocator<BASE_STRUCT>_>::
  deque<BASE_STRUCT,std::allocator<BASE_STRUCT>_>(&queuedState);
  atexit(_dynamic_atexit_destructor_for__queuedState__);
  return;
}
