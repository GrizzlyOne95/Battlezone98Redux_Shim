
void __fastcall FUN_005fb500(int param_1)

{
  uint uVar1;
  void *pvVar2;
  int iVar3;
  int iVar4;
  undefined4 local_40;
  undefined4 local_38;
  undefined4 local_30;
  undefined4 local_24;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084d110;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  iVar3 = *(int *)(*(int *)(param_1 + 0x34) + 0x230);
  *(undefined4 *)(iVar3 + 0xc4) = 0;
  *(undefined4 *)(iVar3 + 200) = 0;
  if (*(int *)(param_1 + 0x3c) == 0) {
    pvVar2 = operator_new(0x14c);
    local_8 = 0;
    if (pvVar2 == (void *)0x0) {
      local_24 = 0;
    }
    else {
      local_24 = FUN_004e54c0(*(undefined4 *)(param_1 + 0x34),*(undefined4 *)(param_1 + 0x10),
                              *(undefined1 *)(param_1 + 0x40));
    }
    *(undefined4 *)(param_1 + 0x38) = local_24;
  }
  else {
    iVar3 = FUN_00462630(*(undefined4 *)(param_1 + 0x3c),uVar1);
    if (iVar3 == 0) {
      pvVar2 = operator_new(0x14c);
      local_8 = 3;
      if (pvVar2 == (void *)0x0) {
        local_40 = 0;
      }
      else {
        local_40 = FUN_004e54c0(*(undefined4 *)(param_1 + 0x34),*(undefined4 *)(param_1 + 0x10),0);
      }
      *(undefined4 *)(param_1 + 0x38) = local_40;
    }
    else {
      iVar4 = (*(code *)**(undefined4 **)(iVar3 + 0x18))();
      if ((*(int *)(iVar4 + 0x1c) == 3) && (*(int *)(iVar4 + 0x14) != 0x43504f44)) {
        pvVar2 = operator_new(0x15c);
        local_8 = 1;
        if (pvVar2 == (void *)0x0) {
          local_30 = 0;
        }
        else {
          local_30 = FUN_004e7830(*(undefined4 *)(param_1 + 0x34),iVar3);
        }
        *(undefined4 *)(param_1 + 0x38) = local_30;
      }
      else {
        pvVar2 = operator_new(0x14c);
        local_8 = 2;
        if (pvVar2 == (void *)0x0) {
          local_38 = 0;
        }
        else {
          local_38 = FUN_004e58d0(*(undefined4 *)(param_1 + 0x34),iVar3);
        }
        *(undefined4 *)(param_1 + 0x38) = local_38;
      }
    }
  }
  ExceptionList = local_10;
  return;
}

