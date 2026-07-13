/*
 * Entry: 004e0e6b
 * Name: dpEnumPlayerLivesCallback
 * Namespace: Global
 * Signature: void dpEnumPlayerLivesCallback(ushort param_1, char * param_2, long param_3, void * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl dpEnumPlayerLivesCallback(ushort param_1,char *param_2,long param_3,void *param_4)

{
  ushort uVar1;
  undefined2 in_stack_00000006;
  undefined4 local_c;
  int local_8;
  
  if (param_1 != 0xfa01) {
    local_8 = Net::iStartLivesLeft;
    local_c = 4;
    dpGetPlayerData(Net::dp,_param_1,0x13,&local_8,&local_c,0);
    uVar1 = Net_GetMyPlayerID();
    if (param_1 == uVar1) {
      if (local_8 != 0) {
        return;
      }
    }
    else if (local_8 < 1) {
      return;
    }
    *(undefined1 *)param_4 = 0;
  }
  return;
}
