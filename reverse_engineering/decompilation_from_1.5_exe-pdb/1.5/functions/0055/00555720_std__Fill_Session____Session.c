/*
 * Entry: 00555720
 * Name: std::_Fill<Session_*_*,Session_*>
 * Namespace: std
 * Signature: void _Fill<Session_*_*,Session_*>(Session * * param_1, Session * * param_2, Session * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::_Fill<Session_*_*,Session_*>(Session **param_1,Session **param_2,Session **param_3)

{
  for (; param_1 != param_2; param_1 = param_1 + 1) {
    *param_1 = *param_3;
  }
  return;
}
