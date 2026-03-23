
/* WARNING: Function: __alloca_probe replaced with injection: alloca_probe */

void FUN_004afeb0(undefined4 param_1)

{
  int *piVar1;
  char *pcVar2;
  char local_1008 [4096];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  sprintf(local_1008,"%s%s%s",&DAT_02cf1000,&DAT_00871328,param_1);
  FUN_004afe80();
  DAT_009174e4 = (int)fopen(local_1008,"wt");
  if ((FILE *)DAT_009174e4 == (FILE *)0x0) {
    pcVar2 = local_1008;
    piVar1 = _errno();
    FUN_007d6a70("crc32openlog: error %d when opening \"%s\"\n",*piVar1,pcVar2);
  }
  FUN_0083e885();
  return;
}

