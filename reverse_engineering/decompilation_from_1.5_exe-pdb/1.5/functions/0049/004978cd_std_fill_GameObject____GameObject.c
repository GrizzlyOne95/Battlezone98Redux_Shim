/*
 * Entry: 004978cd
 * Name: std::fill<GameObject_*_*,GameObject_*>
 * Namespace: std
 * Signature: void fill<GameObject_*_*,GameObject_*>(GameObject * * param_1, GameObject * * param_2, GameObject * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::fill<GameObject_*_*,GameObject_*>
          (GameObject **param_1,GameObject **param_2,GameObject **param_3)

{
  for (; param_1 != param_2; param_1 = param_1 + 1) {
    *param_1 = *param_3;
  }
  return;
}
