
void __thiscall FUN_0045b820(uint *param_1,int param_2)

{
  void *pvVar1;
  uint uVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  void *local_28;
  uint local_18;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008470ec;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  uVar2 = param_2 + param_1[3] & param_1[4];
  if (param_1[1] < uVar2) {
    pvVar1 = (void *)param_1[2];
    local_28 = (void *)FUN_0083d92c(-(uint)((int)((ulonglong)uVar2 * 0x28 >> 0x20) != 0) |
                                    (uint)((ulonglong)uVar2 * 0x28),
                                    DAT_008e7000 ^ (uint)&stack0xfffffffc);
    local_8 = 0;
    if (local_28 == (void *)0x0) {
      local_28 = (void *)0x0;
    }
    else {
      _vector_constructor_iterator_(local_28,0x28,uVar2,FUN_00459600);
    }
    local_8 = 0xffffffff;
    param_1[2] = (uint)local_28;
    if (pvVar1 != (void *)0x0) {
      for (local_18 = 0; local_18 < *param_1; local_18 = local_18 + 1) {
        puVar4 = (undefined4 *)(local_18 * 0x28 + (int)pvVar1);
        puVar5 = (undefined4 *)(param_1[2] + local_18 * 0x28);
        for (iVar3 = 10; iVar3 != 0; iVar3 = iVar3 + -1) {
          *puVar5 = *puVar4;
          puVar4 = puVar4 + 1;
          puVar5 = puVar5 + 1;
        }
      }
      operator_delete__(pvVar1);
    }
    param_1[1] = uVar2;
  }
  ExceptionList = local_10;
  return;
}

