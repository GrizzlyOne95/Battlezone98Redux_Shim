
/* WARNING: Removing unreachable block (ram,0x006aedc6) */
/* WARNING: Removing unreachable block (ram,0x006aedd8) */
/* WARNING: Removing unreachable block (ram,0x006aeda9) */
/* WARNING: Removing unreachable block (ram,0x006aee49) */
/* WARNING: Removing unreachable block (ram,0x006aee5b) */
/* WARNING: Removing unreachable block (ram,0x006aee2c) */

void FUN_006aed80(SOCKET param_1,undefined4 *param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  timeval local_22c;
  int local_224;
  undefined4 local_220;
  int local_21c [3];
  fd_set local_210;
  fd_set local_10c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_10c.fd_count = 0;
  local_21c[1] = 0;
  local_10c.fd_array[0] = param_1;
  local_10c.fd_count = 1;
  local_21c[2] = 0;
  local_210.fd_array[0] = param_1;
  local_10c.fd_count = 1;
  local_210.fd_count = 1;
  local_22c.tv_sec = 0;
  local_22c.tv_usec = 0;
  local_224 = select(param_1 + 1,(fd_set *)0x0,&local_10c,&local_210,&local_22c);
  if (local_224 != 0) {
    local_21c[0] = 0;
    local_220 = 4;
    iVar1 = FUN_006af5a0(param_1,0,0xffff,0x1007,local_21c,&local_220,param_2);
    if (iVar1 == 0) {
      if (local_21c[0] == 0) {
        puVar3 = (undefined4 *)FUN_004fbb60();
        uVar2 = puVar3[1];
        *param_2 = *puVar3;
        param_2[1] = uVar2;
      }
      else {
        uVar2 = FUN_006abbb0();
        puVar3 = (undefined4 *)FUN_00416430(local_21c[0],uVar2);
        uVar2 = puVar3[1];
        *param_2 = *puVar3;
        param_2[1] = uVar2;
      }
    }
  }
  FUN_0083e885();
  return;
}

