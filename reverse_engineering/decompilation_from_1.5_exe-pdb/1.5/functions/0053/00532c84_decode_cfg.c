/*
 * Entry: 00532c84
 * Name: decode_cfg
 * Namespace: Global
 * Signature: long64 decode_cfg(uchar param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long64 __cdecl decode_cfg(uchar param_1)

{
  byte in_AL;
  
  if ((0x7f < in_AL) && (in_AL < 0x97)) {
    return CONCAT44((&magnetBuildingClass._padding_)[(uint)in_AL * 2],
                    (&magnetBuildingClass._padding_)[(uint)in_AL * 2]);
  }
  return 0;
}
