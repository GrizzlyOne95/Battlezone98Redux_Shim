
undefined4 * __thiscall FUN_005124f0(undefined4 *param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  undefined4 *puVar3;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00849598;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_004e7370(param_2);
  local_8 = 0;
  *param_1 = LayMinesTask::vftable;
  iVar2 = (*(code *)**(undefined4 **)(param_2 + 0x18))(uVar1);
  if (*(int *)(iVar2 + 0x14) == 0x4d4c5952) {
    param_1[0x54] = *(undefined4 *)(iVar2 + 0x5f0);
    param_1[0x58] = *(undefined4 *)(iVar2 + 0x5f4);
    param_1[0x55] = *(undefined4 *)(iVar2 + 0x5f8);
    param_1[0x5a] = *(undefined4 *)(iVar2 + 0x5fc);
  }
  else {
    param_1[0x54] = 0xf;
    param_1[0x58] = 0x42700000;
    param_1[0x55] = 0x42700000;
    param_1[0x5a] = 0x3fa0d97c;
  }
  param_1[0x56] = 0;
  param_1[0x57] = 0;
  param_1[0x59] = 0;
  puVar3 = (undefined4 *)(**(code **)(*(int *)(param_2 + 0x18) + 0xc))();
  param_1[0x5b] = *puVar3;
  param_1[0x5c] = puVar3[1];
  param_1[0x5d] = puVar3[2];
  ExceptionList = local_10;
  return param_1;
}

