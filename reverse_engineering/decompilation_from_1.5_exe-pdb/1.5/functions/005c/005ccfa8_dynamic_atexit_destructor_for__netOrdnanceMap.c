/*
 * Entry: 005ccfa8
 * Name: `dynamic_atexit_destructor_for_'netOrdnanceMap''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'netOrdnanceMap''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__netOrdnanceMap__(void)

{
  std::
  _Tree<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_>
  ::_Tidy((_Tree<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_>
           *)&netOrdnanceMap);
  operator_delete((void *)netOrdnanceMap._0_4_);
  return;
}
