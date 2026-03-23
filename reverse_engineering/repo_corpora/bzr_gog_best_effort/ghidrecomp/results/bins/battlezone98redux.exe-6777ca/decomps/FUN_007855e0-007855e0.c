
float10 FUN_007855e0(double param_1,double param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  float fVar5;
  float fVar6;
  double dVar7;
  double dVar8;
  undefined4 local_28;
  undefined4 local_20;
  
  dVar7 = (double)DAT_02cc50e4;
  dVar8 = (double)DAT_02cc50e4;
  iVar1 = FUN_0046eaf0(dVar7 * param_1);
  iVar2 = FUN_0046eaf0(dVar8 * param_2);
  fVar5 = (float)(dVar7 * param_1 - (double)iVar1);
  fVar6 = (float)(dVar8 * param_2 - (double)iVar2);
  iVar3 = FUN_00784100(iVar1,iVar2);
  iVar4 = FUN_00784100(iVar1 + 1,iVar2 + 1);
  if (fVar6 <= fVar5) {
    local_28 = FUN_00784100(iVar1 + 1,iVar2);
    local_20 = iVar3 - local_28;
    local_28 = local_28 - iVar4;
  }
  else {
    local_28 = FUN_00784100(iVar1,iVar2 + 1);
    local_20 = local_28 - iVar4;
    local_28 = iVar3 - local_28;
  }
  return (float10)(((float)iVar3 - ((float)local_20 * fVar5 + (float)local_28 * fVar6)) * 0.1);
}

