
void __fastcall FUN_005b0dc0(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 *puVar3;
  
  uVar1 = (**(code **)(*(int *)(param_1 + 0x18) + 4))(0);
  iVar2 = (**(code **)(*(int *)(param_1 + 0x18) + 0xc))
                    (*(undefined4 *)(*(int *)(param_1 + 0xf8) + 0x168),uVar1);
  puVar3 = (undefined4 *)(**(code **)(*(int *)(param_1 + 0x18) + 0xc))(*(undefined4 *)(iVar2 + 8));
  FUN_00469900(*puVar3);
  FUN_0047eb00();
  return;
}

