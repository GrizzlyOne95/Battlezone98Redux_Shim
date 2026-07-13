
void __thiscall FUN_00611aa0(undefined4 *param_1,int param_2,uint param_3,uint param_4)

{
  undefined4 *puVar1;
  uint uVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 *local_5c;
  int local_58;
  int local_54;
  undefined4 local_50;
  undefined4 *local_4c;
  char local_45;
  undefined4 *local_40;
  char local_3c [32];
  char local_1c [8];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084d268;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *param_1 = WeaponClass::vftable;
  param_1[2] = param_2;
  local_5c = param_1;
  local_40 = param_1;
  local_14 = uVar2;
  FUN_0041fe40(&local_5c);
  local_40[3] = *(undefined4 *)(param_2 + 0xc);
  local_40[4] = *(undefined4 *)(param_2 + 0x10);
  local_40[6] = param_3 & 0x7f7f7f7f;
  local_40[7] = param_4 & 0x7f7f7f7f;
  strncpy((char *)(local_40 + 8),(char *)(local_40 + 6),8);
  *(undefined1 *)(local_40 + 10) = 0;
  puVar1 = (undefined4 *)((int)local_40 + 0x1f);
  do {
    local_4c = puVar1;
    local_45 = *(char *)((int)local_4c + 1);
    puVar1 = (undefined4 *)((int)local_4c + 1);
  } while (local_45 != '\0');
  *puVar1 = 0x66646f2e;
  *(undefined1 *)((int)local_4c + 5) = 0;
  local_4c = puVar1;
  FUN_00589430(local_40 + 8);
  local_8 = 0;
  FUN_00589c20(0xacda90ab,0x10e6fd23,&local_58,0,0);
  if (local_58 == 0 && local_54 == 0) {
    local_40[0xc] = 0;
  }
  else {
    uVar3 = FUN_00586c60(local_58,local_54,uVar2);
    local_40[0xc] = uVar3;
  }
  if (local_40[0xc] == 0) {
    local_50 = 0;
  }
  else {
    local_50 = *(undefined4 *)(local_40[0xc] + 0x4c);
  }
  local_40[0xd] = local_50;
  FUN_0047b6c0(0xacda90ab,0xcfde2fc0,local_40 + 0x16,param_2 + 0x58);
  FUN_004cbc10(0xacda90ab,0xf429d8cf,local_40 + 0xe,param_2 + 0x38);
  FUN_004cbc10(0xacda90ab,0x1a05f72c,local_3c,0);
  if (local_3c[0] == '\0') {
    local_40[0x1a] = 0;
  }
  else {
    uVar3 = FUN_0068bed0(local_3c);
    local_40[0x1a] = uVar3;
  }
  FUN_004cbc10(0xacda90ab,0x48dae6d8,local_3c,0);
  if (local_3c[0] == '\0') {
    local_40[0x1b] = 0;
  }
  else {
    uVar3 = FUN_0068bed0(local_3c);
    local_40[0x1b] = uVar3;
  }
  FUN_00589760(0xacda90ab,0xd84e3a3c,local_40 + 0x1c,0);
  FUN_006122b0(0xacda90ab,0xf21ccf2c,local_1c,0);
  iVar4 = _strnicmp(local_1c,"CANN",4);
  if (iVar4 == 0) {
    local_40[0x1d] = 0x47;
  }
  else {
    iVar4 = _strnicmp(local_1c,"ROCK",4);
    if (iVar4 == 0) {
      local_40[0x1d] = 0x48;
    }
    else {
      iVar4 = _strnicmp(local_1c,"MORT",4);
      if (iVar4 == 0) {
        local_40[0x1d] = 0x49;
      }
      else {
        iVar4 = _strnicmp(local_1c,"SPEC",4);
        if (iVar4 == 0) {
          local_40[0x1d] = 0x4a;
        }
        else {
          local_40[0x1d] = 0x46;
        }
      }
    }
  }
  FUN_00589920(0xacda90ab,0xace3380d,local_40 + 0x1e,*(undefined1 *)(param_2 + 0x78));
  FUN_00589920(0xacda90ab,0x76576c99,(int)local_40 + 0x79,*(undefined1 *)(param_2 + 0x79));
  local_8 = 0xffffffff;
  FUN_00589530();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

