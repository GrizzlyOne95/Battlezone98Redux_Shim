
void __fastcall FUN_006b3e50(int param_1)

{
  uint uVar1;
  int iVar2;
  void *pvVar3;
  undefined4 uVar4;
  undefined4 *puVar5;
  undefined4 uVar6;
  undefined4 local_1c;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008507a4;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_006c8ce0(param_1 + 4);
  local_8 = 0;
  iVar2 = get(uVar1);
  if (iVar2 == 0) {
    pvVar3 = operator_new(0xc);
    local_8._0_1_ = 1;
    if (pvVar3 == (void *)0x0) {
      local_1c = 0;
    }
    else {
      uVar6 = 0;
      uVar4 = get(0);
      puVar5 = (undefined4 *)FUN_00447eb0(uVar4);
      local_1c = FUN_006d9940(*puVar5,uVar6);
    }
    local_8 = (uint)local_8._1_3_ << 8;
    FUN_006c8eb0(local_1c);
  }
  local_8 = 0xffffffff;
  FUN_006c8d50();
  ExceptionList = local_10;
  return;
}

