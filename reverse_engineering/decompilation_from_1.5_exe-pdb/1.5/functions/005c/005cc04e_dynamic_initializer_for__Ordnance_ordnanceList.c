/*
 * Entry: 005cc04e
 * Name: `dynamic_initializer_for_'Ordnance::ordnanceList''
 * Namespace: `dynamic_initializer_for_'Ordnance
 * Signature: void ordnanceList''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl `dynamic_initializer_for_'Ordnance::ordnanceList__(void)

{
  std::list<Ordnance_*,std::allocator<Ordnance_*>_>::list<Ordnance_*,std::allocator<Ordnance_*>_>
            (&Ordnance::ordnanceList);
  atexit(`dynamic_atexit_destructor_for_'Ordnance::ordnanceList__);
  return;
}
