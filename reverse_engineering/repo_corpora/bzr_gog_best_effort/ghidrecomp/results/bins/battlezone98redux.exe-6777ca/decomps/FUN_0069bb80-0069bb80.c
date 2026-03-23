
void FUN_0069bb80(int param_1,int *param_2,int param_3,int param_4,int param_5,int param_6)

{
  int iVar1;
  double dVar2;
  int local_c;
  int local_8;
  
  local_c = 0;
  *param_2 = 0;
  while (*(char *)(param_1 + local_c) != '\0') {
    local_8 = FUN_0069b970(param_1,&local_c,*param_2 * 0x50 + param_5);
    if (local_8 == 1) {
      iVar1 = atoi((char *)(*param_2 * 0x50 + param_5));
      *(int *)(param_3 + *param_2 * 4) = iVar1;
      *(double *)(param_4 + *param_2 * 8) = (double)*(int *)(param_3 + *param_2 * 4);
    }
    else {
      *(undefined4 *)(param_3 + *param_2 * 4) = 0xffffffff;
    }
    if (local_8 == 3) {
      dVar2 = atof((char *)(*param_2 * 0x50 + param_5));
      *(double *)(param_4 + *param_2 * 8) = dVar2;
    }
    else {
      *(undefined8 *)(param_4 + *param_2 * 8) = 0xbff0000000000000;
    }
    *(int *)(param_6 + *param_2 * 4) = local_8;
    *param_2 = *param_2 + 1;
  }
  return;
}

