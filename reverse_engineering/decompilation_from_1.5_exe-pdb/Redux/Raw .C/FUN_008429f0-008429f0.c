
void FUN_008429f0(int *param_1,DWORD *param_2)

{
  int iVar1;
  uint uVar2;
  int *piVar3;
  DWORD DVar4;
  short ****ppppsVar5;
  undefined4 uVar6;
  DWORD DVar7;
  undefined4 local_ac;
  undefined4 local_a8;
  undefined4 local_a4;
  undefined4 local_a0;
  int local_98;
  undefined1 local_94 [8];
  short ***local_8c [4];
  int local_7c;
  uint local_78;
  void *local_74 [4];
  undefined4 local_64;
  uint local_60;
  undefined1 local_5c [8];
  undefined1 auStack_54 [68];
  uint local_10;
  void *local_c;
  undefined1 *puStack_8;
  undefined1 local_4;
  undefined3 uStack_3;
  
  puStack_8 = &LAB_00865b83;
  local_c = ExceptionList;
  local_10 = DAT_008e7000 ^ (uint)&local_ac;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xffffff44;
  ExceptionList = &local_c;
  local_78 = 7;
  local_7c = 0;
  local_8c[0] = (short ***)((uint)local_8c[0] & 0xffff0000);
  local_4 = 0;
  uStack_3 = 0;
  local_ac = 0;
  local_a8 = 0xffff;
  local_a4 = 0;
  local_a0 = 0xffff;
  FUN_0083e820(uVar2);
  piVar3 = (int *)FUN_00842550(local_94,*param_1 + 0x28,local_8c,&local_ac,&local_a4);
  iVar1 = *piVar3;
  local_98 = piVar3[1];
  do {
    if (iVar1 != 0) {
      FUN_00841100(local_74);
      local_4 = 1;
      FUN_00843850();
      if (param_2 == (DWORD *)0x0) {
        basic_string<>("boost::filesystem::directory_iterator::operator++");
        _local_4 = CONCAT31(uStack_3,2);
        uVar6 = FUN_0083e820();
        DVar4 = GetLastError();
        FUN_00841dd0(local_5c,local_74,DVar4,uVar6);
                    /* WARNING: Subroutine does not return */
        _CxxThrowException(auStack_54,(ThrowInfo *)&DAT_008d8618);
      }
      DVar4 = FUN_0083e820();
      DVar7 = GetLastError();
      *param_2 = DVar7;
      param_2[1] = DVar4;
      if (7 < local_60) {
        operator_delete(local_74[0]);
      }
      local_60 = 7;
      local_64 = 0;
      local_74[0] = (void *)((uint)local_74[0] & 0xffff0000);
LAB_00842c68:
      if (7 < local_78) {
        operator_delete(local_8c[0]);
      }
      ExceptionList = local_c;
      FUN_0083e885();
      return;
    }
    if (param_2 != (DWORD *)0x0) {
      *param_2 = 0;
      DVar4 = FUN_0083e820(uVar2);
      param_2[1] = DVar4;
    }
    if (*(int *)(*param_1 + 0x28) == 0) {
      FUN_00843850();
      goto LAB_00842c68;
    }
    ppppsVar5 = local_8c;
    if (7 < local_78) {
      ppppsVar5 = (short ****)local_8c[0];
    }
    if (*(short *)ppppsVar5 != 0x2e) {
LAB_00842bac:
      local_60 = 7;
      local_74[0] = (void *)((uint)local_74[0] & 0xffff0000);
      local_64 = 0;
      FID_conflict_assign(local_8c,0,0xffffffff);
      iVar1 = *param_1;
      local_4 = 3;
      FUN_00841260();
      FUN_0083fa10(local_74);
      *(undefined4 *)(iVar1 + 0x18) = local_ac;
      *(undefined4 *)(iVar1 + 0x1c) = local_a8;
      *(undefined4 *)(iVar1 + 0x20) = local_a4;
      *(undefined4 *)(iVar1 + 0x24) = local_a0;
      if (7 < local_60) {
        operator_delete(local_74[0]);
      }
      goto LAB_00842c68;
    }
    if (local_7c != 1) {
      ppppsVar5 = local_8c;
      if (7 < local_78) {
        ppppsVar5 = (short ****)local_8c[0];
      }
      if ((*(short *)((int)ppppsVar5 + 2) != 0x2e) || (local_7c != 2)) goto LAB_00842bac;
    }
    piVar3 = (int *)FUN_00842550(local_94,*param_1 + 0x28,local_8c,&local_ac,&local_a4);
    iVar1 = *piVar3;
    local_98 = piVar3[1];
  } while( true );
}

