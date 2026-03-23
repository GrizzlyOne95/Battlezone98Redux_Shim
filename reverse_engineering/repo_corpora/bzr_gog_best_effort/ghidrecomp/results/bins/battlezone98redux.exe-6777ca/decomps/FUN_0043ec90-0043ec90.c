
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0043ec90(undefined4 *param_1,undefined4 param_2,uint param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6,undefined4 param_7,uint param_8,int param_9)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  void *pvVar4;
  uint uVar5;
  int iVar6;
  undefined4 local_64;
  undefined2 local_58;
  int *local_50;
  uint local_4c;
  int local_48;
  int *local_44;
  void *local_40;
  int local_3c;
  undefined4 local_38;
  uint local_34;
  int local_30;
  undefined4 local_2c;
  undefined *local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00845fcc;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  if ((param_1 != (undefined4 *)0x0) && (param_9 != 0)) {
    local_50 = (int *)0x0;
    local_40 = (void *)0x0;
    local_44 = (int *)0x0;
    iVar2 = ov_info(param_2,0xffffffff,local_14);
    uVar1 = *(uint *)(iVar2 + 4);
    iVar2 = *(int *)(iVar2 + 8);
    uVar3 = (uVar1 << 4) >> 3;
    uVar5 = iVar2 * 3 * uVar3 >> 4;
    local_48 = uVar5 - uVar5 % uVar3;
    iVar6 = local_48 * param_8;
    local_2c = 0;
    local_38 = 0x24;
    local_34 = param_3 | 0x10100;
    local_24 = param_4;
    local_20 = param_5;
    local_1c = param_6;
    local_18 = param_7;
    _DAT_02cc2e14 = 1;
    local_58 = (undefined2)uVar1;
    DAT_02cc2e16 = local_58;
    DAT_02cc2e22 = 0x10;
    _DAT_02cc2e24 = 0;
    _DAT_02cc2e20 = (undefined2)((int)((uVar1 & 0xffff) * 0x10) >> 3);
    _DAT_02cc2e1c = (uVar1 & 0xffff) * iVar2 * 0x10 >> 3;
    local_28 = &DAT_02cc2e14;
    DAT_02cc2e18 = iVar2;
    local_30 = iVar6;
    local_3c = (**(code **)(**(int **)(DAT_00915594 + 0x18) + 0xc))
                         (*(undefined4 *)(DAT_00915594 + 0x18),&local_38,&local_50,0);
    if (local_3c < 0) {
      FUN_007d6a70("Couldn\'t CreateSoundBuffer(). hr = %08X (%d)\n",local_3c,local_3c);
    }
    else {
      local_3c = (**(code **)*local_50)(local_50,&DAT_0086e988,&local_44);
      if ((-1 < local_3c) &&
         (local_40 = (void *)FUN_0083d92c(-(uint)((int)((ulonglong)param_8 * 8 >> 0x20) != 0) |
                                          (uint)((ulonglong)param_8 * 8)), local_40 != (void *)0x0))
      {
        for (local_4c = 0; local_4c < param_8; local_4c = local_4c + 1) {
          *(uint *)((int)local_40 + local_4c * 8) = local_48 * local_4c + -1 + local_48;
          *(int *)((int)local_40 + local_4c * 8 + 4) = param_9;
        }
        local_3c = (**(code **)(*local_44 + 0xc))(local_44,param_8,local_40);
        if (local_3c < 0) {
          if (local_44 != (int *)0x0) {
            (**(code **)(*local_44 + 8))(local_44);
            local_44 = (int *)0x0;
          }
          if (local_40 != (void *)0x0) {
            operator_delete__(local_40);
            local_40 = (void *)0x0;
          }
        }
        else {
          if (local_44 != (int *)0x0) {
            (**(code **)(*local_44 + 8))(local_44);
            local_44 = (int *)0x0;
          }
          if (local_40 != (void *)0x0) {
            operator_delete__(local_40);
            local_40 = (void *)0x0;
          }
          pvVar4 = operator_new(0x38);
          local_8 = 0;
          if (pvVar4 == (void *)0x0) {
            local_64 = 0;
          }
          else {
            local_64 = FUN_00416830(local_50,iVar6,param_2,local_48);
          }
          local_8 = 0xffffffff;
          *param_1 = local_64;
          (**(code **)(*local_50 + 0x44))(local_50,iVar2);
        }
      }
    }
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

