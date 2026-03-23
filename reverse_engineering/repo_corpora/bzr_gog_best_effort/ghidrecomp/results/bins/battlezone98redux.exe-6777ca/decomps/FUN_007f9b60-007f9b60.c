
void __thiscall
FUN_007f9b60(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5
            )

{
  byte *pbVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  uint uVar4;
  undefined1 local_14 [8];
  int local_c;
  undefined1 local_8;
  undefined1 local_7;
  undefined1 local_6;
  undefined1 local_5;
  
  local_5 = 0;
  local_6 = 0;
  uVar3 = param_3;
  local_c = param_1;
  pbVar1 = (byte *)FUN_007f55f0(&local_7,0,*(undefined1 *)(param_1 + 0x14));
  uVar4 = (uint)*pbVar1;
  uVar2 = FUN_007f9c70(local_14,&DAT_0260c032,param_3);
  uVar3 = FUN_007f9cc0(&local_8,uVar2,uVar4,param_2,uVar3,param_4,param_5);
  _Debug_range_ptr<>(uVar3);
  return;
}

