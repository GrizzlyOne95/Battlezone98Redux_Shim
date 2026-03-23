
void __fastcall FUN_005b6b50(int param_1)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  undefined4 uVar4;
  void *pvVar5;
  undefined4 local_2c;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084c54c;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_00462590(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  iVar1 = FUN_005e10b0();
  iVar2 = FUN_005e1190();
  if (iVar1 < iVar2) {
    uVar3 = (**(code **)(*(int *)(*(int *)(param_1 + 0x2c) + 0x18) + 4))();
    iVar1 = FUN_00463120(*(undefined4 *)(param_1 + 0x2c));
    if (iVar1 == 0) {
      if ((&DAT_02a13ce8)[uVar3] != '\0') {
        FUN_005b6500(*(undefined4 *)(param_1 + 0x14));
        if (0xf < uVar3) {
          ___report_rangecheckfailure();
        }
        (&DAT_02a13ce8)[uVar3] = 0;
      }
      *(undefined4 *)(param_1 + 0x4c) = 6;
    }
    else {
      (&DAT_02a13ce8)[uVar3] = 1;
      uVar4 = FUN_00477590(iVar1);
      *(undefined4 *)(param_1 + 0x44) = uVar4;
      pvVar5 = operator_new(0x15c);
      local_8 = 0;
      if (pvVar5 == (void *)0x0) {
        local_2c = 0;
      }
      else {
        local_2c = FUN_005b81e0(*(undefined4 *)(param_1 + 0x2c),iVar1);
      }
      *(undefined4 *)(param_1 + 0x30) = local_2c;
    }
  }
  else {
    *(undefined4 *)(param_1 + 0x4c) = 6;
  }
  ExceptionList = local_10;
  return;
}

