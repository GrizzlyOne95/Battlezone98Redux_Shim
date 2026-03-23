
void __thiscall
FUN_007f5750(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5
            )

{
  byte *pbVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  uint uVar4;
  undefined1 local_a [2];
  undefined1 local_8;
  undefined1 local_7;
  undefined1 local_6;
  undefined1 local_5;
  
  local_5 = 0;
  local_6 = 0;
  uVar3 = param_3;
  pbVar1 = (byte *)FUN_007f55f0(&local_7,0,*(undefined1 *)(param_1 + 2));
  uVar4 = (uint)*pbVar1;
  uVar2 = FUN_007f6070(local_a,&DAT_0260c032,param_3);
  uVar3 = FUN_007f5620(&local_8,uVar2,uVar4,param_2,uVar3,param_4,param_5);
  _Debug_range_ptr<>(uVar3);
  return;
}

