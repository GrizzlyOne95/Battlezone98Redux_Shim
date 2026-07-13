/*
 * Entry: 0041c1e9
 * Name: UnpackValue
 * Namespace: Global
 * Signature: void UnpackValue(char * * param_1, lua_State * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl UnpackValue(char **param_1,lua_State *param_2)

{
  byte *pbVar1;
  ulong uVar2;
  byte bVar3;
  int iVar4;
  GameObject *this;
  ulong *puVar5;
  lua_State *unaff_ESI;
  uint uVar6;
  char **unaff_EDI;
  
  pbVar1 = (byte *)*param_1;
  bVar3 = *pbVar1 >> 5;
  puVar5 = (ulong *)(pbVar1 + 1);
  *param_1 = (char *)puVar5;
  if (bVar3 == 0) {
    lua_pushnil(param_2);
  }
  else if (bVar3 == 1) {
    lua_pushboolean(param_2,(uint)((*pbVar1 & 0x1f) != 0));
  }
  else if (bVar3 == 2) {
    iVar4 = 0;
    if ((*pbVar1 & 0x1f) != 0) {
      uVar2 = *puVar5;
      *param_1 = (char *)(pbVar1 + 5);
      this = DistributedObject::GetGameObject(uVar2);
      iVar4 = 0;
      if (this != (GameObject *)0x0) {
        iVar4 = GameObject::GetHandle(this);
      }
    }
    PushHandle(param_2,iVar4);
  }
  else if (bVar3 == 3) {
    UnpackNumber(unaff_EDI,unaff_ESI);
  }
  else if (bVar3 == 4) {
    uVar6 = (int)(char)*pbVar1 & 0x1f;
    if (uVar6 == 0x1f) {
      uVar6 = (uint)(char)(byte)*puVar5;
      *param_1 = (char *)(pbVar1 + 2);
    }
    lua_pushlstring(param_2,*param_1,uVar6);
    *param_1 = *param_1 + uVar6;
  }
  else if (bVar3 == 5) {
    UnpackTable(unaff_EDI,unaff_ESI);
  }
  else if (bVar3 == 7) {
    UnpackUserData(unaff_EDI,unaff_ESI);
  }
  return;
}
