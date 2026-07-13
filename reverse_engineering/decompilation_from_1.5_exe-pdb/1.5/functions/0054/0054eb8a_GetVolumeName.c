/*
 * Entry: 0054eb8a
 * Name: GetVolumeName
 * Namespace: Global
 * Signature: char * GetVolumeName(char param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

char * __cdecl GetVolumeName(char param_1)

{
  BOOL BVar1;
  DWORD local_54;
  DWORD local_50;
  DWORD local_4c;
  CHAR local_48 [32];
  char local_28;
  undefined3 uStack_27;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  _local_28 = CONCAT31(0x5c3a,param_1);
  BVar1 = GetVolumeInformationA
                    (&local_28,VolumeName,0x20,&local_4c,&local_50,&local_54,local_48,0x20);
  return (char *)(-(uint)(BVar1 != 0) & 0xc90620);
}
