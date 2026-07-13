
void __thiscall FUN_0083fec0(undefined4 param_1,undefined2 *param_2)

{
  short sVar1;
  uint uVar2;
  undefined2 *puVar3;
  int iVar4;
  short *psVar5;
  undefined4 local_34;
  undefined4 local_30;
  undefined2 *local_2c;
  void *local_28 [5];
  uint local_14;
  uint local_10;
  void *local_c;
  undefined1 *puStack_8;
  uint local_4;
  
  puStack_8 = &LAB_008655b1;
  local_c = ExceptionList;
  local_10 = DAT_008e7000 ^ (uint)&local_34;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xffffffc0;
  ExceptionList = &local_c;
  local_2c = param_2;
  *(undefined4 *)(param_2 + 10) = 7;
  *(undefined4 *)(param_2 + 8) = 0;
  *param_2 = 0;
  local_4 = 0;
  local_30 = 1;
  *(undefined4 *)(param_2 + 0xc) = param_1;
  FUN_008409e0(param_1,param_2 + 0xe,&local_34,0xffffffff,uVar2);
  puVar3 = (undefined2 *)FUN_008417a0(local_28,*(undefined4 *)(param_2 + 0xe),local_34);
  local_4 = 1;
  if (param_2 != puVar3) {
    FID_conflict_assign(puVar3,0,0xffffffff);
  }
  local_4 = local_4 & 0xffffff00;
  if (7 < local_14) {
    operator_delete(local_28[0]);
  }
  if (*(short *)PTR_DAT_008e7024 == 0) {
    iVar4 = 0;
  }
  else {
    psVar5 = (short *)PTR_DAT_008e7024;
    do {
      sVar1 = *psVar5;
      psVar5 = psVar5 + 1;
    } while (sVar1 != 0);
    iVar4 = (int)psVar5 - (int)(PTR_DAT_008e7024 + 2) >> 1;
  }
  iVar4 = FUN_00840080(0,*(undefined4 *)(param_2 + 8),PTR_DAT_008e7024,iVar4);
  if (iVar4 == 0) {
    if (*(short *)PTR_DAT_008e7020 == 0) {
      iVar4 = 0;
    }
    else {
      psVar5 = (short *)PTR_DAT_008e7020;
      do {
        sVar1 = *psVar5;
        psVar5 = psVar5 + 1;
      } while (sVar1 != 0);
      iVar4 = (int)psVar5 - (int)(PTR_DAT_008e7020 + 2) >> 1;
    }
    FUN_0083fdc0(PTR_DAT_008e7020,iVar4);
  }
  ExceptionList = local_c;
  FUN_0083e885();
  return;
}

