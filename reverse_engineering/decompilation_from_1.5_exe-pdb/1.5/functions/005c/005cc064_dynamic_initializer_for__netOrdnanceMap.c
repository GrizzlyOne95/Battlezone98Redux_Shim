/*
 * Entry: 005cc064
 * Name: `dynamic_initializer_for_'netOrdnanceMap''
 * Namespace: Global
 * Signature: void `dynamic_initializer_for_'netOrdnanceMap''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_initializer_for__netOrdnanceMap__(void)

{
  std::
  map<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>_>
  ::
  map<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>_>
            (&netOrdnanceMap);
  atexit(_dynamic_atexit_destructor_for__netOrdnanceMap__);
  return;
}
