
void FUN_00693900(undefined4 param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined1 local_160 [4];
  int local_15c;
  char local_158 [256];
  undefined1 local_58 [80];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  uVar1 = FUN_00693160();
  *(undefined4 *)(param_2 + 0x8c) = uVar1;
  FUN_006a6030("Loading UCP");
  for (local_15c = 0; local_15c < 0x20; local_15c = local_15c + 1) {
    *(undefined4 *)(*(int *)(param_2 + 0x90) + local_15c * 4) = 0;
  }
  iVar2 = FUN_0069d0a0(param_1,"unit_construction_program",local_160);
  FUN_006a6030("Account Count: %d.",iVar2);
  for (local_15c = 0; local_15c < iVar2; local_15c = local_15c + 1) {
    sprintf(local_158,"unit_construction_program[%d].account_name",local_15c);
    FUN_0069cfa0(param_1,local_158,local_160,local_58);
    sprintf(local_158,"unit_construction_program[%d].budget",local_15c);
    uVar1 = FUN_0069ce40(param_1,local_158,local_160);
    sprintf(local_158,"unit_construction_program[%d].max_reserve",local_15c);
    uVar3 = FUN_0069ce40(param_1,local_158,local_160);
    FUN_006a6030("Loading account %s with a budget of %d max reserve %d.",local_58,uVar1,uVar3);
    uVar4 = FUN_00693520(param_1,param_2,local_58);
    FUN_00693330(*(undefined4 *)(param_2 + 0x8c),local_15c,uVar4);
    if (local_15c != 0) {
      *(undefined4 *)(*(int *)(param_2 + 0x90) + local_15c * 4) = uVar1;
      *(undefined4 *)(*(int *)(param_2 + 0x94) + local_15c * 4) = uVar3;
    }
  }
  FUN_0083e885();
  return;
}

