
void __thiscall FUN_0083fa10(short *param_1,short *param_2)

{
  uint uVar1;
  short ****ppppsVar2;
  short *psVar3;
  short ***local_28 [4];
  undefined4 local_18;
  uint local_14;
  uint local_10;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_00865568;
  local_c = ExceptionList;
  local_10 = DAT_008e7000 ^ (uint)local_28;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xffffffd0;
  ExceptionList = &local_c;
  if (*(int *)(param_2 + 8) != 0) {
    if (param_1 == param_2) {
      local_14 = 7;
      local_18 = 0;
      local_28[0] = (short ***)((uint)local_28[0] & 0xffff0000);
      FID_conflict_assign(param_2,0,0xffffffff);
      local_4 = 0;
      ppppsVar2 = local_28;
      if (7 < local_14) {
        ppppsVar2 = (short ****)local_28[0];
      }
      if ((*(short *)ppppsVar2 != 0x2f) && (*(short *)ppppsVar2 != 0x5c)) {
        FUN_00840de0(uVar1);
      }
      FUN_0083fb60(local_28,0,0xffffffff);
      if (7 < local_14) {
        operator_delete(local_28[0]);
      }
    }
    else {
      psVar3 = param_2;
      if (7 < *(uint *)(param_2 + 10)) {
        psVar3 = *(short **)param_2;
      }
      if ((*psVar3 != 0x2f) && (*psVar3 != 0x5c)) {
        FUN_00840de0(uVar1);
      }
      FUN_0083fb60(param_2,0,0xffffffff);
    }
  }
  ExceptionList = local_c;
  FUN_0083e885();
  return;
}

