/*
 * Entry: 004bd3c2
 * Name: giddi_read_key
 * Namespace: Global
 * Signature: int giddi_read_key(short * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl giddi_read_key(short *param_1)

{
  short *psVar1;
  
  if (bufferOut == bufferIn) {
    *param_1 = 0;
  }
  else {
    psVar1 = keyboardBuffer + bufferOut;
    bufferOut = bufferOut + 1;
    *param_1 = *psVar1;
    if (bufferOut == 0x40) {
      bufferOut = 0;
    }
  }
  return 0;
}
