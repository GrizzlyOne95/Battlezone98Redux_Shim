
void FUN_00841ef0(undefined4 param_1,int *param_2)

{
  uint uVar1;
  int iVar2;
  short ****ppppsVar3;
  undefined4 uVar4;
  int local_9c;
  int local_98;
  int local_94 [2];
  short ***local_8c [4];
  int local_7c;
  uint local_78;
  void *local_74 [4];
  int local_64;
  uint local_60;
  void *local_5c [2];
  undefined1 auStack_54 [8];
  undefined4 local_4c;
  uint local_48;
  uint local_10;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_00865a13;
  local_c = ExceptionList;
  local_10 = DAT_008e7000 ^ (uint)&local_9c;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xffffff58;
  ExceptionList = &local_c;
  FUN_008405e0(local_8c);
  local_4._0_1_ = 0;
  local_4._1_3_ = 0;
  if (local_7c == 1) {
    ppppsVar3 = local_8c;
    if (7 < local_78) {
      ppppsVar3 = (short ****)local_8c[0];
    }
    if (*(short *)ppppsVar3 != 0x2e) goto LAB_00841f70;
LAB_00841ffd:
    uVar4 = FUN_00841100(local_5c);
    local_4._0_1_ = 1;
    FUN_00841ef0(uVar4,param_2,uVar1);
    if (7 < local_48) {
      operator_delete(local_5c[0]);
    }
    local_48 = 7;
    local_4c = 0;
    local_5c[0] = (void *)((uint)local_5c[0] & 0xffff0000);
  }
  else {
    if (local_7c == 2) {
      ppppsVar3 = local_8c;
      if (7 < local_78) {
        ppppsVar3 = (short ****)local_8c[0];
      }
      if (*(short *)ppppsVar3 == 0x2e) {
        ppppsVar3 = local_8c;
        if (7 < local_78) {
          ppppsVar3 = (short ****)local_8c[0];
        }
        if (*(short *)((int)ppppsVar3 + 2) == 0x2e) goto LAB_00841ffd;
      }
    }
LAB_00841f70:
    local_9c = 0;
    local_98 = FUN_0083e820();
    FUN_008438a0(local_94,param_1,&local_9c);
    if (local_94[0] == 3) {
      if (param_2 != (int *)0x0) {
        *param_2 = 0;
        iVar2 = FUN_0083e820();
        param_2[1] = iVar2;
      }
      if (7 < local_78) {
        operator_delete(local_8c[0]);
      }
      goto LAB_00842151;
    }
    FUN_00841100(local_74);
    local_4._0_1_ = 2;
    if (((local_64 != 0) && (FUN_008438a0(local_94,local_74,&local_9c), local_94[0] == 1)) &&
       (FUN_00841ef0(local_74,&local_9c), local_9c != 0)) {
      if (param_2 == (int *)0x0) {
        basic_string<>("boost::filesystem::create_directories");
        local_4 = CONCAT31(local_4._1_3_,3);
        FUN_00841dd0(local_5c,local_74,local_9c,local_98);
                    /* WARNING: Subroutine does not return */
        _CxxThrowException(auStack_54,(ThrowInfo *)&DAT_008d8618);
      }
      *param_2 = local_9c;
      param_2[1] = local_98;
      FUN_004180b0();
      FUN_004180b0();
      goto LAB_00842151;
    }
    FUN_00842180(param_1,param_2);
    if (7 < local_60) {
      operator_delete(local_74[0]);
    }
    local_60 = 7;
    local_64 = 0;
    local_74[0] = (void *)((uint)local_74[0] & 0xffff0000);
  }
  if (7 < local_78) {
    operator_delete(local_8c[0]);
  }
LAB_00842151:
  ExceptionList = local_c;
  FUN_0083e885();
  return;
}

