/*
 * Entry: 004e53c8
 * Name: std::vector<ScorePlayer_*,std::allocator<ScorePlayer_*>_>::_Umove<ScorePlayer_*_*>
 * Namespace: std::vector<ScorePlayer_*,std::allocator<ScorePlayer_*>_>
 * Signature: ScorePlayer * * _Umove<ScorePlayer_*_*>(vector<ScorePlayer_*,std::allocator<ScorePlayer_*>_> * this, ScorePlayer * * param_1, ScorePlayer * * param_2, ScorePlayer * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ScorePlayer ** __thiscall
std::vector<ScorePlayer_*,std::allocator<ScorePlayer_*>_>::_Umove<ScorePlayer_*_*>
          (vector<ScorePlayer_*,std::allocator<ScorePlayer_*>_> *this,ScorePlayer **param_1,
          ScorePlayer **param_2,ScorePlayer **param_3)

{
  ScorePlayer **ppSVar1;
  
  ppSVar1 = stdext::
            unchecked_uninitialized_copy<ScorePlayer_*_*,ScorePlayer_*_*,std::allocator<ScorePlayer_*>_>
                      (param_1,param_2,param_3,(allocator<ScorePlayer_*> *)&this->_padding_);
  return ppSVar1;
}
