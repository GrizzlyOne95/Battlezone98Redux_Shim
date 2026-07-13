/*
 * Entry: 004e4787
 * Name: std::allocator<ScorePlayer_*>::allocate
 * Namespace: std::allocator<ScorePlayer_*>
 * Signature: ScorePlayer * * allocate(allocator<ScorePlayer_*> * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ScorePlayer ** __thiscall
std::allocator<ScorePlayer_*>::allocate(allocator<ScorePlayer_*> *this,uint param_1)

{
  ScorePlayer **ppSVar1;
  
  ppSVar1 = _Allocate<ScorePlayer_*>(param_1,(ScorePlayer **)0x0);
  return ppSVar1;
}
