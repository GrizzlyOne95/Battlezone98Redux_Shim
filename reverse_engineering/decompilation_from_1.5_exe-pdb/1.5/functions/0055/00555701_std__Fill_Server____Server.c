/*
 * Entry: 00555701
 * Name: std::_Fill<Server_*_*,Server_*>
 * Namespace: std
 * Signature: void _Fill<Server_*_*,Server_*>(Server * * param_1, Server * * param_2, Server * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl std::_Fill<Server_*_*,Server_*>(Server **param_1,Server **param_2,Server **param_3)

{
  for (; param_1 != param_2; param_1 = param_1 + 1) {
    *param_1 = *param_3;
  }
  return;
}
