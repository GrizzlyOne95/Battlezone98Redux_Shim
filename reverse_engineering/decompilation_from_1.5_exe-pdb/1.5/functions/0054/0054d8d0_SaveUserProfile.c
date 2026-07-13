/*
 * Entry: 0054d8d0
 * Name: SaveUserProfile
 * Namespace: Global
 * Signature: void SaveUserProfile(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl SaveUserProfile(void)

{
  uint uVar1;
  FILE *_File;
  char local_10c;
  undefined1 local_10b [127];
  undefined1 local_8c [132];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_8c;
  local_10c = '\0';
  memset(local_10b,0,0x103);
  strcat_s(&local_10c,0x104,"BZPLYR.DEF");
  _File = fopen(&local_10c,"wb");
  if (_File != (FILE *)0x0) {
    uVar1 = UserProfilePtr->playOption;
    UserProfilePtr->playOption = uVar1 & 0xfffffcf0;
    fwrite(UserProfilePtr,1,0x74,_File);
    fclose(_File);
    UserProfilePtr->playOption = uVar1;
  }
  return;
}
