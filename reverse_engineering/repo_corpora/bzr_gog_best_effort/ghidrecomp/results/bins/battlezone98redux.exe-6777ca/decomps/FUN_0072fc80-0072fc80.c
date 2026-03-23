
void __fastcall FUN_0072fc80(int param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  
  uVar1 = FUN_00417780(param_1 + 8);
  uVar2 = FUN_0072f970(param_1,param_1 + 8,&stack0x00000004,uVar1);
  uVar1 = FUN_004242e0(param_1 + 8,uVar2);
  puVar3 = (undefined4 *)FUN_0070d600(param_1,param_1 + 8,&stack0x00000004,uVar1);
  uVar1 = *puVar3;
  uVar4 = FUN_004242f0(param_1 + 8,uVar1);
  uVar4 = FUN_0070d600(param_1,param_1 + 8,&stack0x00000004,uVar4);
  FUN_00732050(uVar4,uVar1,uVar2);
  return;
}

