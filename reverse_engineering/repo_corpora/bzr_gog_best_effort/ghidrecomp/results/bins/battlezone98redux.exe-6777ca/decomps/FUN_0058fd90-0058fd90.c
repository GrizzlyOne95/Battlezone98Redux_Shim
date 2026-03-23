
uint FUN_0058fd90(float param_1,float param_2,byte param_3)

{
  undefined1 uVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  uint local_10;
  uint local_c;
  
  FUN_00461fd0(param_1 * DAT_02cc50e4);
  iVar2 = FUN_0083f040();
  FUN_00461fd0(param_2 * DAT_02cc50e4);
  iVar3 = FUN_0083f040();
  uVar4 = iVar3 - 1;
  local_c = uVar4;
  do {
    if (iVar3 + 1 < (int)local_c) {
      return CONCAT31((int3)(uVar4 >> 8),1);
    }
    uVar4 = iVar2 - 1;
    for (local_10 = uVar4; (int)local_10 <= iVar2 + 1; local_10 = local_10 + 1) {
      uVar4 = FUN_0046adb0(local_10,local_c);
      if (((char)uVar4 == '\0') || (uVar4 = uVar4 & 0xff, uVar4 != param_3)) {
        return uVar4 & 0xffffff00;
      }
      uVar1 = FUN_0046acc0(local_10,local_c);
      iVar5 = FUN_00591670(uVar1);
      uVar4 = (uint)(byte)(&DAT_008e8e10)[iVar5];
      if (uVar4 == 0) {
        return 0;
      }
    }
    local_c = local_c + 1;
  } while( true );
}

