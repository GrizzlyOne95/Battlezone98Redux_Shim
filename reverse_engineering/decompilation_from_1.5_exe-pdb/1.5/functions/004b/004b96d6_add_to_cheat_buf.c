/*
 * Entry: 004b96d6
 * Name: add_to_cheat_buf
 * Namespace: Global
 * Signature: int add_to_cheat_buf(short param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl add_to_cheat_buf(short param_1)

{
  int iVar1;
  
  if ((param_1 & 0xff00U) != 0x300) {
    return 0;
  }
  memmove(cheat_buf,cheat_buf + 1,0xe);
  iVar1 = tolower((ushort)param_1 & 0xff);
  cheat_buf[0xe] = (char)iVar1;
  return 1;
}
