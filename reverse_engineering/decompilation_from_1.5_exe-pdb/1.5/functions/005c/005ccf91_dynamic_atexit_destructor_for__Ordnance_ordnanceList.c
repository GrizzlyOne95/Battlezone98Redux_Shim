/*
 * Entry: 005ccf91
 * Name: `dynamic_atexit_destructor_for_'Ordnance::ordnanceList''
 * Namespace: `dynamic_atexit_destructor_for_'Ordnance
 * Signature: void ordnanceList''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl `dynamic_atexit_destructor_for_'Ordnance::ordnanceList__(void)

{
  std::list<Ordnance_*,std::allocator<Ordnance_*>_>::_Tidy(&Ordnance::ordnanceList);
  operator_delete((void *)Ordnance::ordnanceList._padding_);
  return;
}
