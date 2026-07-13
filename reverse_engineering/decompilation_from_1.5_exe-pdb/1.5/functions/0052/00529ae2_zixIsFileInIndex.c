/*
 * Entry: 00529ae2
 * Name: zixIsFileInIndex
 * Namespace: Global
 * Signature: int zixIsFileInIndex(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl zixIsFileInIndex(char *param_1)

{
  void *pvVar1;
  char local_38 [48];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  to_zfsname(local_38,param_1);
  pvVar1 = bsearch(local_38,fentry,num_fentries,0x30,fentry_compare2);
  return (uint)(pvVar1 != (void *)0x0);
}
