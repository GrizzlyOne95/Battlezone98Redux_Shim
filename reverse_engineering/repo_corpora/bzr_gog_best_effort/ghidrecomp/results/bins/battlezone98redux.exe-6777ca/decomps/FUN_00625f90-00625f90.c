
void FUN_00625f90(void)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  int *piVar4;
  int local_8;
  
  uVar1 = FUN_005771b0(DAT_009180d4);
  uVar2 = FUN_00575510(0xf);
  iVar3 = FUN_004bb390(uVar1,uVar2);
  if (iVar3 == 4) {
    piVar4 = (int *)get();
    local_8 = *piVar4 + 1;
  }
  else {
    local_8 = 1;
  }
  FUN_00575570(0xf,&local_8,4);
  return;
}

