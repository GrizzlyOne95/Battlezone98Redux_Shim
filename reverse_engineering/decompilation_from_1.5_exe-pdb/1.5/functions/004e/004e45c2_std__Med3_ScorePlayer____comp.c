/*
 * Entry: 004e45c2
 * Name: std::_Med3<ScorePlayer_*_*,comp>
 * Namespace: std
 * Signature: void _Med3<ScorePlayer_*_*,comp>(ScorePlayer * * param_1, ScorePlayer * * param_2, ScorePlayer * * param_3, comp param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::_Med3<ScorePlayer_*_*,comp>
          (ScorePlayer **param_1,ScorePlayer **param_2,ScorePlayer **param_3,comp param_4)

{
  if ((*param_1)->iKills - (*param_1)->iDeaths < (*param_2)->iKills - (*param_2)->iDeaths) {
    swap<ScorePlayer_*>(param_2,param_1);
  }
  if ((*param_2)->iKills - (*param_2)->iDeaths < (*param_3)->iKills - (*param_3)->iDeaths) {
    swap<ScorePlayer_*>(param_3,param_2);
  }
  if ((*param_1)->iKills - (*param_1)->iDeaths < (*param_2)->iKills - (*param_2)->iDeaths) {
    swap<ScorePlayer_*>(param_2,param_1);
  }
  return;
}
