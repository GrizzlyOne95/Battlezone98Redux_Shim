/*
 * Entry: 005b9461
 * Name: iscleared
 * Namespace: Global
 * Signature: int iscleared(lua_TValue * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl iscleared(lua_TValue *param_1,int param_2)

{
  byte *pbVar1;
  byte bVar2;
  int iVar3;
  int *in_EAX;
  
  iVar3 = in_EAX[2];
  if (3 < iVar3) {
    if (iVar3 == 4) {
      pbVar1 = (byte *)(*in_EAX + 5);
      *pbVar1 = *pbVar1 & 0xfc;
    }
    else {
      bVar2 = *(byte *)(*in_EAX + 5);
      if (((bVar2 & 3) != 0) ||
         (((iVar3 == 7 && (param_1 == (lua_TValue *)0x0)) && ((bVar2 & 8) != 0)))) {
        return 1;
      }
    }
  }
  return 0;
}
