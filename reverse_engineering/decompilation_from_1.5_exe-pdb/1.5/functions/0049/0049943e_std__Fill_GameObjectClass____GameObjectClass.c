/*
 * Entry: 0049943e
 * Name: std::_Fill<GameObjectClass_*_*,GameObjectClass_*>
 * Namespace: std
 * Signature: void _Fill<GameObjectClass_*_*,GameObjectClass_*>(GameObjectClass * * param_1, GameObjectClass * * param_2, GameObjectClass * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::_Fill<GameObjectClass_*_*,GameObjectClass_*>
          (GameObjectClass **param_1,GameObjectClass **param_2,GameObjectClass **param_3)

{
  for (; param_1 != param_2; param_1 = param_1 + 1) {
    *param_1 = *param_3;
  }
  return;
}
