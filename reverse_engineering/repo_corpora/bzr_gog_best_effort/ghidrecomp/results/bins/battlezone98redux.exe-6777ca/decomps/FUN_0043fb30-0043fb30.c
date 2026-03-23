
void FUN_0043fb30(undefined4 param_1,int *param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int *local_82c;
  int *local_820;
  int *local_81c;
  int local_818;
  int local_814;
  int *local_810;
  int local_80c;
  int local_808 [512];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  iVar1 = param_2[0x8000];
  iVar2 = param_2[0x8001];
  iVar3 = param_2[0x8006];
  local_81c = param_2;
  for (local_818 = iVar2; local_814 = iVar1, 0 < local_818; local_818 = local_818 + -1) {
    local_810 = local_81c;
    local_80c = 0;
    for (; 0 < local_814; local_814 = local_814 + -1) {
      if (*local_810 == 0) {
        if (1 < local_80c) {
          FUN_00687340(local_820,local_80c,iVar3);
        }
        local_80c = 0;
      }
      else {
        if (local_80c == 0) {
          local_820 = local_810;
        }
        local_80c = local_80c + 1;
      }
      local_810 = local_810 + 2;
    }
    if (1 < local_80c) {
      FUN_00687340(local_820,local_80c,iVar3);
    }
    local_81c = local_81c + iVar1 * 2;
  }
  local_81c = param_2;
  for (; 0 < local_814; local_814 = local_814 + -1) {
    local_82c = local_808;
    local_810 = local_81c;
    local_80c = 0;
    for (local_818 = iVar2; 0 < local_818; local_818 = local_818 + -1) {
      if (*local_810 == 0) {
        if (1 < local_80c) {
          FUN_00687340(local_820,local_80c,iVar3);
        }
        local_80c = 0;
      }
      else {
        if (local_80c == 0) {
          local_820 = local_82c;
        }
        iVar4 = local_810[1];
        *local_82c = *local_810;
        local_82c[1] = iVar4;
        local_82c = local_82c + 2;
        local_80c = local_80c + 1;
      }
      local_810 = local_810 + iVar1 * 2;
    }
    if (1 < local_80c) {
      FUN_00687340(local_820,local_80c,iVar3);
    }
    local_81c = local_81c + 2;
  }
  FUN_0083e885();
  return;
}

