
void __thiscall FUN_006d1600(int param_1,int param_2)

{
  char cVar1;
  uint uVar2;
  undefined4 *puVar3;
  undefined1 *puVar4;
  undefined1 local_4c [4];
  undefined1 local_48 [4];
  undefined4 local_44;
  undefined4 local_40;
  void *local_3c;
  void *local_38;
  void *local_34;
  void *local_30;
  uint local_2c;
  undefined4 local_28;
  void *local_24;
  undefined1 local_20 [4];
  uint local_1c;
  uint local_18;
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085314c;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  if (param_2 != *(int *)(param_1 + 0x18)) {
    *(int *)(param_1 + 0x18) = param_2;
    local_14 = param_1;
    FID_conflict_begin(&local_28);
    local_2c = *(uint *)(local_14 + 0x18);
    local_24 = (void *)FUN_0083d92c(-(uint)((int)((ulonglong)local_2c * 8 >> 0x20) != 0) |
                                    (uint)((ulonglong)local_2c * 8),uVar2);
    local_8 = 0;
    if (local_24 == (void *)0x0) {
      local_30 = (void *)0x0;
    }
    else {
      _vector_constructor_iterator_(local_24,8,local_2c,SafeSQueue<>);
      local_30 = local_24;
    }
    local_34 = local_30;
    local_8 = 0xffffffff;
    local_3c = local_30;
    local_38 = *(void **)(local_14 + 0x14);
    operator_delete__(local_38);
    *(void **)(local_14 + 0x14) = local_3c;
    for (local_1c = 0; local_1c < *(uint *)(local_14 + 0x18); local_1c = local_1c + 1) {
      *(undefined4 *)(*(int *)(local_14 + 0x14) + 4 + local_1c * 8) = local_28;
      *(undefined4 *)(*(int *)(local_14 + 0x14) + local_1c * 8) =
           *(undefined4 *)(*(int *)(local_14 + 0x14) + 4 + local_1c * 8);
    }
    FUN_0042d8c0(local_20);
    while (cVar1 = FUN_00420f10(&local_28), cVar1 != '\0') {
      puVar3 = (undefined4 *)FUN_0042da60();
      local_18 = FUN_00417780(*puVar3);
      local_18 = local_18 % *(uint *)(local_14 + 0x18);
      cVar1 = FUN_004221b0(&local_28);
      if (cVar1 == '\0') {
        puVar4 = local_20;
        FUN_0042da80(puVar4);
        cVar1 = FUN_004221b0(puVar4);
        if (cVar1 == '\0') {
          puVar3 = (undefined4 *)FUN_00438c10(local_4c,0);
          local_40 = *puVar3;
          local_44 = *(undefined4 *)(*(int *)(local_14 + 0x14) + 4 + local_18 * 8);
          FUN_006d5150(local_44,local_14 + 4,local_40);
          FUN_0044f170();
        }
        else {
          FUN_0042da80();
        }
      }
      else {
        puVar3 = (undefined4 *)FUN_00438c10(local_48,0);
        *(undefined4 *)(*(int *)(local_14 + 0x14) + 4 + local_18 * 8) = *puVar3;
        *(undefined4 *)(*(int *)(local_14 + 0x14) + local_18 * 8) =
             *(undefined4 *)(*(int *)(local_14 + 0x14) + 4 + local_18 * 8);
      }
    }
  }
  ExceptionList = local_10;
  return;
}

