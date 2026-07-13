/*
 * Entry: 00550333
 * Name: SaveChatColors
 * Namespace: Global
 * Signature: void SaveChatColors(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl SaveChatColors(void)

{
  uint uVar1;
  ChatColor *pCVar2;
  char local_48 [64];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  pCVar2 = ChatColor;
  do {
    uVar1 = pCVar2->Value;
    sprintf(local_48,"\"%d %d %d\"",uVar1 & 0xff,uVar1 >> 8 & 0xff,uVar1 >> 0x10 & 0xff);
    WritePrivateProfileStringA("Chat",pCVar2->Name,local_48,shellCfgName);
    pCVar2 = pCVar2 + 1;
  } while ((int)pCVar2 < 0x633c18);
  return;
}
