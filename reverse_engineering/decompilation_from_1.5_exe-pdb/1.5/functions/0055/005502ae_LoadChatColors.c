/*
 * Entry: 005502ae
 * Name: LoadChatColors
 * Namespace: Global
 * Signature: void LoadChatColors(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl LoadChatColors(void)

{
  int iVar1;
  ulong *puVar2;
  undefined1 local_54 [4];
  undefined1 local_50 [4];
  undefined1 local_4c [4];
  CHAR local_48 [64];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  puVar2 = &ChatColor[0].Value;
  do {
    GetPrivateProfileStringA
              ("Chat",((ChatColor *)(puVar2 + -1))->Name,(LPCSTR)0x0,local_48,0x40,shellCfgName);
    iVar1 = sscanf(local_48,"%d %d %d",local_50,local_4c,local_54);
    if (iVar1 == 3) {
      *puVar2 = (uint)CONCAT21(CONCAT11(local_54[0],local_4c[0]),local_50[0]);
    }
    puVar2 = puVar2 + 2;
  } while ((int)puVar2 < 0x633c1c);
  return;
}
