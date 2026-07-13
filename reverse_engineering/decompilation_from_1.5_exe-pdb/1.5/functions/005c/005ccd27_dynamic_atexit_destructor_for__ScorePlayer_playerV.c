/*
 * Entry: 005ccd27
 * Name: `dynamic_atexit_destructor_for_'ScorePlayer::playerV''
 * Namespace: `dynamic_atexit_destructor_for_'ScorePlayer
 * Signature: void playerV''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl `dynamic_atexit_destructor_for_'ScorePlayer::playerV__(void)

{
  std::vector<ScorePlayer_*,std::allocator<ScorePlayer_*>_>::_Tidy(&ScorePlayer::playerV);
  operator_delete((void *)ScorePlayer::playerV._padding_);
  return;
}
