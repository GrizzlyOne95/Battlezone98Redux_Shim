
/* WARNING: Removing unreachable block (ram,0x00573b25) */

void FUN_00573ae0(undefined4 param_1,undefined4 *param_2)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  undefined4 uVar4;
  
  piVar1 = (int *)FUN_004b9ab0(*param_2);
  if (piVar1 != (int *)0x0) {
    piVar2 = (int *)FUN_00417c70();
    iVar3 = (**(code **)(piVar1[6] + 0x30))(piVar1 == piVar2);
    if ((*(uint *)(iVar3 + 0x14) & 4) == 0) {
      *(uint *)(iVar3 + 0x14) = *(uint *)(iVar3 + 0x14) | 4;
      (**(code **)(*piVar1 + 0x78))();
      FUN_004b9ba0(param_2[1]);
      uVar4 = (**(code **)(piVar1[6] + 4))(param_2[1],0x53,piVar1 == piVar2);
      FUN_00626470(uVar4);
    }
  }
  return;
}

