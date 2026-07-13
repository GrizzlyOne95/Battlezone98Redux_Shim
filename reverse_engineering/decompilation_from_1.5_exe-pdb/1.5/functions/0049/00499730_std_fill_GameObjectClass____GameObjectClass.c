/*
 * Entry: 00499730
 * Name: std::fill<GameObjectClass_*_*,GameObjectClass_*>
 * Namespace: std
 * Signature: void fill<GameObjectClass_*_*,GameObjectClass_*>(GameObjectClass * * param_1, GameObjectClass * * param_2, GameObjectClass * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::fill<GameObjectClass_*_*,GameObjectClass_*>
          (GameObjectClass **param_1,GameObjectClass **param_2,GameObjectClass **param_3)

{
  for (; param_1 != param_2; param_1 = param_1 + 1) {
    *param_1 = *param_3;
  }
  return;
}
