
void FUN_006402a0(float param_1,undefined4 param_2,char *param_3,int *param_4)

{
  int iVar1;
  undefined4 uVar2;
  float10 fVar3;
  int *local_8;
  
  if (((*param_3 == '\0') && (iVar1 = FUN_005cd9d0(param_2,0,1), iVar1 != 0)) &&
     (fVar3 = (float10)FUN_005c9800(iVar1,param_2,0), (float)fVar3 < param_1)) {
    *param_3 = '\x01';
    for (local_8 = param_4; *local_8 != 0; local_8 = local_8 + 1) {
      uVar2 = FUN_005c8250(*local_8,2,param_2,0,0);
      FUN_005cdb20(uVar2,1);
    }
  }
  return;
}

