
/* WARNING: Removing unreachable block (ram,0x0043b7c5) */

void FUN_0043b720(int param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_c;
  undefined4 local_8;
  
  if (param_1 != 0) {
    if (((*(uint *)(param_1 + 0x14) & 0x40) != 0) && (iVar1 = FUN_0043cf30(param_1), iVar1 != 0)) {
      uVar2 = FUN_008445c0();
      FUN_0043d0a0(param_1,uVar2);
    }
    if ((*(uint *)(param_1 + 0x14) & 0x80) != 0) {
      if ((*(uint *)(param_1 + 0x14) & 4) == 0) {
        local_c = *(int *)(DAT_00915594 + 8) * *(int *)(DAT_00915594 + 8);
      }
      else {
        local_c = *(int *)(DAT_00915594 + 0xc) * *(int *)(DAT_00915594 + 0xc);
      }
      local_8 = FUN_008445c0(local_c);
      if (100 < local_8) {
        local_8 = 100;
      }
      FUN_0043d0c0(param_1,local_8,local_c);
    }
    if (((*(uint *)(param_1 + 0x14) & 0x100) != 0) &&
       (iVar1 = ___scrt_is_ucrt_dll_in_use(DAT_00915594), iVar1 == 0)) {
      uVar2 = FUN_008445c0();
      FUN_0043d110(param_1,uVar2);
    }
    if ((*(int *)(param_1 + 0x58) != 0) &&
       (iVar1 = ___scrt_is_ucrt_dll_in_use(DAT_00915594), iVar1 != 0)) {
      FUN_0043b8b0(param_1);
      if ((*(uint *)(param_1 + 0x14) & 0x400) != 0) {
        *(undefined4 *)(param_1 + 0x58) = 0;
        *(undefined4 *)(param_1 + 0x78) = 0;
        *(uint *)(param_1 + 0x70) = *(uint *)(param_1 + 0x70) | 0x10;
      }
      if (param_2 != 0) {
        FUN_0043c6e0(DAT_00915594);
      }
    }
    *(uint *)(param_1 + 0x14) = *(uint *)(param_1 + 0x14) & 0xfffffc3f;
  }
  return;
}

