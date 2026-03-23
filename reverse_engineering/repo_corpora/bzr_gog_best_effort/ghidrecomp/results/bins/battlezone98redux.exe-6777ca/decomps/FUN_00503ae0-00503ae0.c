
undefined4 FUN_00503ae0(undefined4 param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  float10 fVar4;
  float fVar5;
  
  uVar1 = FUN_0082ba59(param_1,1,0);
  FUN_0082c225(param_1,2,"WHITE",0,uVar1);
  uVar2 = FUN_00503930();
  fVar4 = (float10)FUN_0082c276(param_1,3,0x4020000000000000,uVar1,uVar2);
  fVar5 = (float)fVar4;
  uVar3 = FUN_0082c225(param_1,4,0,0,uVar1,uVar2,fVar5);
  FUN_004ff0d0(uVar1,uVar2,fVar5,uVar3);
  return 0;
}

