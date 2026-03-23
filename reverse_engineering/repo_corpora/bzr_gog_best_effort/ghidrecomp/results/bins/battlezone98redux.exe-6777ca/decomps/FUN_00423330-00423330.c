
void __fastcall FUN_00423330(int *param_1)

{
  char cVar1;
  uint _FileHandle;
  int iVar2;
  int iVar3;
  char *pcVar4;
  void *_Str;
  size_t sVar5;
  char *pcVar6;
  size_t _Size;
  char **ppcVar7;
  FILE *_File;
  undefined1 local_5c [4];
  undefined4 local_58;
  undefined1 local_54 [4];
  undefined1 local_50 [4];
  undefined1 local_4c [4];
  char *local_48;
  int local_44;
  undefined4 local_40;
  int local_3c;
  size_t local_38;
  undefined1 local_34;
  undefined1 local_33;
  undefined1 local_32;
  undefined1 local_31;
  int *local_30;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00845348;
  local_10 = ExceptionList;
  _FileHandle = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_30 = param_1;
  local_14 = _FileHandle;
  if ((param_1[0x10] != 0) && (*(char *)((int)param_1 + 0x45) != '\0')) {
    local_58 = 8;
    iVar2 = eof(_FileHandle);
    local_40 = (**(code **)(*local_30 + 0xc))(iVar2);
    local_44 = eof(_FileHandle);
    cVar1 = eq_int_type(&local_44,&local_40);
    if (cVar1 == '\0') {
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
      basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_2c,8,'\0');
      local_8 = 0;
      while( true ) {
        ppcVar7 = &local_48;
        FID_conflict_begin(local_5c);
        iVar2 = FUN_00421ec0();
        iVar3 = FUN_004170c0();
        pcVar6 = (char *)(iVar2 + iVar3);
        FID_conflict_begin(local_4c);
        pcVar4 = (char *)FUN_00421ec0();
        local_3c = std::codecvt<char,char,int>::unshift
                             ((codecvt<char,char,int> *)local_30[0x10],local_30 + 0x12,pcVar4,pcVar6
                              ,ppcVar7);
        if (local_3c == 0) {
          *(undefined1 *)((int)local_30 + 0x45) = 0;
        }
        else if (local_3c != 1) {
          if (local_3c == 3) {
            local_32 = 1;
            local_8 = 0xffffffff;
            ~basic_string<>();
          }
          else {
            local_31 = 0;
            local_8 = 0xffffffff;
            ~basic_string<>();
          }
          goto LAB_00423521;
        }
        FID_conflict_begin(local_50);
        iVar2 = FUN_00421ec0();
        sVar5 = (int)local_48 - iVar2;
        local_38 = sVar5;
        if (sVar5 != 0) {
          _File = (FILE *)local_30[0x14];
          _Size = 1;
          FID_conflict_begin(local_54);
          _Str = (void *)FUN_00421ec0();
          sVar5 = fwrite(_Str,_Size,sVar5,_File);
          if (local_38 != sVar5) {
            local_33 = 0;
            local_8 = 0xffffffff;
            ~basic_string<>();
            goto LAB_00423521;
          }
        }
        if (*(char *)((int)local_30 + 0x45) == '\0') break;
        if (local_38 == 0) {
          std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::append
                    (local_2c,8,'\0');
        }
      }
      local_34 = 1;
      local_8 = 0xffffffff;
      ~basic_string<>();
    }
  }
LAB_00423521:
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

