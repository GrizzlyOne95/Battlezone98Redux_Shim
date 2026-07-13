/*
 * Entry: 00548546
 * Name: convert
 * Namespace: Global
 * Signature: uchar convert(uchar param_1, uchar param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uchar __cdecl convert(uchar param_1,uchar param_2)

{
  char cVar1;
  char cVar2;
  
  if ((byte)(param_1 - 0x30) < 10) {
    cVar1 = '\0';
  }
  else {
    cVar1 = -0x57;
  }
  if ((byte)(param_2 - 0x30) < 10) {
    cVar2 = -0x30;
  }
  else {
    cVar2 = -0x57;
  }
  return (param_1 + cVar1) * '\x10' | param_2 + cVar2;
}
