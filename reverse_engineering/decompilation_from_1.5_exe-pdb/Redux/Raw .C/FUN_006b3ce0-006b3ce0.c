
void FUN_006b3ce0(int param_1)

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
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084762c;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  iVar2 = get(uVar1);
  if (iVar2 != 0) {
    if (param_1 == 0) {
      get(uVar1);
      FUN_006ae1e0();
      get();
      FUN_006ac600();
    }
    else {
      get(uVar1);
      FUN_006ae220();
      pvVar3 = operator_new(0xc);
      local_8 = 0;
      if (pvVar3 == (void *)0x0) {
        local_1c = 0;
      }
      else {
        uVar6 = 0;
        uVar4 = get(0);
        puVar5 = (undefined4 *)FUN_00447eb0(uVar4);
        local_1c = FUN_006d9940(*puVar5,uVar6);
      }
      local_8 = 0xffffffff;
      FUN_006c8eb0(local_1c);
    }
  }
  ExceptionList = local_10;
  return;
}

