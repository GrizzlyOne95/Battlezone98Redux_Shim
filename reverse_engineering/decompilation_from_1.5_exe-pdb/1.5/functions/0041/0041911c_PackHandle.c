/*
 * Entry: 0041911c
 * Name: PackHandle
 * Namespace: Global
 * Signature: bool PackHandle(char * * param_1, char * param_2, lua_State * param_3, int param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl PackHandle(char **param_1,char *param_2,lua_State *param_3,int param_4)

{
  char *pcVar1;
  int iVar2;
  GameObject *pGVar3;
  ulong uVar4;
  int *unaff_ESI;
  
  iVar2 = GetHandle((lua_State *)param_2,(int)param_3);
  pGVar3 = GameObject::GetObj(iVar2);
  if (pGVar3 != (GameObject *)0x0) {
    if (param_1 <= (char **)(*unaff_ESI + 4U)) {
      return false;
    }
    pcVar1 = (char *)(*unaff_ESI + -1);
    *pcVar1 = *pcVar1 + '\x01';
    uVar4 = DistributedObject::GetID((DistributedObject *)&pGVar3->_padding_);
    *(ulong *)*unaff_ESI = uVar4;
    *unaff_ESI = *unaff_ESI + 4;
  }
  return true;
}
