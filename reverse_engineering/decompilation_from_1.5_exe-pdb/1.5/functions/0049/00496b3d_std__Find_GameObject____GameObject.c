/*
 * Entry: 00496b3d
 * Name: std::_Find<GameObject_*_*,GameObject_*>
 * Namespace: std
 * Signature: GameObject * * _Find<GameObject_*_*,GameObject_*>(GameObject * * param_1, GameObject * * param_2, GameObject * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject ** __cdecl
std::_Find<GameObject_*_*,GameObject_*>
          (GameObject **param_1,GameObject **param_2,GameObject **param_3)

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
