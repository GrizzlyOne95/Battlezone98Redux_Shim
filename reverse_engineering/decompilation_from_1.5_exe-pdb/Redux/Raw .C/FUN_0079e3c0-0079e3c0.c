
void FUN_0079e3c0(void)

{
  int iVar1;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> abStack_2c [8];
  undefined4 uStack_24;
  code *pcStack_20;
  code *pcStack_1c;
  code *pcStack_18;
  undefined4 local_14;
  undefined1 *local_10;
  int local_c;
  int local_8;
  
  pcStack_18 = (code *)0x79e3d7;
  iVar1 = FUN_006cc050();
  if (iVar1 == 4) {
    *(undefined1 *)(local_8 + 0x1fc) = 1;
    *(undefined1 *)(local_8 + 0x1fd) = 0;
    pcStack_18 = (code *)0x0;
    pcStack_1c = (code *)0x79e404;
    FUN_007d05c0();
    pcStack_18 = (code *)0x79e409;
    iVar1 = FUN_004344a0();
    if (iVar1 == 2) {
      pcStack_18 = (code *)0x79e41c;
      local_c = FUN_0073bd10();
      if (local_c != 0) {
        pcStack_18 = (code *)0x79e433;
        FUN_007d0460();
        local_10 = abStack_2c;
        local_14 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                   ::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                             (abStack_2c,
                              (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                               *)(local_c + 0x2c));
        FUN_0079dab0();
      }
    }
    else {
      pcStack_18 = FUN_0079d750;
      pcStack_1c = FUN_0079d740;
      pcStack_20 = FUN_0079d730;
      uStack_24 = 0x79e474;
      FUN_007d0520();
      pcStack_18 = (code *)0x4;
      pcStack_1c = (code *)0x79e484;
      FUN_007d3f20();
      pcStack_18 = (code *)0x89ecac;
      pcStack_1c = (code *)0x89d748;
      pcStack_20 = (code *)0x79e493;
      pcStack_18 = (code *)FUN_0081cb40();
      pcStack_1c = (code *)0x79e4a5;
      FUN_007d0570();
      pcStack_18 = (code *)0x1;
      pcStack_1c = (code *)0x79e4c0;
      (**(code **)(**(int **)(local_8 + 0x1c0) + 0x24))();
      pcStack_1c = (code *)0x0;
      pcStack_20 = (code *)0x79e4d0;
      FUN_007d05c0();
      pcStack_1c = (code *)0x0;
      pcStack_20 = (code *)0x79e4eb;
      (**(code **)(**(int **)(local_8 + 0x1bc) + 0x24))();
    }
  }
  return;
}

