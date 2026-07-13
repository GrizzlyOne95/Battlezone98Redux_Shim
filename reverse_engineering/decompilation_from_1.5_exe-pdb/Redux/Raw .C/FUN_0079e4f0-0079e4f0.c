
void __fastcall FUN_0079e4f0(int param_1)

{
  int iVar1;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> abStack_2c [8];
  undefined4 uStack_24;
  code *pcStack_20;
  code *pcStack_1c;
  
  iVar1 = FUN_006cc050();
  if (iVar1 == 4) {
    *(undefined1 *)(param_1 + 0x1fc) = 1;
    *(undefined1 *)(param_1 + 0x1fd) = 1;
    pcStack_1c = (code *)0x79e534;
    FUN_007d05c0();
    iVar1 = FUN_004344a0();
    if (iVar1 == 2) {
      iVar1 = FUN_0073bd10();
      if (iVar1 != 0) {
        FUN_007d0460();
        std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
        basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                  (abStack_2c,
                   (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                   (iVar1 + 0x2c));
        FUN_0079dab0();
      }
    }
    else {
      pcStack_1c = FUN_0079d740;
      pcStack_20 = FUN_0079d730;
      uStack_24 = 0x79e5a4;
      FUN_007d0520();
      pcStack_1c = (code *)0x79e5b4;
      FUN_007d3f20();
      pcStack_1c = (code *)0x89d748;
      pcStack_20 = (code *)0x79e5c3;
      FUN_0081cb40();
      pcStack_1c = (code *)0x79e5d5;
      FUN_007d0570();
      pcStack_1c = (code *)0x79e5e5;
      CMFCToolBarsCustomizeDialog::EnableUserDefinedToolbars
                (*(CMFCToolBarsCustomizeDialog **)(param_1 + 0x1c0),0xf);
      pcStack_1c = (code *)0x79e600;
      (**(code **)(**(int **)(param_1 + 0x1c0) + 0x24))();
      pcStack_1c = (code *)0x1;
      pcStack_20 = (code *)0x79e610;
      FUN_007d05c0();
      pcStack_1c = (code *)0x0;
      pcStack_20 = (code *)0x79e62b;
      (**(code **)(**(int **)(param_1 + 0x1bc) + 0x24))();
    }
  }
  return;
}

