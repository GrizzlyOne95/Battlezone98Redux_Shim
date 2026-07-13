
uint FUN_008144d0(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  uint uVar3;
  undefined1 local_30 [20];
  undefined4 *local_1c [5];
  undefined4 local_8;
  
  FUN_007ff1f0(param_5);
  local_8 = *param_1;
  FUN_007e9db0(&local_8,param_2,param_3,param_4);
  puVar2 = (undefined4 *)FUN_0080bfe0(local_30,local_1c,param_5);
  uVar3 = FUN_00814ac0(*puVar2,puVar2[1],puVar2[2],puVar2[3],puVar2[4]);
  if ((uVar3 & 0xff) == 0) {
    uVar3 = uVar3 & 0xffffff00;
  }
  else {
    uVar1 = *local_1c[0];
    *param_1 = uVar1;
    uVar3 = CONCAT31((int3)((uint)uVar1 >> 8),1);
  }
  return uVar3;
}

