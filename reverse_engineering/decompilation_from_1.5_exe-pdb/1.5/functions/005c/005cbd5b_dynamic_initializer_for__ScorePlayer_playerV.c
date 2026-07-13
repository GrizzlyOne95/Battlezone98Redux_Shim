/*
 * Entry: 005cbd5b
 * Name: `dynamic_initializer_for_'ScorePlayer::playerV''
 * Namespace: `dynamic_initializer_for_'ScorePlayer
 * Signature: void playerV''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl `dynamic_initializer_for_'ScorePlayer::playerV__(void)

{
  std::vector<ScorePlayer_*,std::allocator<ScorePlayer_*>_>::
  vector<ScorePlayer_*,std::allocator<ScorePlayer_*>_>(&ScorePlayer::playerV);
  atexit(`dynamic_atexit_destructor_for_'ScorePlayer::playerV__);
  return;
}
