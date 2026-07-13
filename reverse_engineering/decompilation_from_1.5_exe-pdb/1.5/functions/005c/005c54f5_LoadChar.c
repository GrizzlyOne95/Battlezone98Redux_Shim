/*
 * Entry: 005c54f5
 * Name: LoadChar
 * Namespace: Global
 * Signature: int LoadChar(LoadState * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl LoadChar(LoadState *param_1)

{
  uint in_ECX;
  
  LoadBlock((LoadState *)&stack0xfffffffb,(void *)0x1,in_ECX);
  return (int)(char)(in_ECX >> 0x18);
}
