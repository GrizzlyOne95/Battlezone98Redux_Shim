
/* WARNING: Function: __alloca_probe replaced with injection: alloca_probe */
/* WARNING: Removing unreachable block (ram,0x004ff405) */

void FUN_004ff3a0(char *param_1)

{
  uint uVar1;
  va_list _Args;
  char local_1008 [4095];
  undefined1 uStack_9;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  _Args = &stack0x00000008;
  uVar1 = _vsnprintf(local_1008,0x1000,param_1,_Args);
  uStack_9 = 0;
  if (0xfff < uVar1) {
    uVar1 = 0xfff;
  }
  FUN_007d6a70(local_1008,_Args,0xfff,uVar1);
  FUN_0083e885(0);
  return;
}

