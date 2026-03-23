
void FUN_00595080(int param_1,int param_2,int param_3,undefined4 param_4,ulong param_5,
                 undefined4 param_6)

{
  float fVar1;
  int iVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  float fVar6;
  float local_c;
  float local_8;
  
  FUN_00689ab0(DAT_00917550,param_4,&local_c,&local_8);
  fVar1 = DAT_00920ef4;
  if (param_3 == 0) {
    DAT_00920ef4 = DAT_00920ef4 + 0.01;
    FUN_0068afb0(DAT_00917580,param_1,param_2,(int)((float)param_1 + local_c),
                 (int)((float)param_2 + local_8),param_6,0);
    DAT_00920ef4 = fVar1;
  }
  else {
    uVar3 = FUN_00689eb0();
    iVar2 = FUN_0068f090(param_3);
    fVar6 = (float)uVar3;
    DAT_00920ef4 = DAT_00920ef4 + 0.01;
    uVar4 = FUN_00689eb0();
    FUN_0068afb0(DAT_00917580,(param_1 - (int)((float)uVar4 * 5.0)) - (int)((float)iVar2 * fVar6),
                 param_2,(int)((float)param_1 + local_c),(int)((float)param_2 + local_8),param_6,0);
    DAT_00920ef4 = fVar1;
    uVar5 = FUN_00689eb0();
    FUN_0068c560(DAT_00917580,param_3,param_1 - (int)((float)uVar5 * 5.0),param_2,0x20001,0,uVar5,
                 uVar4,uVar3);
  }
  std::_Init_atomic_counter(DAT_00917550,param_5);
  FUN_00689d10(DAT_00917550,DAT_00917580,param_1,param_2,param_4);
  return;
}

