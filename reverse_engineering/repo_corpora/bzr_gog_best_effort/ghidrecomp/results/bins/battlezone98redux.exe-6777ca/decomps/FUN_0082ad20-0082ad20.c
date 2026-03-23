
undefined4
FUN_0082ad20(int param_1,int param_2,int param_3,int param_4,int param_5,int param_6,int param_7,
            int param_8,int param_9,int param_10)

{
  int *piVar1;
  undefined4 uVar2;
  uint extraout_ECX;
  uint uVar3;
  uint uVar4;
  int iVar5;
  bool bVar6;
  bool bVar7;
  int local_24;
  uint local_20;
  int local_1c;
  uint local_18;
  undefined4 local_14;
  undefined4 local_10;
  uint local_4;
  
  if ((((((param_1 == 0) || ((param_2 != -1 && (param_2 != 2)))) ||
        ((param_3 != -1 && (param_3 != 4)))) ||
       ((((param_4 != -1 && (param_4 != 4)) || ((param_5 != -1 && (param_5 != 4)))) ||
        ((param_6 != -1 && (param_6 != 4)))))) || ((param_7 != -1 && (param_7 != 4)))) ||
     ((((param_8 != -1 && (param_8 != 4)) || ((param_9 != -1 && (param_9 != 4)))) ||
      ((param_10 != -1 && (param_10 != 0x18)))))) {
    return 0xffffffff;
  }
  local_4 = DAT_008e7000 ^ (uint)&local_24;
  local_10 = 0;
  local_14 = 0;
  FUN_0082afa0(&local_14,0);
  local_10 = 0;
  local_14 = 0x2000001;
  piVar1 = (int *)FUN_0082afa0(&local_14,1);
  local_14 = 0x82818003;
  local_10 = 0x483;
  uVar3 = extraout_ECX & (short)*piVar1 == 0 & (uint)((short)*piVar1 == 0) &
          (uint)((short)*piVar1 == 0x80) & (uint)((short)*piVar1 == -0x7e80) &
          (uint)((short)*piVar1 == -0x7e80) & (uint)(*piVar1 == 0) & (uint)(*piVar1 == 0) &
          (uint)(*piVar1 == 0x80) & (uint)(*piVar1 == -0x7c7d7e80) & (uint)(*piVar1 == -0x7c7d7e80);
  iVar5 = 0;
  uVar4 = 1;
  do {
    if (uVar3 != 1) break;
    local_18 = 0x1f;
    if (uVar4 != 0) {
      for (; uVar4 >> local_18 == 0; local_18 = local_18 - 1) {
      }
    }
    uVar3 = 0x1f - iVar5;
    local_20 = 0x1f;
    if (uVar4 != 0) {
      for (; uVar4 >> local_20 == 0; local_20 = local_20 - 1) {
      }
    }
    iVar5 = iVar5 + 1;
    uVar3 = (uint)((local_20 ^ 0x1f) == uVar3 && (local_18 ^ 0x1f) == uVar3);
    uVar4 = uVar4 * 2;
  } while (uVar4 != 0);
  iVar5 = 0;
  uVar4 = 1;
  do {
    if (uVar3 != 1) break;
    local_1c = 0;
    if (uVar4 != 0) {
      for (; (uVar4 >> local_1c & 1) == 0; local_1c = local_1c + 1) {
      }
    }
    local_24 = 0;
    if (uVar4 != 0) {
      for (; (uVar4 >> local_24 & 1) == 0; local_24 = local_24 + 1) {
      }
    }
    bVar6 = local_24 == iVar5;
    bVar7 = local_1c == iVar5;
    iVar5 = iVar5 + 1;
    uVar3 = (uint)(bVar6 && bVar7);
    uVar4 = uVar4 * 2;
  } while (uVar4 != 0);
  uVar2 = FUN_0083e885();
  return uVar2;
}

