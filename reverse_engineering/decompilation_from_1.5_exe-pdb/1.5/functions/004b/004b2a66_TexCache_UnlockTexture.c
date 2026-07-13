/*
 * Entry: 004b2a66
 * Name: TexCache_UnlockTexture
 * Namespace: Global
 * Signature: void TexCache_UnlockTexture(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl TexCache_UnlockTexture(char *param_1)

{
  char cVar1;
  undefined4 *puVar2;
  char *pcVar3;
  _texcache *p_Var4;
  ushort uVar5;
  _texcache *unaff_ESI;
  undefined4 *puVar6;
  char local_18 [4];
  undefined1 auStack_14 [12];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  pcVar3 = param_1;
  do {
    cVar1 = *pcVar3;
    pcVar3[(int)(local_18 + -(int)param_1)] = cVar1;
    pcVar3 = pcVar3 + 1;
  } while (cVar1 != '\0');
  pcVar3 = strchr(local_18,0x2e);
  if (pcVar3 != (char *)0x0) {
    *pcVar3 = '\0';
  }
  puVar2 = (undefined4 *)&stack0xffffffe7;
  do {
    puVar6 = puVar2;
    puVar2 = (undefined4 *)((int)puVar6 + 1);
  } while (*(char *)((int)puVar6 + 1) != '\0');
  *(undefined4 *)((int)puVar6 + 1) = 0x6d71762e;
  *(undefined1 *)((int)puVar6 + 5) = 0;
  p_Var4 = find_texture(local_18);
  if (p_Var4 == (_texcache *)0x0) {
    UnlockItem(param_1);
  }
  else if ((p_Var4->count != 0) && (uVar5 = p_Var4->count - 1, p_Var4->count = uVar5, uVar5 == 0)) {
    add_to_purge(unaff_ESI);
  }
  return;
}
