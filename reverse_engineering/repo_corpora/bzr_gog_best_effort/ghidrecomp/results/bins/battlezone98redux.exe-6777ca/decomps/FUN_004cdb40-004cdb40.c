
undefined1 FUN_004cdb40(FILE *param_1,int param_2,uint param_3,undefined4 param_4)

{
  char cVar1;
  int iVar2;
  bool bVar3;
  undefined1 local_10;
  
  if (DAT_009173b6 == '\0') {
    FUN_004cc410(1,0,0xfe,0,param_3 / 0x48);
    iVar2 = fprintf(param_1,"%s =\r\n",param_4);
    bVar3 = -1 < iVar2;
  }
  else {
    bVar3 = true;
  }
  if ((((((bVar3) && (cVar1 = FUN_004cd360(param_1,param_2,4," mass"), cVar1 != '\0')) &&
        (cVar1 = FUN_004cd360(param_1,param_2 + 4,4," mass_inv"), cVar1 != '\0')) &&
       ((cVar1 = FUN_004cd360(param_1,param_2 + 8,4," v_mag"), cVar1 != '\0' &&
        (cVar1 = FUN_004cd360(param_1,param_2 + 0xc,4," v_mag_inv"), cVar1 != '\0')))) &&
      ((cVar1 = FUN_004cd360(param_1,param_2 + 0x10,4,&DAT_00879820), cVar1 != '\0' &&
       ((cVar1 = FUN_004cd360(param_1,param_2 + 0x14,4,&DAT_00879824), cVar1 != '\0' &&
        (cVar1 = FUN_004cd520(param_1,param_2 + 0x18,0xc,&DAT_00879814), cVar1 != '\0')))))) &&
     ((cVar1 = FUN_004cd520(param_1,param_2 + 0x24,0xc," omega"), cVar1 != '\0' &&
      (cVar1 = FUN_004cd520(param_1,param_2 + 0x30,0xc," Accel"), cVar1 != '\0')))) {
    local_10 = 1;
  }
  else {
    local_10 = 0;
  }
  return local_10;
}

