
void __fastcall FUN_00576480(int param_1)

{
  char cVar1;
  undefined2 uVar2;
  int iVar3;
  undefined4 uVar4;
  undefined2 local_28;
  undefined4 local_26;
  undefined4 local_22;
  undefined4 local_1e;
  undefined4 local_1a;
  undefined4 local_16;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_28 = 0x5050;
  if (*(char *)(param_1 + 0x8c) == '\0') {
    local_22 = 0;
    local_16 = 0;
    local_1e = 0;
  }
  else {
    local_22 = *(undefined4 *)(param_1 + 4);
    if (*(int *)(param_1 + 4) == 0) {
      local_16 = 1;
    }
    else {
      local_16 = *(undefined4 *)(param_1 + 8);
    }
    local_1e = FUN_00822dd0();
  }
  local_1a = FUN_00575f80();
  local_26 = FUN_00822e10(1);
  *(undefined4 *)(param_1 + 0x4c) = local_26;
  iVar3 = FUN_007659f0();
  if (iVar3 != 0) {
    cVar1 = FUN_00759710(param_1 + 0x30,&local_28,0x16,0);
    if ((cVar1 != '\0') && (DAT_009180d8 != 0)) {
      uVar2 = FUN_0056f920();
      uVar4 = FUN_0081e820("PING SENT off = %lu dl = %lu mst = %lu hst = %lu to player %d\n",
                           local_22,local_1a,local_26,local_1e,uVar2);
      FUN_0081e710(uVar4);
    }
  }
  *(int *)(param_1 + 0x1b0) = *(int *)(param_1 + 0x1b0) << 1;
  FUN_0083e885();
  return;
}

