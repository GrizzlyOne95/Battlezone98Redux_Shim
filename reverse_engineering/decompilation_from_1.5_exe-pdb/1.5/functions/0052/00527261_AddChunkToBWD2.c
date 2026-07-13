/*
 * Entry: 00527261
 * Name: AddChunkToBWD2
 * Namespace: Global
 * Signature: long AddChunkToBWD2(void * param_1, char * param_2, long param_3, void * param_4, ulong param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

long __cdecl AddChunkToBWD2(void *param_1,char *param_2,long param_3,void *param_4,ulong param_5)

{
  size_t sVar1;
  uint uVar2;
  uint local_10;
  int local_c;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  local_10 = ((param_3 & 0xffU) << 8 | param_3 >> 8 & 0xffU) << 0x10 | param_3 >> 0x18 & 0xffU |
             param_3 >> 8 & 0xff00U;
  local_c = param_5 + 8;
  sVar1 = fwrite(&local_10,1,8,param_1);
  if (sVar1 == 8) {
    if (param_4 == (void *)0x0) {
      uVar2 = 1;
    }
    else {
      sVar1 = fwrite(param_4,1,param_5,param_1);
      uVar2 = (uint)(sVar1 == param_5);
    }
    if (uVar2 != 0) {
      return uVar2;
    }
  }
  DEBUG_systemWarning("Error writing %s");
  return 0;
}
