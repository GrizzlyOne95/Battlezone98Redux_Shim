/*
 * Entry: 0041117e
 * Name: MovedObject
 * Namespace: Global
 * Signature: bool MovedObject(GameObject * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl MovedObject(GameObject *param_1)

{
  int iVar1;
  int in_ECX;
  
  iVar1 = (**(code **)(*(int *)(in_ECX + 0x20) + 4))();
  return (bool)('\x01' - (iVar1 != 3));
}
