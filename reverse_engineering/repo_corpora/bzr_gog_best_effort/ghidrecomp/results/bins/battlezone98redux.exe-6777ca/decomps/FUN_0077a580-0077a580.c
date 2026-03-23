
void __thiscall
FUN_0077a580(int param_1,int param_2,int param_3,int param_4,int param_5,int param_6,int param_7,
            int param_8,int param_9)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 local_10;
  undefined4 local_c;
  
  iVar2 = *(int *)(param_1 + 0x240) * 0x100 + DAT_02ce99c0;
  iVar3 = *(int *)(param_1 + 0x244) * 0x100 + DAT_02cd9984;
  for (local_c = param_8; local_c < param_9; local_c = local_c + 1) {
    for (local_10 = param_6; local_10 < param_7; local_10 = local_10 + 1) {
      iVar1 = FUN_0077d640(iVar2 + -0x80 + (param_2 * 0x10 + param_4) * 4 + local_10,
                           iVar3 + -0x80 + (param_3 * 0x10 + param_5) * 4 + local_c);
      **(float **)(param_1 + 0x3ac) = (float)iVar1 * 0.1;
      *(int *)(param_1 + 0x3ac) = *(int *)(param_1 + 0x3ac) + 4;
    }
  }
  return;
}

