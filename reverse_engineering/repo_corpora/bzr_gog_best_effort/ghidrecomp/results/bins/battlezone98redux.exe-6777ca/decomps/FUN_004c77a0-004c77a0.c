
void __thiscall FUN_004c77a0(undefined4 param_1,int param_2,int param_3)

{
  ushort *puVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint local_38;
  uint local_34;
  uint local_2c;
  uint local_28;
  uint local_24;
  uint local_20;
  uint local_1c;
  
  puVar1 = (ushort *)FUN_004c0fe0(param_2,param_3,param_1);
  local_28 = (int)(*puVar1 & 0xf000) >> 0xc;
  puVar1 = (ushort *)FUN_004c0fe0(param_2,param_3 + -2);
  uVar4 = (int)(*puVar1 & 0xf000) >> 0xc;
  puVar1 = (ushort *)FUN_004c0fe0(param_2 + 2,param_3);
  uVar3 = (int)(*puVar1 & 0xf000) >> 0xc;
  puVar1 = (ushort *)FUN_004c0fe0(param_2,param_3 + 2);
  uVar5 = (int)(*puVar1 & 0xf000) >> 0xc;
  puVar1 = (ushort *)FUN_004c0fe0(param_2 + -2,param_3);
  uVar2 = (int)(*puVar1 & 0xf000) >> 0xc;
  local_20 = local_28;
  if (uVar4 < local_28) {
    local_20 = uVar4;
  }
  local_24 = local_28;
  if (local_28 < uVar4) {
    local_24 = uVar4;
  }
  if (uVar3 < local_20) {
    local_20 = uVar3;
  }
  if (local_24 < uVar3) {
    local_24 = uVar3;
  }
  if (uVar5 < local_20) {
    local_20 = uVar5;
  }
  if (local_24 < uVar5) {
    local_24 = uVar5;
  }
  if (uVar2 < local_20) {
    local_20 = uVar2;
  }
  if (local_24 < uVar2) {
    local_24 = uVar2;
  }
  if (local_28 == local_20) {
    local_38 = local_24;
  }
  else {
    local_38 = local_20;
  }
  local_1c = (uint)(local_28 != uVar4);
  if (local_28 != uVar3) {
    local_1c = local_1c | 2;
  }
  if (local_28 != uVar5) {
    local_1c = local_1c | 4;
  }
  if (local_28 != uVar2) {
    local_1c = local_1c | 8;
  }
  if ((((((((local_1c == 5) || (local_1c == 7)) || (local_1c == 10)) ||
         ((local_1c == 0xb || (local_1c == 0xd)))) || ((local_1c == 0xe || (local_1c == 0xf)))) ||
       ((local_28 != local_20 && (local_28 != local_24)))) ||
      ((uVar4 != local_20 && (uVar4 != local_24)))) ||
     ((((uVar3 != local_20 && (uVar3 != local_24)) || ((uVar5 != local_20 && (uVar5 != local_24))))
      || ((uVar2 != local_20 && (uVar2 != local_24)))))) {
    if (local_28 == local_20) {
      local_28 = local_24;
    }
    else {
      local_28 = local_20;
    }
    local_20 = local_28;
    local_24 = local_28;
    local_1c = 0;
  }
  local_1c = *(uint *)(&DAT_008fe680 + local_1c * 4) | *(uint *)(&DAT_008fe640 + local_1c * 4);
  uVar2 = rand();
  if (local_20 == local_24) {
    local_1c = (int)uVar2 >> 0xd;
  }
  if ((uVar2 & 0x10) == 0) {
    local_34 = 0;
  }
  else {
    local_34 = 4;
  }
  uVar2 = uVar2 & 0xf;
  if (uVar2 < 8) {
    if (uVar2 < 4) {
      if (uVar2 < 2) {
        local_2c = 3;
      }
      else {
        local_2c = 2;
      }
    }
    else {
      local_2c = 1;
    }
  }
  else {
    local_2c = 0;
  }
  FUN_0083e885(param_1,local_34,
               local_28 << 0xc | local_38 << 8 | (local_1c & 0xf | local_34) << 4 | local_2c);
  return;
}

