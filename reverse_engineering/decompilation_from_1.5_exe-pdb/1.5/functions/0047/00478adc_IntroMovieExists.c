/*
 * Entry: 00478adc
 * Name: IntroMovieExists
 * Namespace: Global
 * Signature: int IntroMovieExists(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl IntroMovieExists(void)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  undefined1 local_138 [20];
  int local_124;
  char local_108 [80];
  undefined1 local_b8 [176];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_b8;
  if (needIntroMovie == 0) {
    uVar2 = 1;
  }
  else {
    cVar1 = CDDriveLetter();
    sprintf(local_108,"%c:\\movie\\intro.avi",(int)cVar1);
    iVar3 = stat64i32(local_108,local_138);
    if (iVar3 < 0) {
      cVar1 = CDDriveLetter();
      sprintf(local_108,"%c:\\bzone\\movie\\intro.avi",(int)cVar1);
      iVar3 = stat64i32(local_108,local_138);
      if (iVar3 < 0) {
        return 0;
      }
    }
    uVar2 = (uint)(16999999 < local_124);
  }
  return uVar2;
}
