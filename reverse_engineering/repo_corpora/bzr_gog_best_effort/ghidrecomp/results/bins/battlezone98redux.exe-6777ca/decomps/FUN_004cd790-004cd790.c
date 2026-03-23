
/* WARNING: Removing unreachable block (ram,0x004cd809) */

undefined1 FUN_004cd790(FILE *param_1,int param_2,uint param_3,undefined4 param_4)

{
  bool bVar1;
  char cVar2;
  int iVar3;
  int local_c;
  undefined1 local_5;
  
  if (DAT_009173b6 == '\0') {
    FUN_004cc410(1,1,0xb,param_3);
    iVar3 = fprintf(param_1,"%s [%d] =\r\n",param_4,param_3 >> 6);
    for (local_c = 0; local_c < (int)(param_3 >> 6); local_c = local_c + 1) {
      cVar2 = FUN_004cd360(param_1,local_c * 0x40 + param_2,4,"  right_x",iVar3);
      if (((((cVar2 == '\0') ||
            (cVar2 = FUN_004cd360(param_1,param_2 + 4 + local_c * 0x40,4,"  right_y",iVar3),
            cVar2 == '\0')) ||
           (cVar2 = FUN_004cd360(param_1,param_2 + 8 + local_c * 0x40,4,"  right_z",iVar3),
           cVar2 == '\0')) ||
          ((((cVar2 = FUN_004cd360(param_1,param_2 + 0xc + local_c * 0x40,4,"  up_x",iVar3),
             cVar2 == '\0' ||
             (cVar2 = FUN_004cd360(param_1,param_2 + 0x10 + local_c * 0x40,4,"  up_y"),
             cVar2 == '\0')) ||
            ((cVar2 = FUN_004cd360(param_1,param_2 + 0x14 + local_c * 0x40,4,"  up_z"),
             cVar2 == '\0' ||
             ((cVar2 = FUN_004cd360(param_1,param_2 + 0x18 + local_c * 0x40,4,"  front_x"),
              cVar2 == '\0' ||
              (cVar2 = FUN_004cd360(param_1,param_2 + 0x1c + local_c * 0x40,4,"  front_y"),
              cVar2 == '\0')))))) ||
           (cVar2 = FUN_004cd360(param_1,param_2 + 0x20 + local_c * 0x40,4,"  front_z"),
           cVar2 == '\0')))) ||
         (((cVar2 = FUN_004cd440(param_1,param_2 + 0x28 + local_c * 0x40,8,"  posit_x"),
           cVar2 == '\0' ||
           (cVar2 = FUN_004cd440(param_1,param_2 + 0x30 + local_c * 0x40,8,"  posit_y"),
           cVar2 == '\0')) ||
          (cVar2 = FUN_004cd440(param_1,param_2 + 0x38 + local_c * 0x40,8,"  posit_z"),
          cVar2 == '\0')))) {
        bVar1 = false;
      }
      else {
        bVar1 = true;
      }
      if (!bVar1) {
        return 0;
      }
    }
    local_5 = 1;
  }
  else {
    local_5 = FUN_004ccae0(param_1,0xb,param_3,param_2);
  }
  return local_5;
}

