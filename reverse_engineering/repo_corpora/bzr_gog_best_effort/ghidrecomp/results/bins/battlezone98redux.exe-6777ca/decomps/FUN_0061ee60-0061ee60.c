
void FUN_0061ee60(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_150;
  char local_14c [4];
  int local_148;
  char local_144 [256];
  undefined1 local_44 [40];
  undefined1 local_1c [20];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  iVar1 = FUN_0061e470(local_144,0xff,param_1);
  if (iVar1 == 0) {
    FUN_007d6830("%s line %d: unexpected end of file.",DAT_0091a454,DAT_0091fef8);
  }
  else {
    iVar1 = sscanf(local_144," %1[+-] %s %s",local_14c,local_44,local_1c);
    if (iVar1 == 3) {
      uVar2 = FUN_0061e1c0(local_44,local_1c);
      iVar1 = FUN_0061e240(uVar2);
      if ((iVar1 != -1) && (local_148 = FUN_0061ea90(param_2,local_44,iVar1), -1 < local_148)) {
        if (local_14c[0] == '-') {
          local_150 = 0xffffffff;
        }
        else {
          local_150 = 1;
        }
        *(undefined4 *)(&DAT_00919914 + local_148 * 0x84) = local_150;
        FUN_0061ec80(param_1,&DAT_0091991c + local_148 * 0x84,&DAT_00919920 + local_148 * 0x84);
      }
    }
    else {
      FUN_007d6830("%s line %d: invalid analog entry.",DAT_0091a454,DAT_0091fef8);
    }
  }
  FUN_0083e885();
  return;
}

