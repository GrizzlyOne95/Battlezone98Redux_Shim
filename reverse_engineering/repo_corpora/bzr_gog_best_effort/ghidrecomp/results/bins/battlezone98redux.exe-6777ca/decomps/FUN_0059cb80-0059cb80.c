
void __thiscall FUN_0059cb80(int param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  
  uVar6 = *(undefined4 *)(&DAT_008e8e74 + *(int *)(param_1 + 0x154) * 4);
  uVar7 = *(undefined4 *)(&DAT_008e8e54 + *(int *)(param_1 + 0x154) * 4);
  puVar3 = (undefined4 *)
           (**(code **)(*(int *)(*(int *)(param_1 + 0x150) + 0x18) + 0xc))(uVar6,uVar7,0);
  uVar5 = *puVar3;
  uVar1 = puVar3[1];
  uVar2 = puVar3[2];
  uVar4 = (**(code **)(*(int *)(*(int *)(param_1 + 0x150) + 0x18) + 4))
                    (*(undefined4 *)(param_1 + 0x14c));
  uVar5 = FUN_006a5b70(uVar5,uVar1,uVar2,uVar6,uVar7,param_2,param_3,uVar4);
  FUN_0083e885(uVar6,uVar7,uVar5);
  return;
}

