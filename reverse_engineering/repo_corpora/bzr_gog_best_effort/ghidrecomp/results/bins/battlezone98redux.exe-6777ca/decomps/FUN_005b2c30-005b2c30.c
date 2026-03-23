
void __thiscall FUN_005b2c30(double *param_1,undefined4 param_2,double param_3,double param_4)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  double dVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  
  dVar3 = param_1[2];
  iVar4 = *(int *)((int)param_1 + 0x24) + -1;
  uVar6 = 0;
  floor((param_3 - param_1[3]) * *param_1);
  FUN_0083f040(uVar6,iVar4);
  iVar4 = FUN_00453d10();
  iVar5 = *(int *)(param_1 + 5) + -1;
  uVar6 = 0;
  floor((param_4 - dVar3) * param_1[1]);
  FUN_0083f040(uVar6,iVar5);
  iVar5 = FUN_00453d10();
  puVar1 = (undefined4 *)
           (*(int *)((int)param_1 + 0x34) + (iVar5 * *(int *)((int)param_1 + 0x24) + iVar4) * 4);
  puVar2 = (undefined4 *)(*(int *)(param_1 + 6) + *(int *)((int)param_1 + 0x2c) * 8);
  *puVar2 = param_2;
  puVar2[1] = *puVar1;
  *puVar1 = *(undefined4 *)((int)param_1 + 0x2c);
  *(int *)((int)param_1 + 0x2c) = *(int *)((int)param_1 + 0x2c) + 1;
  return;
}

