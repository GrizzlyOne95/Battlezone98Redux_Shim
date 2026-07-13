
void FUN_007d64a0(char *param_1)

{
  undefined2 uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  undefined4 uVar5;
  char local_408 [1024];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  if (DAT_0094671c == 0) {
    DAT_0094671c = 1;
    iVar2 = _vsnprintf(local_408,0x400,param_1,&stack0x00000008);
    uVar5 = 0;
    local_408[iVar2] = '\n';
    uVar3 = iVar2 + 1;
    uVar4 = uVar3;
    if (0x3ff < uVar3) {
      ___report_rangecheckfailure(uVar3,0);
    }
    local_408[uVar4] = '\0';
    FUN_007d6a70(local_408);
    uVar1 = FUN_007d62a0();
    FUN_007d62e0(0xd,uVar4,uVar5,uVar1);
    FUN_007d6270(local_408,uVar3);
    FUN_007d62e0(uVar1);
    FUN_00623ff0();
    FUN_00619fd0(local_408,s_BattleZone_Error_008f1698);
                    /* WARNING: Subroutine does not return */
    exit(0x70);
  }
  FUN_0083e885();
  return;
}

