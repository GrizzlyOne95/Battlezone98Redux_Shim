
float10 __thiscall FUN_005a22c0(int *param_1,float param_2,float param_3)

{
  char cVar1;
  int *piVar2;
  float10 fVar3;
  int local_10;
  float local_c;
  
  if (param_2 < (float)param_1[0x1b]) {
    param_1[0x1b] = (int)param_2;
  }
  local_c = ((250.0 - param_3) / 250.0) * 5.0 + (param_2 - (float)param_1[0x1b]);
  fVar3 = (float10)(**(code **)(*param_1 + 0x1c))();
  if (((float)fVar3 != (float)param_1[0x1d]) && (param_3 < 250.0)) {
    local_c = local_c + 1.0;
  }
  fVar3 = (float10)(**(code **)(*param_1 + 0x1c))();
  if (((float)fVar3 < 0.0) || ((*(uint *)(param_1[0x37] + 0x14) & 0x1000200) != 0)) {
    local_c = local_c + 10.0;
  }
  if (param_1[0x62] != 0) {
    for (local_10 = 0; local_10 < 5; local_10 = local_10 + 1) {
      piVar2 = (int *)FUN_00417f60(local_10);
      if ((piVar2 != (int *)0x0) && (*(int *)(piVar2[2] + 0xc) == 0x534e4950)) {
        cVar1 = (**(code **)(*piVar2 + 0x10))();
        if (cVar1 != '\0') {
          local_c = local_c + 2.0;
        }
      }
    }
  }
  return (float10)local_c;
}

