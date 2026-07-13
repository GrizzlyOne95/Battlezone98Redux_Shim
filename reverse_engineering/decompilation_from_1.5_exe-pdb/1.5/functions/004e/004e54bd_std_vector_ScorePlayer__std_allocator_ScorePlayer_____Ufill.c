/*
 * Entry: 004e54bd
 * Name: std::vector<ScorePlayer_*,std::allocator<ScorePlayer_*>_>::_Ufill
 * Namespace: std::vector<ScorePlayer_*,std::allocator<ScorePlayer_*>_>
 * Signature: ScorePlayer * * _Ufill(vector<ScorePlayer_*,std::allocator<ScorePlayer_*>_> * this, ScorePlayer * * param_1, uint param_2, ScorePlayer * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ScorePlayer ** __thiscall
std::vector<ScorePlayer_*,std::allocator<ScorePlayer_*>_>::_Ufill
          (vector<ScorePlayer_*,std::allocator<ScorePlayer_*>_> *this,ScorePlayer **param_1,
          uint param_2,ScorePlayer **param_3)

{
  stdext::unchecked_fill_n<ScorePlayer_*_*,unsigned_int,ScorePlayer_*>(param_1,param_2,param_3);
  return param_1 + param_2;
}
