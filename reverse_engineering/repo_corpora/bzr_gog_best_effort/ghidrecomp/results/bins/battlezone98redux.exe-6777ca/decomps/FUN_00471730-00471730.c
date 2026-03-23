
void __fastcall FUN_00471730(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  void *pvVar3;
  undefined4 local_1c;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084762c;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  iVar1 = (*(code *)**(undefined4 **)(*(int *)(param_1 + 0x34) + 0x18))
                    (DAT_008e7000 ^ (uint)&stack0xfffffffc);
  if (*(int *)(iVar1 + 0x14) == 0x41504300) {
    uVar2 = FUN_00462630(*(undefined4 *)(param_1 + 0x3c));
    pvVar3 = operator_new(0x134);
    local_8 = 0;
    if (pvVar3 == (void *)0x0) {
      local_1c = 0;
    }
    else {
      local_1c = FUN_00471e20(*(undefined4 *)(param_1 + 0x34),uVar2);
    }
    *(undefined4 *)(param_1 + 0x38) = local_1c;
  }
  else {
    *(undefined4 *)(param_1 + 0x20) = 3;
  }
  ExceptionList = local_10;
  return;
}

