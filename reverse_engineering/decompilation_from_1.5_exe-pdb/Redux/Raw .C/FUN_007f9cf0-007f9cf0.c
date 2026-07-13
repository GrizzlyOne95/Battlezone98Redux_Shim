
void __thiscall
FUN_007f9cf0(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5
            )

{
  byte *pbVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  uint uVar5;
  undefined1 local_28 [12];
  undefined1 local_1c [8];
  undefined1 local_14 [8];
  int local_c;
  undefined1 local_7;
  undefined1 local_6;
  undefined1 local_5;
  
  local_5 = 0;
  local_6 = 0;
  uVar4 = param_3;
  local_c = param_1;
  pbVar1 = (byte *)FUN_007f55f0(&local_7,0,*(undefined1 *)(param_1 + 4));
  uVar5 = (uint)*pbVar1;
  iVar2 = local_c + 3;
  uVar3 = FUN_007f9dd0(local_14,&DAT_0260c032,param_3);
  uVar4 = FUN_007f9e20(local_28,uVar3,iVar2,uVar5,param_2,uVar4,param_4,param_5);
  uVar4 = FUN_007f9e40(local_1c,uVar4);
  _Debug_range_ptr<>(uVar4);
  return;
}

