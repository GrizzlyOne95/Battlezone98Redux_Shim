/*
 * Entry: 00557ffd
 * Name: std::fill<Server_*_*,Server_*>
 * Namespace: std
 * Signature: void fill<Server_*_*,Server_*>(Server * * param_1, Server * * param_2, Server * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl std::fill<Server_*_*,Server_*>(Server **param_1,Server **param_2,Server **param_3)

{
  for (; param_1 != param_2; param_1 = param_1 + 1) {
    *param_1 = *param_3;
  }
  return;
}
