
void FUN_00680920(int param_1)

{
  int iVar1;
  int *piVar2;
  
  if ((*(int *)(param_1 + 200) == 0) && (iVar1 = *(int *)(param_1 + 0xc0), iVar1 != 0)) {
    piVar2 = (int *)(**(code **)(**(int **)(DAT_00920ea0 + 8) + 0x164))();
    piVar2 = (int *)(**(code **)(*piVar2 + 0x180))(ZERO_exref,IDENTITY_exref);
    (**(code **)(*piVar2 + 0x124))(iVar1);
    (**(code **)(*piVar2 + 0x38))(0xbf800000,0x3f800000,0xbf800000);
    *(int **)(param_1 + 200) = piVar2;
  }
  return;
}

