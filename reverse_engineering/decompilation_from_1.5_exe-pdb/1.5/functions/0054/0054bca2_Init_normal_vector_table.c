/*
 * Entry: 0054bca2
 * Name: Init_normal_vector_table
 * Namespace: Global
 * Signature: void Init_normal_vector_table(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Init_normal_vector_table(void)

{
  uint uVar1;
  int iStack_10;
  
  uVar1 = 0;
  do {
    iStack_10 = (int)((ulonglong)
                      (1.0 / SQRT((double)((ulonglong)((uVar1 | 0x1ff00) << 0xd) << 0x20))) >> 0x20)
    ;
    rsqrt_lookup[uVar1] = (uchar)(iStack_10 + 0x400 >> 0xc);
    uVar1 = uVar1 + 1;
  } while ((int)uVar1 < 0x100);
  rsqrt_lookup[0x80] = 0xff;
  return;
}
