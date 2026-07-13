
void __fastcall FUN_005fba40(int param_1)

{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  void *pvVar4;
  undefined4 local_20;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084c57c;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  iVar1 = *(int *)(*(int *)(param_1 + 0x34) + 0x230);
  *(undefined4 *)(iVar1 + 0xc4) = 0;
  *(undefined4 *)(iVar1 + 200) = 0;
  uVar3 = FUN_00462630(*(undefined4 *)(param_1 + 0x3c),uVar2);
  pvVar4 = operator_new(0x134);
  local_8 = 0;
  if (pvVar4 == (void *)0x0) {
    local_20 = 0;
  }
  else {
    local_20 = FUN_004d3790(*(undefined4 *)(param_1 + 0x34),uVar3);
  }
  *(undefined4 *)(param_1 + 0x38) = local_20;
  ExceptionList = local_10;
  return;
}

