
/* WARNING: Function: __alloca_probe replaced with injection: alloca_probe */

void FUN_00790d40(void)

{
  char cVar1;
  undefined4 uStack_1f580;
  undefined4 uStack_1f578;
  undefined4 uStack_1f570;
  uint uStack_1f56c;
  undefined1 *puStack_1f568;
  undefined1 *puStack_1f564;
  undefined1 *puStack_1f560;
  undefined1 *puStack_1f55c;
  undefined1 *puStack_1f558;
  undefined1 *puStack_1f554;
  undefined4 uStack_1f550;
  undefined1 *puStack_1f54c;
  undefined4 uStack_1f548;
  undefined4 uStack_1f544;
  undefined1 *puStack_1f540;
  undefined4 uStack_1f53c;
  undefined4 uStack_1f538;
  undefined4 uStack_1f534;
  undefined1 *puStack_1f530;
  undefined1 *puStack_1f52c;
  undefined4 uStack_1f528;
  int iStack_1f524;
  undefined4 uStack_1f520;
  undefined4 uStack_1f51c;
  undefined4 uStack_1f518;
  int iStack_1f514;
  uint uStack_1f510;
  int iStack_1f50c;
  undefined1 auStack_1f508 [128000];
  undefined1 local_108 [256];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  puStack_1f55c = (undefined1 *)0x790d6e;
  uStack_1f510 = FUN_007cb0a0();
  puStack_1f55c = auStack_1f508;
  puStack_1f560 = (undefined1 *)(uStack_1f510 & 0xff);
  puStack_1f558 = (undefined1 *)&uStack_1f578;
  uStack_1f580 = 0x790d9f;
  uStack_1f550 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
                 basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                           ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                             *)&uStack_1f578,
                            (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                             *)(iStack_1f50c + 0x150));
  uStack_1f520 = FUN_004880e0();
  puStack_1f560 = (undefined1 *)0x790dbe;
  puStack_1f560 = (undefined1 *)FUN_0041f870();
  puStack_1f564 = (undefined1 *)0x790dc4;
  FUN_004889c0();
  puStack_1f52c = (undefined1 *)&uStack_1f570;
  uStack_1f578 = 0x790de6;
  uStack_1f534 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
                 basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                           ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                             *)&uStack_1f570,
                            (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                             *)(iStack_1f50c + 0x150));
  puStack_1f55c = (undefined1 *)FUN_00489670();
  puStack_1f560 = auStack_1f508;
  puStack_1f564 = (undefined1 *)0x790e27;
  uStack_1f518 = puStack_1f55c;
  (**(code **)(**(int **)(iStack_1f50c + 0x148) + 0x3c))();
  puStack_1f564 = local_108;
  puStack_1f568 = (undefined1 *)uStack_1f510;
  puStack_1f554 = (undefined1 *)&uStack_1f580;
  uStack_1f53c = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
                 basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                           ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                             *)&uStack_1f580,
                            (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                             *)(iStack_1f50c + 0x150));
  FUN_00489b60();
  puStack_1f564 = auStack_1f508;
  puStack_1f568 = local_108;
  uStack_1f56c = 0x790e72;
  FUN_004889c0();
  puStack_1f54c = (undefined1 *)&uStack_1f578;
  uStack_1f580 = 0x790e91;
  uStack_1f544 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
                 basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                           ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                             *)&uStack_1f578,
                            (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                             *)(iStack_1f50c + 0x150));
  puStack_1f564 = (undefined1 *)FUN_00489670();
  puStack_1f568 = auStack_1f508;
  uStack_1f56c = 0x790ed2;
  uStack_1f528 = puStack_1f564;
  (**(code **)(**(int **)(iStack_1f50c + 0x14c) + 0x3c))();
  if (uStack_1f510 != 0xffffffff) {
    uStack_1f56c = uStack_1f510 & 0xff;
    puStack_1f530 = &stack0xfffe0a7c;
    uStack_1f538 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                   ::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                             ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                               *)&stack0xfffe0a7c,
                              (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                               *)(iStack_1f50c + 0x150));
    iStack_1f524 = FUN_004880e0();
    uStack_1f56c = 0x790f2b;
    iStack_1f514 = iStack_1f524;
    cVar1 = FUN_00488d80();
    if (cVar1 == '\x01') {
      uStack_1f56c = *(undefined4 *)(iStack_1f514 + 0xac);
      uStack_1f570 = 0x790f55;
      FUN_007ccd20();
      uStack_1f56c = *(undefined4 *)(iStack_1f514 + 0xac);
      uStack_1f570 = 0x790f73;
      FUN_007ccd20();
      uStack_1f56c = uStack_1f510 & 0xff;
      puStack_1f540 = &stack0xfffe0a7c;
      uStack_1f548 = std::
                     basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
                     basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                               ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                                 *)&stack0xfffe0a7c,
                                (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                                 *)(iStack_1f50c + 0x150));
      uStack_1f51c = FUN_004880e0();
      uStack_1f56c = 0x790fb9;
      uStack_1f56c = FUN_0041f870();
      uStack_1f570 = 0x790fcb;
      FUN_007d2870();
    }
  }
  uStack_1f56c = 0x790fd5;
  FUN_0083e885();
  return;
}

