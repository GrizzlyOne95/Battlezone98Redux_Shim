/*
 * Entry: 004b11a0
 * Name: std::_Find<GameObject_*_*,SpawnBuoy_*>
 * Namespace: std
 * Signature: GameObject * * _Find<GameObject_*_*,SpawnBuoy_*>(GameObject * * param_1, GameObject * * param_2, SpawnBuoy * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject ** __cdecl
std::_Find<GameObject_*_*,SpawnBuoy_*>
          (GameObject **param_1,GameObject **param_2,SpawnBuoy **param_3)

{
  if (param_1 != param_2) {
    do {
      if ((SpawnBuoy *)*param_1 == *param_3) {
        return param_1;
      }
      param_1 = param_1 + 1;
    } while (param_1 != param_2);
  }
  return param_1;
}
