/*
 * Entry: 0041c1b7
 * Name: UnpackHandle
 * Namespace: Global
 * Signature: bool UnpackHandle(char * * param_1, lua_State * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl UnpackHandle(char **param_1,lua_State *param_2)

{
  ulong *puVar1;
  ulong uVar2;
  int iVar3;
  GameObject *this;
  int *in_EDX;
  
  puVar1 = (ulong *)*in_EDX;
  iVar3 = 0;
  if ((*(byte *)((int)puVar1 + -1) & 0x1f) != 0) {
    uVar2 = *puVar1;
    *in_EDX = (int)(puVar1 + 1);
    this = DistributedObject::GetGameObject(uVar2);
    iVar3 = 0;
    if (this != (GameObject *)0x0) {
      iVar3 = GameObject::GetHandle(this);
    }
  }
  PushHandle((lua_State *)param_1,iVar3);
  return true;
}
