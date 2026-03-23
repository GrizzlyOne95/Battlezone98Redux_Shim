
void FUN_00709028(void)

{
  char cVar1;
  basic_ostream<char,struct_std::char_traits<char>_> *pbVar2;
  undefined4 uVar3;
  int iVar4;
  int unaff_EBP;
  int iStack_18;
  char *pcStack_14;
  uint uVar5;
  uint uVar6;
  
  *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
  if (*(uint *)(unaff_EBP + 0xc) < *(uint *)(unaff_EBP + -0xc4)) {
    FUN_006d47b0();
    make_error_code();
    FUN_006daf10();
  }
  else {
    cVar1 = FUN_006d4590();
    if (cVar1 != '\0') {
      FUN_00574400();
      *(undefined4 *)(unaff_EBP + -4) = 3;
      if (unaff_EBP == 0x240) {
        uRam00000168 = 0;
      }
      else {
        *(int *)(unaff_EBP + -0xd8) = unaff_EBP + -0x230;
      }
      uVar6 = *(uint *)(unaff_EBP + -0xc4);
      uVar5 = *(uint *)(unaff_EBP + 0xc);
      pcStack_14 = "bytes_transferred: ";
      iStack_18 = *(int *)(unaff_EBP + -0xd8);
      pbVar2 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590();
      pcStack_14 = (char *)0x70910f;
      std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar2,uVar5);
      pcStack_14 = (char *)0x709115;
      pbVar2 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590();
      std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar2,uVar6);
      FUN_004bc590();
      uVar3 = GetPolicy();
      *(undefined4 *)(unaff_EBP + -0x114) = uVar3;
      *(undefined4 *)(unaff_EBP + -0x100) = *(undefined4 *)(unaff_EBP + -0x114);
      *(undefined1 *)(unaff_EBP + -4) = 4;
      FUN_006d4480();
      *(undefined1 *)(unaff_EBP + -4) = 3;
      ~basic_string<>();
      *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
      FUN_00417f10();
    }
    cVar1 = FUN_006b8190();
    if (cVar1 == '\0') {
      *(code **)(unaff_EBP + -0xec) = FUN_00708d60;
      *(undefined4 *)(unaff_EBP + -0xe8) = 0;
      uVar3 = FUN_006e1540();
      *(undefined4 *)(unaff_EBP + -0xf4) = uVar3;
      *(undefined4 *)(unaff_EBP + -0xf8) = *(undefined4 *)(unaff_EBP + -0xf4);
      *(undefined4 *)(unaff_EBP + -4) = 0xb;
      pcStack_14 = *(char **)(unaff_EBP + -0xec);
      iStack_18 = unaff_EBP + -400;
      uVar3 = FUN_0070a660();
      *(undefined4 *)(unaff_EBP + -0xfc) = uVar3;
      *(undefined4 *)(unaff_EBP + -0x11c) = *(undefined4 *)(unaff_EBP + -0xfc);
      *(undefined1 *)(unaff_EBP + -4) = 0xc;
      *(int **)(unaff_EBP + -300) = &iStack_18;
      uVar3 = FUN_0070a6c0(*(undefined4 *)(unaff_EBP + -0x11c));
      *(undefined4 *)(unaff_EBP + -0x148) = uVar3;
      FUN_006ffbc0(1,*(int *)(unaff_EBP + -0xc0) + 0xa30,0x4000);
      *(undefined1 *)(unaff_EBP + -4) = 0xb;
      ~input_processor<>();
      *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
      FUN_006ca8c0();
    }
    else {
      FUN_007146b0();
      cVar1 = FUN_006ab7d0();
      if (cVar1 == '\0') {
        cVar1 = FUN_006ab7d0();
        if (cVar1 != '\0') {
          uVar3 = FUN_00421ec0();
          *(undefined4 *)(unaff_EBP + -0xe0) = uVar3;
          iVar4 = (**(code **)(**(int **)(unaff_EBP + -0xe0) + 4))();
          if (iVar4 == 0) {
            if ((uint)(*(int *)(unaff_EBP + 0xc) - *(int *)(unaff_EBP + -0xc4)) < 8) {
              FUN_006d08b0();
              FUN_006b9910();
              make_error_code();
              FUN_00715820();
              goto LAB_00709647;
            }
            basic_string<>();
            *(undefined4 *)(unaff_EBP + -4) = 5;
            uVar3 = FUN_00716260();
            *(undefined4 *)(unaff_EBP + -0x108) = uVar3;
            *(undefined4 *)(unaff_EBP + -0x110) = *(undefined4 *)(unaff_EBP + -0x108);
            *(undefined1 *)(unaff_EBP + -4) = 6;
            FUN_006b7810();
            *(undefined1 *)(unaff_EBP + -4) = 5;
            ~basic_string<>();
            *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
            ~basic_string<>();
            *(int *)(unaff_EBP + -0xc4) = *(int *)(unaff_EBP + -0xc4) + 8;
          }
        }
        cVar1 = FUN_006d4590();
        if (cVar1 != '\0') {
          uVar3 = FUN_006b87d0();
          *(undefined4 *)(unaff_EBP + -0x118) = uVar3;
          *(undefined4 *)(unaff_EBP + -0x120) = *(undefined4 *)(unaff_EBP + -0x118);
          *(undefined4 *)(unaff_EBP + -4) = 7;
          FUN_006d4480();
          *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
          ~basic_string<>();
          basic_string<>();
          *(undefined4 *)(unaff_EBP + -4) = 8;
          FUN_006b7490();
          cVar1 = FUN_0041f890();
          if (cVar1 == '\0') {
            *(undefined4 *)(unaff_EBP + -0xdc) = 1;
          }
          else {
            *(undefined4 *)(unaff_EBP + -0xdc) = 0;
          }
          *(undefined1 *)(unaff_EBP + -0xc5) = *(undefined1 *)(unaff_EBP + -0xdc);
          *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
          ~basic_string<>();
          if (*(char *)(unaff_EBP + -0xc5) != '\0') {
            basic_string<>();
            *(undefined4 *)(unaff_EBP + -4) = 9;
            FUN_006b7490();
            uVar3 = FUN_006b6520();
            *(undefined4 *)(unaff_EBP + -0xe4) = uVar3;
            *(undefined4 *)(unaff_EBP + -0xf0) = *(undefined4 *)(unaff_EBP + -0xe4);
            *(undefined1 *)(unaff_EBP + -4) = 10;
            FUN_006d4480();
            *(undefined1 *)(unaff_EBP + -4) = 9;
            ~basic_string<>();
            *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
            ~basic_string<>();
          }
        }
        FUN_006da2a0();
        *(int *)(*(int *)(unaff_EBP + -0xc0) + 0x4a30) =
             *(int *)(unaff_EBP + 0xc) - *(int *)(unaff_EBP + -0xc4);
        *(undefined4 *)(*(int *)(unaff_EBP + -0xc0) + 0xa24) = 6;
        FUN_00714970();
        if ((*(char *)(*(int *)(unaff_EBP + -0xc0) + 0x4c30) == '\0') ||
           (*(int *)(*(int *)(unaff_EBP + -0xc0) + 0x4c34) == 0)) {
          FUN_00715290();
        }
      }
      else {
        FUN_00715820();
      }
    }
  }
LAB_00709647:
  ExceptionList = *(void **)(unaff_EBP + -0xc);
  FUN_0083e885();
  return;
}

