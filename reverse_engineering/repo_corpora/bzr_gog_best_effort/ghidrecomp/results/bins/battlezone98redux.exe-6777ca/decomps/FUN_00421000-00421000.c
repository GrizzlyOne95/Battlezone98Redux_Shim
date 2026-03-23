
void FUN_00421000(int param_1)

{
  char cVar1;
  undefined1 uVar2;
  uint _FileHandle;
  char *pcVar3;
  char *pcVar4;
  int iVar5;
  int iVar6;
  void *_Str;
  uint uVar7;
  size_t sVar8;
  size_t _Size;
  char **ppcVar9;
  FILE *_File;
  undefined1 local_78 [4];
  undefined1 local_74 [4];
  undefined1 local_70 [4];
  undefined1 local_6c [4];
  undefined4 local_68;
  int local_64;
  char *local_60;
  int local_5c;
  int local_58;
  int local_54;
  int local_50;
  int local_4c;
  char *local_48;
  int local_44;
  int local_40;
  int local_3c;
  size_t local_38;
  char local_32;
  char local_31;
  basic_streambuf<char,struct_std::char_traits<char>_> *local_30;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00845218;
  local_10 = ExceptionList;
  _FileHandle = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = _FileHandle;
  local_64 = eof(_FileHandle);
  cVar1 = eq_int_type(&local_64,&param_1);
  if (cVar1 == '\0') {
    pcVar3 = std::basic_streambuf<char,struct_std::char_traits<char>_>::pptr(local_30);
    if (pcVar3 != (char *)0x0) {
      pcVar3 = std::basic_streambuf<char,struct_std::char_traits<char>_>::pptr(local_30);
      pcVar4 = std::basic_streambuf<char,struct_std::char_traits<char>_>::epptr(local_30);
      if (pcVar3 < pcVar4) {
        cVar1 = FUN_00417aa0(&param_1);
        pcVar3 = std::basic_streambuf<char,struct_std::char_traits<char>_>::_Pninc(local_30);
        *pcVar3 = cVar1;
        goto LAB_004212fd;
      }
    }
    if (*(int *)(local_30 + 0x50) == 0) {
      eof(_FileHandle);
    }
    else {
      FUN_00423580();
      if (*(int *)(local_30 + 0x40) == 0) {
        uVar2 = FUN_00417aa0(&param_1,*(undefined4 *)(local_30 + 0x50));
        cVar1 = FUN_00417e90(uVar2);
        if (cVar1 == '\0') {
          local_44 = eof(_FileHandle);
        }
        else {
          local_44 = param_1;
        }
      }
      else {
        local_68 = 8;
        local_32 = FUN_00417aa0(&param_1);
        std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
        basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                  (local_2c,8,'\0');
        local_8 = 0;
        while( true ) {
          ppcVar9 = &local_60;
          FID_conflict_begin(local_78);
          iVar5 = FUN_00421ec0();
          iVar6 = FUN_004170c0();
          pcVar4 = (char *)(iVar5 + iVar6);
          FID_conflict_begin(local_74);
          pcVar3 = (char *)FUN_00421ec0();
          local_3c = std::codecvt<char,char,int>::out
                               (*(codecvt<char,char,int> **)(local_30 + 0x40),
                                (int *)(local_30 + 0x48),&local_32,&local_31,&local_48,pcVar3,pcVar4
                                ,ppcVar9);
          if (local_3c < 0) break;
          if (1 < local_3c) {
            if (local_3c == 3) {
              cVar1 = FUN_00417e90(local_32,*(undefined4 *)(local_30 + 0x50));
              if (cVar1 == '\0') {
                local_40 = eof(_FileHandle);
              }
              else {
                local_40 = param_1;
              }
              local_54 = local_40;
              local_8 = 0xffffffff;
              ~basic_string<>();
              goto LAB_004212fd;
            }
            break;
          }
          FID_conflict_begin(local_6c);
          iVar5 = FUN_00421ec0();
          sVar8 = (int)local_60 - iVar5;
          local_38 = sVar8;
          if (sVar8 != 0) {
            _File = *(FILE **)(local_30 + 0x50);
            _Size = 1;
            FID_conflict_begin(local_70);
            _Str = (void *)FUN_00421ec0();
            sVar8 = fwrite(_Str,_Size,sVar8,_File);
            if (local_38 != sVar8) {
              local_5c = eof(_FileHandle);
              local_8 = 0xffffffff;
              ~basic_string<>();
              goto LAB_004212fd;
            }
          }
          local_30[0x45] = (basic_streambuf<char,struct_std::char_traits<char>_>)0x1;
          if (local_48 != &local_32) {
            local_58 = param_1;
            local_8 = 0xffffffff;
            ~basic_string<>();
            goto LAB_004212fd;
          }
          if (local_38 == 0) {
            uVar7 = FUN_004170c0();
            if (0x1f < uVar7) {
              local_50 = eof(_FileHandle);
              local_8 = 0xffffffff;
              ~basic_string<>();
              goto LAB_004212fd;
            }
            std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
            append(local_2c,8,'\0');
          }
        }
        local_4c = eof(_FileHandle);
        local_8 = 0xffffffff;
        ~basic_string<>();
      }
    }
  }
  else {
    not_eof(&param_1);
  }
LAB_004212fd:
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

