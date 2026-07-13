
void __thiscall FUN_004666c0(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  
  puVar1 = (undefined4 *)(**(code **)(*(int *)(param_2 + 0x18) + 0xc))(param_1);
  uVar2 = (**(code **)(*(int *)(param_2 + 0x18) + 4))();
  FUN_00466450(*puVar1,puVar1[2],param_3,param_4,*(undefined4 *)(param_2 + 0x234),uVar2);
  return;
}

