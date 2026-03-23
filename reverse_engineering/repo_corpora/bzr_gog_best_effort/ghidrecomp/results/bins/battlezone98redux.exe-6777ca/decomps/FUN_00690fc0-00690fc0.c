
uint FUN_00690fc0(undefined4 *param_1,uint param_2,int param_3,int *param_4,undefined4 param_5,
                 undefined4 param_6)

{
  uint uVar1;
  int iVar2;
  char cVar3;
  int iVar4;
  int local_24;
  uint local_20;
  uint local_14;
  int local_10;
  int local_8;
  
  local_10 = param_1[0x99];
  local_14 = 0;
  if (local_10 == 0) {
    local_14 = 0;
  }
  else {
    local_8 = FUN_006a0710(local_10);
    if ((local_10 <= local_8) || (local_8 < 0)) {
      printf("Node %d Count %d\n",local_8,local_10);
    }
    while ((local_10 != 0 && (local_14 == 0))) {
      if (0 < (int)param_1[local_8 * 5 + 0x9b]) {
        uVar1 = param_1[local_8 * 5 + 0x9c];
        if (param_3 == 0) {
          local_20 = FUN_006a0560(param_2 & 0xffff,uVar1 & 0xffff,*(undefined1 *)param_1);
          local_20 = local_20 & 0xff;
        }
        else {
          local_20 = FUN_00690f50(param_2,uVar1);
        }
        if (local_20 != 0) {
          iVar4 = FUN_00690d20(uVar1);
          iVar2 = param_1[local_8 * 5 + 0x9d];
          if (iVar4 <= (int)param_1[iVar2 + 0x2f]) {
            local_24 = 1;
            if ((param_3 == 0) && (cVar3 = FUN_006a05c0(uVar1 & 0xffff), cVar3 != '\0')) {
              local_24 = FUN_006924a0(param_1,uVar1,param_5,param_6);
            }
            if (local_24 != 0) {
              FUN_00690570(*param_1,uVar1);
              FUN_0068ff30(*param_1,iVar2,iVar4);
              *param_4 = iVar2;
              param_1[0x2e] = param_1[0x2e] + iVar4;
              param_1[local_8 * 5 + 0x9b] = param_1[local_8 * 5 + 0x9b] + -1;
              if (param_1[local_8 * 5 + 0x9e] == 1) {
                *(int *)param_1[local_8 * 5 + 0x9f] = *(int *)param_1[local_8 * 5 + 0x9f] + -1;
              }
              else if (param_1[local_8 * 5 + 0x9e] == 2) {
                *(int *)param_1[local_8 * 5 + 0x9f] = *(int *)param_1[local_8 * 5 + 0x9f] + 1;
              }
              FUN_00690da0(param_1);
              local_14 = uVar1;
            }
          }
        }
      }
      local_10 = local_10 + -1;
      local_8 = local_8 + 1;
      if (local_8 == param_1[0x99]) {
        local_8 = 0;
      }
    }
  }
  return local_14;
}

