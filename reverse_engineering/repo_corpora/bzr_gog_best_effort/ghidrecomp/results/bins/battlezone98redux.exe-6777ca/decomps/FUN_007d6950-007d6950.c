
void FUN_007d6950(char *param_1)

{
  undefined2 uVar1;
  int iVar2;
  undefined4 uVar3;
  char local_408 [1024];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  iVar2 = _vsnprintf(local_408,0x400,param_1,&stack0x00000008);
  local_408[iVar2] = '\n';
  if (0x3ff < iVar2 + 1U) {
    ___report_rangecheckfailure();
  }
  local_408[iVar2 + 1] = '\0';
  FUN_007d6a70(local_408);
  uVar1 = FUN_007d62a0();
  FUN_007d62e0(0xc);
  FUN_007d6270(local_408,iVar2 + 1U);
  FUN_007d62e0(uVar1);
  FUN_00623ff0();
  uVar3 = FUN_005d4a60(local_408,1);
  FUN_00623eb0(uVar3);
  FUN_0083e885();
  return;
}

