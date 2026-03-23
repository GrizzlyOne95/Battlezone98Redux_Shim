
void FUN_00626070(float param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  float *pfVar4;
  float local_8;
  
  uVar1 = FUN_005771b0(DAT_009180d4);
  uVar2 = FUN_00575510(0x12);
  iVar3 = FUN_004bb390(uVar1,uVar2);
  if (iVar3 == 4) {
    pfVar4 = (float *)get();
    local_8 = *pfVar4 + param_1;
  }
  else {
    local_8 = param_1;
  }
  FUN_00575570(0x12,&local_8,4);
  return;
}

