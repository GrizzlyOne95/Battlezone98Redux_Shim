/*
 * Entry: 0055573f
 * Name: std::_Fill<Player_*_*,Player_*>
 * Namespace: std
 * Signature: void _Fill<Player_*_*,Player_*>(Player * * param_1, Player * * param_2, Player * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl std::_Fill<Player_*_*,Player_*>(Player **param_1,Player **param_2,Player **param_3)

{
  for (; param_1 != param_2; param_1 = param_1 + 1) {
    *param_1 = *param_3;
  }
  return;
}
