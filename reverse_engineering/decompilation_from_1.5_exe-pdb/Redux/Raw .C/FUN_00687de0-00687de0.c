
void FUN_00687de0(int param_1,int param_2,char *param_3,undefined4 param_4,int param_5,int param_6,
                 float param_7,undefined1 param_8)

{
  int iVar1;
  undefined8 uVar2;
  float local_44;
  int local_40;
  float local_3c;
  int local_38;
  int local_34;
  int local_30;
  char *local_2c;
  char local_25;
  int local_24;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_20 [24];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  uVar2 = FUN_00689eb0();
  FUN_00689ec0((float)uVar2 * param_7,(float)((ulonglong)uVar2 >> 0x20) * param_7);
  basic_string<>(&DAT_008a1ad8);
  local_2c = param_3;
  do {
    local_25 = *local_2c;
    local_2c = local_2c + 1;
  } while (local_25 != '\0');
  iVar1 = (int)local_2c - (int)(param_3 + 1);
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::assign
            (local_20,param_3);
  local_44 = 0.0;
  local_3c = 0.0;
  FUN_00689ab0(DAT_0091552c,param_3,&local_44,&local_3c,iVar1);
  local_38 = param_5;
  if (param_5 == 0) {
    local_34 = param_1;
  }
  else if (param_5 == 1) {
    local_34 = (int)((float)param_1 - local_44);
  }
  else if (param_5 == 2) {
    local_34 = (int)((float)param_1 - local_44 / 2.0);
  }
  local_40 = param_6;
  if (param_6 == 0) {
    local_30 = param_2;
  }
  else if (param_6 == 1) {
    local_30 = (int)((float)param_2 - local_3c / 2.0);
  }
  else if (param_6 == 2) {
    local_30 = (int)((float)param_2 - local_3c);
  }
  local_24 = FUN_00687ce0();
  if (local_24 < 0) {
    ~basic_string<>();
  }
  else {
    *(int *)(&DAT_02b79b38 + local_24 * 0x97c) = local_34;
    *(int *)(&DAT_02b79b3c + local_24 * 0x97c) = local_30;
    strncpy(&DAT_02b79b40 + local_24 * 0x97c,param_3,0x960);
    *(undefined4 *)(&DAT_02b7a4a0 + local_24 * 0x97c) = param_4;
    *(int *)(&DAT_02b7a4a4 + local_24 * 0x97c) = (int)param_7;
    *(undefined **)(&DAT_02b7a4ac + local_24 * 0x97c) = &DAT_02b79b38 + local_24 * 0x97c;
    *(float *)(&DAT_02b7a4a8 + local_24 * 0x97c) = param_7;
    (&DAT_02b7a4b0)[local_24 * 0x97c] = param_8;
    FUN_00689ec0(uVar2);
    ~basic_string<>();
  }
  FUN_0083e885();
  return;
}

