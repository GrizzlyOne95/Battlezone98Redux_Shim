
void __thiscall FUN_005d8a20(int param_1,undefined4 param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  char cVar4;
  uint uVar5;
  undefined4 *puVar6;
  void *pvVar7;
  undefined4 local_28;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084cacc;
  local_10 = ExceptionList;
  uVar5 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_0047eae0(param_2);
  cVar4 = FUN_00571c40(uVar5);
  if (cVar4 != '\0') {
    puVar6 = (undefined4 *)(**(code **)(*(int *)(param_1 + 0x18) + 0xc))();
    uVar1 = *puVar6;
    uVar2 = puVar6[1];
    uVar3 = puVar6[2];
    pvVar7 = operator_new(0x14);
    local_8 = 0;
    if (pvVar7 == (void *)0x0) {
      local_28 = 0;
    }
    else {
      local_28 = FUN_005d8d50(uVar1,uVar2,uVar3,param_2);
    }
    local_8 = 0xffffffff;
    *(undefined4 *)(param_1 + 0x238) = local_28;
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

