
void FUN_0083c26e(int param_1,int *param_2,int param_3)

{
  undefined4 uVar1;
  int *piVar2;
  int iVar3;
  undefined4 local_c;
  undefined4 local_8;
  
  piVar2 = param_2;
  FUN_0083c185(param_1,param_2,param_3);
  if (*param_2 == 10) {
    FUN_0083c626(param_1,param_2 + 4,param_2[2]);
  }
  if (param_2[4] == param_2[5]) goto LAB_0083c34a;
  local_8 = 0xffffffff;
  local_c = 0xffffffff;
  iVar3 = FUN_0083cfa8(param_1,param_2[4]);
  if (iVar3 == 0) {
    iVar3 = FUN_0083cfa8(param_1,param_2[5]);
    if (iVar3 != 0) goto LAB_0083c2d1;
  }
  else {
LAB_0083c2d1:
    if (*param_2 == 10) {
      param_2 = (int *)0xffffffff;
    }
    else {
      param_2 = (int *)FUN_0083c9bd(param_1);
    }
    *(undefined4 *)(param_1 + 0x1c) = *(undefined4 *)(param_1 + 0x18);
    local_8 = FUN_0083c5d2(param_1,2,param_3,0,1);
    *(undefined4 *)(param_1 + 0x1c) = *(undefined4 *)(param_1 + 0x18);
    local_c = FUN_0083c5d2(param_1,2,param_3,1,0);
    FUN_0083cadc(param_1,param_2);
  }
  uVar1 = *(undefined4 *)(param_1 + 0x18);
  *(undefined4 *)(param_1 + 0x1c) = uVar1;
  FUN_0083cfe1(param_1,piVar2[5],uVar1,param_3,local_8);
  FUN_0083cfe1(param_1,piVar2[4],uVar1,param_3,local_c);
LAB_0083c34a:
  piVar2[4] = -1;
  piVar2[5] = -1;
  piVar2[2] = param_3;
  *piVar2 = 0xc;
  return;
}

