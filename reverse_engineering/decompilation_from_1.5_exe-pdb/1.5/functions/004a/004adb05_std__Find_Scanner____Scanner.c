/*
 * Entry: 004adb05
 * Name: std::_Find<Scanner_*_*,Scanner_*>
 * Namespace: std
 * Signature: Scanner * * _Find<Scanner_*_*,Scanner_*>(Scanner * * param_1, Scanner * * param_2, Scanner * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Scanner ** __cdecl
std::_Find<Scanner_*_*,Scanner_*>(Scanner **param_1,Scanner **param_2,Scanner **param_3)

{
  if (param_1 != param_2) {
    do {
      if (*param_1 == *param_3) {
        return param_1;
      }
      param_1 = param_1 + 1;
    } while (param_1 != param_2);
  }
  return param_1;
}
