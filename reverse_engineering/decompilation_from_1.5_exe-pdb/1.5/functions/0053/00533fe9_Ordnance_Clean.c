/*
 * Entry: 00533fe9
 * Name: Ordnance_Clean
 * Namespace: Global
 * Signature: void Ordnance_Clean(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Ordnance_Clean(void)

{
  Ordnance **ppOVar1;
  
  while (Ordnance::ordnanceList._Mysize != 0) {
    ppOVar1 = std::list<Ordnance_*,std::allocator<Ordnance_*>_>::back(&Ordnance::ordnanceList);
    (**(code **)((*ppOVar1)->_padding_ + 8))();
  }
  g_next_ordid = 0;
  std::
  _Tree<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_>
  ::clear((_Tree<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_>
           *)&netOrdnanceMap);
  return;
}
