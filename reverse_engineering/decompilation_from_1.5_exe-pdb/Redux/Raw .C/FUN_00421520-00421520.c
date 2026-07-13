
void __fastcall FUN_00421520(basic_streambuf<char,struct_std::char_traits<char>_> *param_1)

{
  char cVar1;
  uint _FileHandle;
  char *pcVar2;
  char *pcVar3;
  int iVar4;
  int iVar5;
  char *pcVar6;
  void *_Src;
  char *pcVar7;
  char **ppcVar8;
  char **ppcVar9;
  rsize_t _MaxCount;
  undefined1 local_70 [4];
  undefined1 local_6c [4];
  undefined1 local_68 [4];
  undefined1 local_64 [4];
  undefined1 local_60 [4];
  undefined4 local_5c;
  int local_58;
  int local_54;
  undefined4 local_50;
  char *local_4c;
  int local_48;
  int local_44;
  char *local_40;
  int local_3c;
  int local_38;
  undefined1 local_33;
  char local_32;
  char local_31;
  basic_streambuf<char,struct_std::char_traits<char>_> *local_30;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00845248;
  local_10 = ExceptionList;
  _FileHandle = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_30 = param_1;
  local_14 = _FileHandle;
  pcVar2 = std::basic_streambuf<char,struct_std::char_traits<char>_>::gptr(param_1);
  if (pcVar2 != (char *)0x0) {
    pcVar2 = std::basic_streambuf<char,struct_std::char_traits<char>_>::gptr(local_30);
    pcVar3 = std::basic_streambuf<char,struct_std::char_traits<char>_>::egptr(local_30);
    if (pcVar2 < pcVar3) {
      pcVar2 = std::basic_streambuf<char,struct_std::char_traits<char>_>::_Gninc(local_30);
      FUN_00417ab0(pcVar2);
      goto LAB_004217ed;
    }
  }
  if (*(int *)(local_30 + 0x50) == 0) {
    eof(_FileHandle);
  }
  else {
    FUN_00423580();
    if (*(int *)(local_30 + 0x40) == 0) {
      local_33 = 0;
      cVar1 = FUN_00417e60(&local_33,*(undefined4 *)(local_30 + 0x50));
      if (cVar1 == '\0') {
        local_48 = eof(_FileHandle);
      }
      else {
        local_48 = FUN_00417ab0(&local_33);
      }
    }
    else {
      basic_string<>();
      local_8 = 0;
LAB_00421601:
      do {
        local_44 = fgetc(*(FILE **)(local_30 + 0x50));
        if (local_44 == -1) {
          local_58 = eof(_FileHandle);
          local_8 = 0xffffffff;
          ~basic_string<>();
          goto LAB_004217ed;
        }
        std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::append
                  (local_2c,1,(char)local_44);
        ppcVar9 = &local_4c;
        pcVar2 = &local_31;
        pcVar3 = &local_32;
        ppcVar8 = &local_40;
        FID_conflict_begin(local_70);
        iVar4 = FUN_00421ec0();
        iVar5 = FUN_004170c0();
        pcVar7 = (char *)(iVar4 + iVar5);
        FID_conflict_begin(local_60);
        pcVar6 = (char *)FUN_00421ec0();
        local_3c = std::codecvt<char,char,int>::in
                             (*(codecvt<char,char,int> **)(local_30 + 0x40),(int *)(local_30 + 0x48)
                              ,pcVar6,pcVar7,ppcVar8,pcVar3,pcVar2,ppcVar9);
        if (local_3c < 0) {
LAB_004217bd:
          local_54 = eof(_FileHandle);
          local_8 = 0xffffffff;
          ~basic_string<>();
          goto LAB_004217ed;
        }
        if (local_3c < 2) {
          if (local_4c != &local_32) {
            FID_conflict_begin(local_6c);
            iVar4 = FUN_00421ec0();
            iVar5 = FUN_004170c0();
            local_38 = (iVar4 + iVar5) - (int)local_40;
            while (0 < local_38) {
              local_38 = local_38 + -1;
              ungetc((int)local_40[local_38],*(FILE **)(local_30 + 0x50));
            }
            local_5c = FUN_00417ab0(&local_32);
            local_8 = 0xffffffff;
            ~basic_string<>();
            goto LAB_004217ed;
          }
          FID_conflict_begin(local_64);
          iVar4 = FUN_00421ec0();
          std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::erase
                    (local_2c,0,(int)local_40 - iVar4);
          goto LAB_00421601;
        }
        if (local_3c != 3) goto LAB_004217bd;
        iVar4 = FUN_004170c0();
      } while (iVar4 == 0);
      _MaxCount = 1;
      FID_conflict_begin(local_68);
      _Src = (void *)FUN_00421ec0();
      memcpy_s(&local_32,1,_Src,_MaxCount);
      local_50 = FUN_00417ab0(&local_32);
      local_8 = 0xffffffff;
      ~basic_string<>();
    }
  }
LAB_004217ed:
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

