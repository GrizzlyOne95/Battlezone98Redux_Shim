/*
 * Entry: 00495162
 * Name: GameObject::GetObj
 * Namespace: GameObject
 * Signature: GameObject * GetObj(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject * __cdecl GameObject::GetObj(int param_1)

{
  if (param_1 == 0) {
    return (GameObject *)0x0;
  }
  return (GameObject *)
         (~-(uint)(*(uint *)(gameObjectBuffer[(uint)param_1 >> 0x17] + 0x150) !=
                  (param_1 & 0x7fffffU)) & (uint)(gameObjectBuffer + ((uint)param_1 >> 0x17)));
}
