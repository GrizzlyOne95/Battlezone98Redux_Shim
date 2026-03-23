
void FUN_007ab830(void)

{
  ushort in_FPUControlWord;
  float10 fVar1;
  undefined4 extraout_var;
  
  fVar1 = (float10)FUN_007cc320();
  *(char *)(DAT_0094672c + 0x2c) = (char)(int)ROUND(fVar1);
  FUN_0043a910(*(undefined1 *)(DAT_0094672c + 0x2a),*(undefined1 *)(DAT_0094672c + 0x2b),
               *(undefined1 *)(DAT_0094672c + 0x2c),(int)ROUND(fVar1),in_FPUControlWord | 0xc00,
               extraout_var);
  FUN_00437c50(*(undefined1 *)(DAT_0094672c + 0x2c));
  FUN_0043a170(0);
  return;
}

