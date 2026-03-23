
/* WARNING: Removing unreachable block (ram,0x006afa41) */
/* WARNING: Removing unreachable block (ram,0x006afa53) */
/* WARNING: Removing unreachable block (ram,0x006afa24) */

void FUN_006af9e0(SOCKET param_1,byte param_2,undefined4 *param_3)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 *puVar3;
  timeval local_12c;
  timeval *local_124;
  undefined4 *local_120;
  undefined4 *local_11c;
  timeval *local_118;
  int local_114;
  undefined4 local_110;
  fd_set local_10c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  if (param_1 == 0xffffffff) {
    FUN_006d8cf0(0x2719);
  }
  else {
    local_110 = 0;
    local_10c.fd_array[0] = param_1;
    local_10c.fd_count = 1;
    local_12c.tv_sec = 0;
    local_12c.tv_usec = 0;
    if ((param_2 & 1) == 0) {
      local_118 = (timeval *)0x0;
    }
    else {
      local_118 = &local_12c;
    }
    local_124 = local_118;
    FUN_006ae8d0();
    puVar3 = param_3;
    iVar2 = select(param_1 + 1,(fd_set *)0x0,&local_10c,(fd_set *)0x0,local_124);
    local_114 = FUN_006d8d90(iVar2,puVar3);
    if (local_114 == 0) {
      if ((param_2 & 1) == 0) {
        local_11c = (undefined4 *)FUN_004fbb60();
      }
      else {
        local_11c = (undefined4 *)FUN_006d8cc0(0x2733,0);
      }
      local_120 = local_11c;
      uVar1 = local_11c[1];
      *param_3 = *local_11c;
      param_3[1] = uVar1;
    }
    else if (0 < local_114) {
      puVar3 = (undefined4 *)FUN_004fbb60();
      uVar1 = puVar3[1];
      *param_3 = *puVar3;
      param_3[1] = uVar1;
    }
  }
  FUN_0083e885();
  return;
}

