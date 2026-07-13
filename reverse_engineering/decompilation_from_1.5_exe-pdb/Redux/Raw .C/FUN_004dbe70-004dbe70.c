
void __thiscall
FUN_004dbe70(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5
            )

{
  char cVar1;
  void *pvVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 local_1c;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008477bc;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  if (*(int *)(param_1 + 0xd4) != 0) {
    FUN_00460600(*(undefined4 *)(param_1 + 0xd4),DAT_008e7000 ^ (uint)&stack0xfffffffc);
  }
  *(undefined4 *)(param_1 + 200) = 0;
  *(undefined4 *)(param_1 + 0xcc) = param_2;
  *(undefined4 *)(param_1 + 0xd0) = 0;
  pvVar2 = operator_new(0x18);
  local_8 = 0;
  if (pvVar2 == (void *)0x0) {
    local_1c = 0;
  }
  else {
    uVar4 = param_3;
    uVar3 = (**(code **)(*(int *)(param_1 + 0x18) + 0xc))(param_3);
    local_1c = FUN_00460490(uVar3,uVar4);
  }
  local_8 = 0xffffffff;
  *(undefined4 *)(param_1 + 0xd4) = local_1c;
  *(undefined4 *)(param_1 + 0xe0) = param_4;
  *(undefined4 *)(param_1 + 0xe4) = param_5;
  cVar1 = FUN_004b9830();
  if (cVar1 != '\0') {
    FUN_004b7b00(param_2,param_3);
  }
  ExceptionList = local_10;
  return;
}

