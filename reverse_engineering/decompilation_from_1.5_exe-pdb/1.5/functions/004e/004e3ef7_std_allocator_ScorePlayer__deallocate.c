/*
 * Entry: 004e3ef7
 * Name: std::allocator<ScorePlayer_*>::deallocate
 * Namespace: std::allocator<ScorePlayer_*>
 * Signature: void deallocate(allocator<ScorePlayer_*> * this, ScorePlayer * * param_1, uint param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::allocator<ScorePlayer_*>::deallocate
          (allocator<ScorePlayer_*> *this,ScorePlayer **param_1,uint param_2)

{
  operator_delete(param_1);
  return;
}
