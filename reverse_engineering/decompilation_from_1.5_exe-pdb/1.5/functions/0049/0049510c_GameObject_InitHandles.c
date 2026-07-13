/*
 * Entry: 0049510c
 * Name: GameObject::InitHandles
 * Namespace: GameObject
 * Signature: void InitHandles(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl GameObject::InitHandles(void)

{
  char *pcVar1;
  
  pcVar1 = gameObjectBuffer[0] + 0x178;
  freeObjectCount = 0;
  do {
    freeObject = freeObjectCount;
    *(int *)(pcVar1 + -0x24) = freeObject;
    *(uint *)pcVar1 = freeObject - 1;
    freeObjectCount = freeObject + 1;
    pcVar1 = pcVar1 + 0x400;
  } while ((uint)freeObjectCount < 0x200);
  return;
}
