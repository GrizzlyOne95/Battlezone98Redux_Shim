
void FUN_006852f0(void)

{
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  DAT_02b79b34 = 0;
  if (DAT_02b3f014 == 0) {
    local_8 = 0;
  }
  else {
    local_8 = DAT_02b3f014 + 0xd4;
  }
  (**(code **)(**(int **)(DAT_00920ea0 + 0x10) + 0x210))(local_8);
  FUN_00685260(DAT_02b3f014);
  DAT_02b3f014 = 0;
  if (DAT_02b79b30 == 0) {
    local_c = 0;
  }
  else {
    local_c = DAT_02b79b30 + 0xd4;
  }
  (**(code **)(**(int **)(DAT_00920ea0 + 0x14) + 0x210))(local_c);
  FUN_00685260(DAT_02b79b30);
  DAT_02b79b30 = 0;
  if (DAT_02b79b28 == 0) {
    local_10 = 0;
  }
  else {
    local_10 = DAT_02b79b28 + 0xd4;
  }
  (**(code **)(**(int **)(DAT_00920ea0 + 0x18) + 0x210))(local_10);
  FUN_00685260(DAT_02b79b28);
  DAT_02b79b28 = 0;
  return;
}

