
void FUN_0082e8e4(int param_1,char *param_2,int param_3)

{
  char cVar1;
  undefined4 *puVar2;
  double *pdVar3;
  int iVar4;
  char *pcVar5;
  undefined4 uVar6;
  char *pcVar7;
  int local_34;
  char local_30;
  char local_2f;
  undefined1 local_2e;
  char local_2c [4];
  double *local_28;
  int *local_24;
  char local_20 [24];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_34 = 1;
  FUN_0082ebda(param_1,&DAT_008a1ad8);
  pcVar5 = strchr(param_2,0x25);
  if (pcVar5 == (char *)0x0) {
    local_34 = 1;
  }
  else {
    local_24 = (int *)(param_3 + -4);
    local_28 = (double *)(param_3 + -8);
    do {
      puVar2 = *(undefined4 **)(param_1 + 8);
      uVar6 = FUN_008309f4(param_1,param_2,(int)pcVar5 - (int)param_2);
      *puVar2 = uVar6;
      puVar2[2] = 4;
      if (*(int *)(param_1 + 0x1c) - *(int *)(param_1 + 8) < 0x11) {
        FUN_0082f194(param_1,1);
      }
      *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 0x10;
      pdVar3 = *(double **)(param_1 + 8);
      cVar1 = pcVar5[1];
      if (cVar1 == '%') {
        pcVar7 = "%";
LAB_0082ea8c:
        FUN_0082ebda(param_1,pcVar7);
      }
      else {
        if (cVar1 == 'c') {
          local_28 = (double *)((int)local_28 + 4);
          local_24 = local_24 + 1;
          local_2c[1] = 0;
          local_2c[0] = (char)*local_24;
          pcVar7 = local_2c;
          goto LAB_0082ea8c;
        }
        if (cVar1 == 'd') {
          local_28 = (double *)((int)local_28 + 4);
          local_24 = local_24 + 1;
          iVar4 = *local_24;
          *(undefined4 *)(pdVar3 + 1) = 3;
          *pdVar3 = (double)iVar4;
          if (*(int *)(param_1 + 0x1c) - *(int *)(param_1 + 8) < 0x11) {
            FUN_0082f194(param_1,1);
          }
          *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 0x10;
        }
        else if (cVar1 == 'f') {
          local_24 = local_24 + 2;
          local_28 = local_28 + 1;
          *pdVar3 = *local_28;
          *(undefined4 *)(pdVar3 + 1) = 3;
          if (*(int *)(param_1 + 0x1c) - *(int *)(param_1 + 8) < 0x11) {
            FUN_0082f194(param_1,1);
          }
          *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 0x10;
        }
        else {
          if (cVar1 != 'p') {
            if (cVar1 == 's') {
              local_28 = (double *)((int)local_28 + 4);
              local_24 = local_24 + 1;
              pcVar7 = "(null)";
              if (*local_24 != 0) {
                pcVar7 = (char *)*local_24;
              }
            }
            else {
              local_30 = '%';
              local_2e = 0;
              pcVar7 = &local_30;
              local_2f = cVar1;
            }
            goto LAB_0082ea8c;
          }
          local_28 = (double *)((int)local_28 + 4);
          local_24 = local_24 + 1;
          sprintf(local_20,"%p",*local_24);
          FUN_0082ebda(param_1,local_20);
        }
      }
      param_2 = pcVar5 + 2;
      local_34 = local_34 + 2;
      pcVar5 = strchr(param_2,0x25);
    } while (pcVar5 != (char *)0x0);
  }
  FUN_0082ebda(param_1,param_2);
  FUN_00831f3a(param_1,local_34 + 1,(*(int *)(param_1 + 8) - *(int *)(param_1 + 0xc) >> 4) + -1);
  *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + local_34 * -0x10;
  FUN_0083e885();
  return;
}

