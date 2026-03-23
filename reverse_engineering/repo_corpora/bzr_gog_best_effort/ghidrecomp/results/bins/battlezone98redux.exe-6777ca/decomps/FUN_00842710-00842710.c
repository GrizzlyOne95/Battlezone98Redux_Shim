
void FUN_00842710(int *param_1,short *param_2,undefined4 param_3)

{
  int *piVar1;
  short sVar2;
  int *piVar3;
  char cVar4;
  undefined4 uVar5;
  int iVar6;
  short ****ppppsVar7;
  int iVar8;
  short *psVar9;
  short *psVar10;
  undefined4 local_74;
  undefined4 local_70;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 local_64;
  int local_60 [2];
  void *local_58 [4];
  undefined4 local_48;
  uint local_44;
  short ***local_40 [4];
  int local_30;
  uint local_2c;
  void *local_28 [4];
  undefined4 local_18;
  uint local_14;
  uint local_10;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4._0_1_ = 0xff;
  local_4._1_3_ = 0xffffff;
  puStack_8 = &LAB_00865b30;
  local_c = ExceptionList;
  local_10 = DAT_008e7000 ^ (uint)&local_74;
  ExceptionList = &local_c;
  uVar5 = 0;
  if (*(int *)(param_2 + 8) == 0) {
    uVar5 = DAT_009150d0;
  }
  local_64 = param_3;
  cVar4 = FUN_00842d80(uVar5,param_2,param_3,"boost::filesystem::directory_iterator::construct",
                       DAT_008e7000 ^ (uint)&stack0xffffff7c);
  if (cVar4 != '\0') goto LAB_008429c9;
  local_2c = 7;
  local_30 = 0;
  local_40[0] = (short ***)((uint)local_40[0] & 0xffff0000);
  local_4 = 0;
  local_74 = 0;
  local_70 = 0xffff;
  local_6c = 0;
  local_68 = 0xffff;
  psVar10 = param_2;
  if (7 < *(uint *)(param_2 + 10)) {
    psVar10 = *(short **)param_2;
  }
  local_44 = 7;
  local_48 = 0;
  local_58[0] = (void *)((uint)local_58[0] & 0xffff0000);
  if (*psVar10 == 0) {
    iVar8 = 0;
  }
  else {
    psVar9 = psVar10;
    do {
      sVar2 = *psVar9;
      psVar9 = psVar9 + 1;
    } while (sVar2 != 0);
    iVar8 = (int)psVar9 - (int)(psVar10 + 1) >> 1;
  }
  FUN_0083fdc0(psVar10,iVar8);
  local_4._0_1_ = 1;
  FUN_008422e0(local_60,*param_1 + 0x28,local_58,local_40,&local_74,&local_6c);
  local_4._0_1_ = 0;
  if (7 < local_44) {
    operator_delete(local_58[0]);
  }
  if (local_60[0] == 0) {
    if (*(int *)(*param_1 + 0x28) == 0) {
      FUN_00843850();
    }
    else {
      local_44 = 7;
      local_58[0] = (void *)((uint)local_58[0] & 0xffff0000);
      local_48 = 0;
      FID_conflict_assign(local_40,0,0xffffffff);
      local_4._0_1_ = 2;
      iVar6 = FUN_00662ec0(local_28,param_2,local_58);
      iVar8 = *param_1;
      local_4 = CONCAT31(local_4._1_3_,3);
      if (iVar8 != iVar6) {
        FID_conflict_assign(iVar6,0,0xffffffff);
      }
      *(undefined4 *)(iVar8 + 0x18) = local_74;
      *(undefined4 *)(iVar8 + 0x1c) = local_70;
      *(undefined4 *)(iVar8 + 0x20) = local_6c;
      *(undefined4 *)(iVar8 + 0x24) = local_68;
      if (7 < local_14) {
        operator_delete(local_28[0]);
      }
      local_14 = 7;
      local_18 = 0;
      local_28[0] = (void *)((uint)local_28[0] & 0xffff0000);
      local_4._0_1_ = 0;
      if (7 < local_44) {
        operator_delete(local_58[0]);
      }
      ppppsVar7 = local_40;
      if (7 < local_2c) {
        ppppsVar7 = (short ****)local_40[0];
      }
      if (*(short *)ppppsVar7 == 0x2e) {
        if (local_30 != 1) {
          ppppsVar7 = local_40;
          if (7 < local_2c) {
            ppppsVar7 = (short ****)local_40[0];
          }
          if ((*(short *)((int)ppppsVar7 + 2) != 0x2e) || (local_30 != 2)) goto LAB_008429b6;
        }
        FUN_008429f0(param_1,param_3);
      }
    }
  }
  else {
    *param_1 = 0;
    piVar3 = (int *)param_1[1];
    param_1[1] = 0;
    if (piVar3 != (int *)0x0) {
      LOCK();
      iVar8 = piVar3[1] + -1;
      piVar3[1] = iVar8;
      UNLOCK();
      if (iVar8 == 0) {
        (**(code **)(*piVar3 + 4))();
        piVar1 = piVar3 + 2;
        LOCK();
        iVar8 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar8 == 1) {
          (**(code **)(*piVar3 + 8))();
        }
      }
    }
    FUN_00842d80(local_60[0],param_2,local_64,"boost::filesystem::directory_iterator::construct");
  }
LAB_008429b6:
  if (7 < local_2c) {
    operator_delete(local_40[0]);
  }
LAB_008429c9:
  ExceptionList = local_c;
  FUN_0083e885();
  return;
}

