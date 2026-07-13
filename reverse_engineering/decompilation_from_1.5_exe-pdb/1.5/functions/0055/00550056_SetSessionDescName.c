/*
 * Entry: 00550056
 * Name: SetSessionDescName
 * Namespace: Global
 * Signature: void SetSessionDescName(dp_s * param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl SetSessionDescName(dp_s *param_1,char *param_2)

{
  byte *pbVar1;
  byte *pbVar2;
  int iVar3;
  undefined4 local_78;
  undefined1 local_74 [55];
  byte local_3d [24];
  ulong local_25;
  byte local_14 [12];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  local_14[0] = 0;
  local_14[1] = 0;
  local_14[2] = 0;
  local_14[3] = 0;
  local_14[4] = 0;
  local_14[5] = 0;
  local_14[6] = 0;
  local_14[7] = 0;
  local_14[8] = 0;
  local_14[9] = 0;
  local_14[10] = 0;
  local_78 = 0x5f;
  strncpy((char *)local_14,param_2,10);
  dpGetSessionDesc(param_1,local_74,&local_78);
  iVar3 = 0;
  do {
    pbVar1 = local_14 + iVar3;
    if (*pbVar1 == 0x2e) {
      *pbVar1 = 0;
    }
    pbVar2 = local_3d + iVar3;
    *pbVar2 = *pbVar2 ^ (*pbVar2 ^ *pbVar1) & 0x7f;
    iVar3 = iVar3 + 1;
  } while (iVar3 < 10);
  crc32openlog("crc32mission.log");
  local_25 = crc32mission((char *)local_14);
  crc32closelog();
  Net_CRC = local_25;
  dpSetSessionDesc(param_1,local_74,0);
  return;
}
