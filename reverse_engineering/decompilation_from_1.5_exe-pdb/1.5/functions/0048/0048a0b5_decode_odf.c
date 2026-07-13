/*
 * Entry: 0048a0b5
 * Name: decode_odf
 * Namespace: Global
 * Signature: long64 decode_odf(uchar param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long64 __cdecl decode_odf(uchar param_1)

{
  byte in_AL;
  
  if ((0x7f < in_AL) && (in_AL < 0xe6)) {
    return CONCAT44(*(undefined4 *)(wrkmem + (uint)in_AL * 8 + 0x6fcd4),
                    *(undefined4 *)(wrkmem + (uint)in_AL * 8 + 0x6fcd0));
  }
  return 0;
}
