
void FUN_00841590(undefined4 ***param_1)

{
  uint uVar1;
  undefined4 uVar2;
  int iVar3;
  void **ppvVar4;
  undefined4 ***pppuVar5;
  uint local_60;
  undefined4 **local_5c;
  undefined4 **local_58 [5];
  uint local_44;
  void *local_40 [4];
  undefined4 local_30;
  uint local_2c;
  void *local_28;
  undefined4 local_18;
  uint local_14;
  uint local_10;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_008658e2;
  local_c = ExceptionList;
  local_10 = DAT_008e7000 ^ (uint)&local_60;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xffffff94;
  ExceptionList = &local_c;
  local_5c = param_1;
  local_60 = 0;
  FUN_008405e0(local_58);
  local_4 = 0;
  uVar2 = FUN_00840370(uVar1);
  iVar3 = FUN_00840110(uVar2);
  if (iVar3 != 0) {
    uVar2 = FUN_008402e0();
    iVar3 = FUN_00840110(uVar2);
    if (iVar3 != 0) {
      local_5c = (undefined4 ***)0x2e;
      iVar3 = FUN_00841340(&local_5c,0xffffffff,1);
      if (iVar3 == -1) {
        local_2c = 7;
        local_40[0] = (void *)((uint)local_40[0] & 0xffff0000);
        local_30 = 0;
        FID_conflict_assign(local_58,0,0xffffffff);
        ppvVar4 = local_40;
        local_4 = CONCAT31(local_4._1_3_,2);
        uVar1 = 2;
      }
      else {
        pppuVar5 = local_58;
        if (7 < local_44) {
          pppuVar5 = (undefined4 ***)local_58[0];
        }
        ppvVar4 = (void **)FUN_0083f6d0(pppuVar5,(int)pppuVar5 + iVar3 * 2);
        local_4 = 3;
        uVar1 = 4;
      }
      local_60 = uVar1;
      FUN_0083f8e0(ppvVar4);
      if ((uVar1 & 4) != 0) {
        uVar1 = uVar1 & 0xfffffffb;
        if (7 < local_14) {
          operator_delete(local_28);
        }
        local_14 = 7;
        local_18 = 0;
        local_28 = (void *)((uint)local_28 & 0xffff0000);
      }
      if ((uVar1 & 2) != 0) {
        if (7 < local_2c) {
          operator_delete(local_40[0]);
        }
        local_2c = 7;
        local_30 = 0;
        local_40[0] = (void *)((uint)local_40[0] & 0xffff0000);
      }
      goto LAB_0084175c;
    }
  }
  param_1[5] = (undefined4 **)0x7;
  param_1[4] = (undefined4 **)0x0;
  *(undefined2 *)param_1 = 0;
  local_4 = CONCAT31(local_4._1_3_,1);
  if (param_1 != local_58) {
    if ((undefined4 **)0x7 < param_1[5]) {
      operator_delete(*param_1);
    }
    param_1[5] = (undefined4 **)0x7;
    param_1[4] = (undefined4 **)0x0;
    *(undefined2 *)param_1 = 0;
    FID_conflict__Assign_rv(local_58);
  }
LAB_0084175c:
  if (7 < local_44) {
    operator_delete(local_58[0]);
  }
  ExceptionList = local_c;
  FUN_0083e885();
  return;
}

