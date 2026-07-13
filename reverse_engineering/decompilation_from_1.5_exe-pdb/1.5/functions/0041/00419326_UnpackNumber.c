/*
 * Entry: 00419326
 * Name: UnpackNumber
 * Namespace: Global
 * Signature: void UnpackNumber(char * * param_1, lua_State * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl UnpackNumber(char **param_1,lua_State *param_2)

{
  int *piVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 *in_ECX;
  byte bVar4;
  lua_State *unaff_ESI;
  
  piVar1 = (int *)*in_ECX;
  bVar4 = *(byte *)((int)piVar1 + -1) & 0x1f;
  if (bVar4 == 0) {
    iVar3 = 0;
LAB_00419389:
    lua_pushnumber(unaff_ESI,(double)CONCAT44(in_ECX,iVar3));
    return;
  }
  if (bVar4 == 1) {
    iVar3 = *piVar1;
    *in_ECX = (char *)((int)piVar1 + 1);
    iVar3 = (int)(char)iVar3;
  }
  else if (bVar4 == 2) {
    iVar3 = *piVar1;
    *in_ECX = (short *)((int)piVar1 + 2);
    iVar3 = (int)(short)iVar3;
  }
  else {
    if (bVar4 != 4) {
      if (bVar4 != 8) {
        return;
      }
      puVar2 = (undefined4 *)*piVar1;
      iVar3 = piVar1[1];
      *in_ECX = piVar1 + 2;
      in_ECX = puVar2;
      goto LAB_00419389;
    }
    iVar3 = *piVar1;
    *in_ECX = piVar1 + 1;
  }
  lua_pushinteger(unaff_ESI,iVar3);
  return;
}
