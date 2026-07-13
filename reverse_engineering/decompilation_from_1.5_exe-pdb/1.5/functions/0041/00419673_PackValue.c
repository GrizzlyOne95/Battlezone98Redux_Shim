/*
 * Entry: 00419673
 * Name: PackValue
 * Namespace: Global
 * Signature: bool PackValue(char * * param_1, char * param_2, lua_State * param_3, int param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl PackValue(char **param_1,char *param_2,lua_State *param_3,int param_4)

{
  char *pcVar1;
  bool bVar2;
  int iVar3;
  GameObject *pGVar4;
  ulong uVar5;
  int unaff_ESI;
  lua_State *unaff_EDI;
  
  if (param_4 < 0) {
    iVar3 = lua_gettop(param_3);
    param_4 = param_4 + 1 + iVar3;
  }
  if (*param_1 + 1 < param_2) {
    iVar3 = lua_type(param_3,param_4);
    if (iVar3 == -1) {
      iVar3 = 0;
    }
    **param_1 = (char)iVar3 << 5;
    *param_1 = *param_1 + 1;
    if (iVar3 != 0) {
      if (iVar3 == 1) {
        pcVar1 = *param_1;
        iVar3 = lua_toboolean(param_3,param_4);
        pcVar1[-1] = pcVar1[-1] + (char)iVar3;
      }
      else if (iVar3 == 2) {
        iVar3 = GetHandle(param_3,param_4);
        pGVar4 = GameObject::GetObj(iVar3);
        if (pGVar4 != (GameObject *)0x0) {
          if (param_2 <= *param_1 + 4) goto LAB_00419699;
          pcVar1 = *param_1 + -1;
          *pcVar1 = *pcVar1 + '\x01';
          uVar5 = DistributedObject::GetID((DistributedObject *)&pGVar4->_padding_);
          *(ulong *)*param_1 = uVar5;
          *param_1 = *param_1 + 4;
        }
      }
      else {
        if (iVar3 == 3) {
          bVar2 = PackNumber((char **)param_3,(char *)param_4,unaff_EDI,unaff_ESI);
          return bVar2;
        }
        if (iVar3 == 4) {
          bVar2 = PackString((char **)param_2,(char *)param_3,(lua_State *)param_4,(int)unaff_EDI);
          return bVar2;
        }
        if (iVar3 == 5) {
          bVar2 = PackTable((char **)param_2,(char *)param_3,(lua_State *)param_4,(int)unaff_EDI);
          return bVar2;
        }
        if (iVar3 == 7) {
          bVar2 = PackUserData((char **)param_2,(char *)param_4,unaff_EDI,unaff_ESI);
          return bVar2;
        }
      }
    }
    bVar2 = true;
  }
  else {
LAB_00419699:
    bVar2 = false;
  }
  return bVar2;
}
