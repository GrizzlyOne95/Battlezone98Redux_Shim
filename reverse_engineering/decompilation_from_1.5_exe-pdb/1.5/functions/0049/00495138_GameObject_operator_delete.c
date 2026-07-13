/*
 * Entry: 00495138
 * Name: GameObject::operator_delete
 * Namespace: GameObject
 * Signature: void operator_delete(void * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl GameObject::operator_delete(void *param_1)

{
  *(undefined4 *)((int)param_1 + 0x150) = 0;
  freeObjectCount = freeObjectCount + 1;
  *(int *)((int)param_1 + 0x178) = freeObject;
  freeObject = *(int *)((int)param_1 + 0x154);
  return;
}
