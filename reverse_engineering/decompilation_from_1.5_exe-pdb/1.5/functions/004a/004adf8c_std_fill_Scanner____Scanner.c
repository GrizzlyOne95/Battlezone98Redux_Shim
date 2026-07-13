/*
 * Entry: 004adf8c
 * Name: std::fill<Scanner_*_*,Scanner_*>
 * Namespace: std
 * Signature: void fill<Scanner_*_*,Scanner_*>(Scanner * * param_1, Scanner * * param_2, Scanner * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl std::fill<Scanner_*_*,Scanner_*>(Scanner **param_1,Scanner **param_2,Scanner **param_3)

{
  for (; param_1 != param_2; param_1 = param_1 + 1) {
    *param_1 = *param_3;
  }
  return;
}
