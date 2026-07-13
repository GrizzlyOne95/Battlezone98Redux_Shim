/*
 * Entry: 005ccd10
 * Name: `dynamic_atexit_destructor_for_'NetPlayer::netPlayerMap''
 * Namespace: `dynamic_atexit_destructor_for_'NetPlayer
 * Signature: void netPlayerMap''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl `dynamic_atexit_destructor_for_'NetPlayer::netPlayerMap__(void)

{
  std::
  _Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
  ::_Tidy((_Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
           *)&NetPlayer::netPlayerMap);
  operator_delete((void *)NetPlayer::netPlayerMap._0_4_);
  return;
}
