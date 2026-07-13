/*
 * Entry: 005cbd45
 * Name: `dynamic_initializer_for_'NetPlayer::netPlayerMap''
 * Namespace: `dynamic_initializer_for_'NetPlayer
 * Signature: void netPlayerMap''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl `dynamic_initializer_for_'NetPlayer::netPlayerMap__(void)

{
  std::
  map<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>_>
  ::
  map<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>_>
            (&NetPlayer::netPlayerMap);
  atexit(`dynamic_atexit_destructor_for_'NetPlayer::netPlayerMap__);
  return;
}
