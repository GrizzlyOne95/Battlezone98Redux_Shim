
void FUN_004fe280(int param_1,char *param_2,size_t param_3)

{
  undefined4 uVar1;
  char *_Filename;
  size_t sVar2;
  char *_Mode;
  undefined1 local_10c [4];
  undefined1 *local_108;
  undefined1 local_104 [4];
  char *local_100;
  undefined1 local_fc [4];
  undefined4 local_f8;
  FILE *local_f4;
  undefined4 local_f0;
  FILE *local_ec;
  FILE *local_e8;
  undefined4 local_e4;
  void *local_e0;
  undefined4 local_dc;
  FILE *local_d8;
  void *local_d4;
  char *local_d0;
  char *local_cc;
  char *local_c8;
  size_t local_c4;
  char *local_c0;
  undefined1 local_ba;
  undefined1 local_b9;
  uint local_b8;
  char local_b2;
  char local_b1;
  FILE *local_b0;
  undefined1 local_ac [24];
  undefined1 local_94 [48];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_64 [24];
  undefined1 local_4c [52];
  char local_18 [16];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_b0 = (FILE *)0x0;
  if ((0 < param_1) && (param_1 < 0xb)) {
    FUN_00426a60(&DAT_02ceefe0,0);
    basic_string<>(&DAT_0087bb64);
    uVar1 = FUN_00482630(local_ac,param_1);
    FUN_00449810(uVar1);
    ~basic_string<>();
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
              (local_64,".sav");
    FUN_004fed70(local_64);
    FUN_00417fd0(local_94);
    _Mode = "rb";
    _Filename = (char *)FUN_0041f870();
    local_b0 = fopen(_Filename,_Mode);
    if (local_b0 == (FILE *)0x0) {
      local_f0 = 0;
      ~basic_string<>();
      ~basic_string<>();
      FUN_004180b0();
    }
    else {
      local_b9 = DAT_009173b6;
      local_ba = DAT_009173b7;
      local_d0 = &DAT_00915540;
      local_100 = local_18;
      local_c8 = local_100;
      do {
        local_b1 = *local_d0;
        *local_c8 = local_b1;
        local_d0 = local_d0 + 1;
        local_c8 = local_c8 + 1;
      } while (local_b1 != '\0');
      DAT_009173b6 = 0;
      DAT_009173b7 = 0;
      fseek(local_b0,0,2);
      local_c4 = ftell(local_b0);
      if (local_c4 == 0) {
        fclose(local_b0);
        local_dc = 0;
        ~basic_string<>();
        ~basic_string<>();
        FUN_004180b0();
      }
      else {
        fseek(local_b0,0,0);
        local_e0 = (void *)FUN_0083d92c(local_c4);
        local_d4 = local_e0;
        sVar2 = fread(local_e0,1,local_c4,local_b0);
        fclose(local_b0);
        local_b0 = local_d4;
        local_b0 = (FILE *)FUN_004cdd10(local_d4,local_c4,sVar2);
        local_b8 = FUN_004ce910(local_b0,&DAT_00917b20,4);
        local_b8 = local_b8 & 0xff;
        if (DAT_00917b20 < 0x40a) {
          _snprintf(param_2,param_3,"Old version save game");
          local_e8 = (FILE *)FUN_004cdd70(local_b0);
          local_d8 = local_e8;
          local_b0 = local_e8;
          operator_delete__(local_e8);
          local_f8 = 0;
          ~basic_string<>();
          ~basic_string<>();
          FUN_004180b0();
        }
        else {
          local_b8 = FUN_004ce5e0(local_b0,&DAT_009173b6,1);
          local_b8 = local_b8 & 0xff;
          local_b8 = FUN_004ce2f0(local_b0,&DAT_00915540,0x10);
          local_b8 = local_b8 & 0xff;
          local_b8 = FUN_004ce910(local_b0,local_104,4);
          local_b8 = local_b8 & 0xff;
          local_b8 = FUN_004ce5e0(local_b0,&DAT_009173b7,1);
          local_b8 = local_b8 & 0xff;
          local_b8 = FUN_004ce910(local_b0,local_10c,4);
          local_b8 = local_b8 & 0xff;
          local_b8 = FUN_004ce400(local_b0,&DAT_008e86d8,0x100);
          local_b8 = local_b8 & 0xff;
          if (DAT_00917b20 < 0x7df) {
            local_b8 = FUN_004ce910(local_b0,local_fc,4);
          }
          else {
            local_b8 = FUN_004ce2f0(local_b0,local_4c,0x32);
          }
          local_b8 = local_b8 & 0xff;
          local_b8 = FUN_004ce910(local_b0,&DAT_0091830c,4);
          local_b8 = local_b8 & 0xff;
          strncpy(param_2,&DAT_008e86d8,param_3);
          param_2[param_3 - 1] = '\0';
          DAT_009173b6 = local_b9;
          DAT_009173b7 = local_ba;
          local_cc = local_18;
          local_c0 = &DAT_00915540;
          local_108 = &DAT_00915540;
          do {
            local_b2 = *local_cc;
            *local_c0 = local_b2;
            local_cc = local_cc + 1;
            local_c0 = local_c0 + 1;
          } while (local_b2 != '\0');
          local_f4 = (FILE *)FUN_004cdd70(local_b0);
          local_ec = local_f4;
          local_b0 = local_f4;
          operator_delete__(local_f4);
          local_e4 = 1;
          ~basic_string<>();
          ~basic_string<>();
          FUN_004180b0();
        }
      }
    }
  }
  FUN_0083e885();
  return;
}

