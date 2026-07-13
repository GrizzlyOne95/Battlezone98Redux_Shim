/*
 * Entry: 004adae6
 * Name: std::_Fill<Scanner_*_*,Scanner_*>
 * Namespace: std
 * Signature: void _Fill<Scanner_*_*,Scanner_*>(Scanner * * param_1, Scanner * * param_2, Scanner * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::_Fill<Scanner_*_*,Scanner_*>(Scanner **param_1,Scanner **param_2,Scanner **param_3)

{
  for (; param_1 != param_2; param_1 = param_1 + 1) {
    *param_1 = *param_3;
  }
  return;
}
