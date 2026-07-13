/*
 * Entry: 0054d771
 * Name: DrawCheckNum
 * Namespace: Global
 * Signature: void DrawCheckNum(long param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl DrawCheckNum(long param_1)

{
  char cVar1;
  char *pcVar2;
  char local_14 [12];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  sprintf(local_14,"%05d-%03d",param_1 / 1000,param_1 % 1000);
  SelectObject((HDC)mInfo.dc,mInfo.checkNumFont);
  if ((UserProfilePtr->graphicDetail).resolution < 6) {
    pcVar2 = local_14;
    do {
      cVar1 = *pcVar2;
      pcVar2 = pcVar2 + 1;
    } while (cVar1 != '\0');
    TextOutA((HDC)mInfo.dc,0xe2,0x3c,local_14,(int)pcVar2 - (int)(local_14 + 1));
  }
  return;
}
