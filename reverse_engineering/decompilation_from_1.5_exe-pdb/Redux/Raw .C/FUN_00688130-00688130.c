
void FUN_00688130(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 char *param_5,float param_6,undefined4 param_7,undefined1 param_8)

{
  char cVar1;
  int iVar2;
  undefined8 uVar3;
  float local_30;
  char *local_2c;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_20 [24];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_30 = param_6;
  if (param_6 == 0.0) {
    local_30 = 1.0;
  }
  uVar3 = FUN_00689eb0();
  FUN_00689ec0((float)uVar3 * local_30,(float)((ulonglong)uVar3 >> 0x20) * local_30);
  basic_string<>(&DAT_008a1ad8);
  local_2c = param_5;
  do {
    cVar1 = *local_2c;
    local_2c = local_2c + 1;
  } while (cVar1 != '\0');
  iVar2 = (int)local_2c - (int)(param_5 + 1);
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::assign
            (local_20,param_5);
  iVar2 = FUN_00687ce0(iVar2);
  *(undefined4 *)(&DAT_02b79b38 + iVar2 * 0x97c) = param_1;
  *(undefined4 *)(&DAT_02b79b3c + iVar2 * 0x97c) = param_2;
  strncpy(&DAT_02b79b40 + iVar2 * 0x97c,param_5,0x960);
  *(undefined4 *)(&DAT_02b7a4a0 + iVar2 * 0x97c) = param_7;
  *(int *)(&DAT_02b7a4a4 + iVar2 * 0x97c) = (int)param_6;
  *(undefined **)(&DAT_02b7a4ac + iVar2 * 0x97c) = &DAT_02b79b38 + iVar2 * 0x97c;
  *(float *)(&DAT_02b7a4a8 + iVar2 * 0x97c) = local_30;
  FUN_00689ec0(uVar3);
  (&DAT_02b7a4b0)[iVar2 * 0x97c] = param_8;
  ~basic_string<>();
  FUN_0083e885();
  return;
}

