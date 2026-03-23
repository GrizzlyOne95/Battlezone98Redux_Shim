
void __thiscall
FUN_005b2950(double *param_1,double param_2,double param_3,double param_4,double param_5,
            undefined1 *param_6)

{
  double dVar1;
  double dVar2;
  undefined4 uVar3;
  double dVar4;
  double dVar5;
  
  dVar5 = param_1[3];
  dVar4 = param_1[2];
  dVar1 = param_1[3];
  dVar2 = param_1[2];
  *param_6 = 0;
  *(undefined4 *)(param_6 + 0x1c) = *(undefined4 *)((int)param_1 + 0x24);
  *(undefined4 *)(param_6 + 0x20) = *(undefined4 *)(param_1 + 6);
  *(undefined4 *)(param_6 + 0x24) = *(undefined4 *)((int)param_1 + 0x34);
  dVar4 = floor(((param_3 - dVar4) - 20.0) * param_1[1]);
  uVar3 = FUN_0046eaf0(dVar4);
  *(undefined4 *)(param_6 + 0x10) = uVar3;
  if (*(int *)(param_6 + 0x10) < 0) {
    *(undefined4 *)(param_6 + 0x10) = 0;
  }
  if (*(int *)(param_1 + 5) <= *(int *)(param_6 + 0x10)) {
    *param_6 = 1;
  }
  dVar4 = floor(((param_5 - dVar2) + 20.0) * param_1[1]);
  uVar3 = FUN_0046eaf0(dVar4);
  *(undefined4 *)(param_6 + 0x14) = uVar3;
  if (*(int *)(param_1 + 5) <= *(int *)(param_6 + 0x14)) {
    *(int *)(param_6 + 0x14) = *(int *)(param_1 + 5) + -1;
  }
  if (*(int *)(param_6 + 0x14) < 0) {
    *param_6 = 1;
  }
  dVar5 = floor(((param_2 - dVar5) - 20.0) * *param_1);
  uVar3 = FUN_0046eaf0(dVar5);
  *(undefined4 *)(param_6 + 4) = uVar3;
  if (*(int *)(param_6 + 4) < 0) {
    *(undefined4 *)(param_6 + 4) = 0;
  }
  if (*(int *)((int)param_1 + 0x24) <= *(int *)(param_6 + 4)) {
    *param_6 = 1;
  }
  dVar5 = floor(((param_4 - dVar1) + 20.0) * *param_1);
  uVar3 = FUN_0046eaf0(dVar5);
  *(undefined4 *)(param_6 + 8) = uVar3;
  if (*(int *)((int)param_1 + 0x24) <= *(int *)(param_6 + 8)) {
    *(int *)(param_6 + 8) = *(int *)((int)param_1 + 0x24) + -1;
  }
  if (*(int *)(param_6 + 8) < 0) {
    *param_6 = 1;
  }
  FUN_005b26e0();
  return;
}

