
void FUN_00783630(void)

{
  undefined4 uVar1;
  int iVar2;
  undefined1 *puVar3;
  undefined4 uVar4;
  float fVar5;
  float fVar6;
  undefined4 uVar7;
  float local_18;
  float local_10;
  int local_c;
  int local_8;
  
  if (DAT_02ceb834 <= 0.999) {
    fVar5 = (DAT_02ceb834 * 5.0) / (DAT_02ceb830 * 0.1);
    uVar7 = 0x457ff000;
    FUN_007d6a70("Building shadows... ");
    uVar1 = FUN_00822e60();
    for (local_c = DAT_02cd9984; local_c < DAT_02ce99c4; local_c = local_c + 1) {
      if (DAT_02ceb830 <= 0.0) {
        iVar2 = FUN_0077d640(DAT_02ce99c0,local_c);
        fVar6 = (float)iVar2;
        local_8 = DAT_02ce99c0;
        while( true ) {
          local_8 = local_8 + 1;
          local_18 = fVar6 + fVar5;
          if (DAT_02ce99a0 <= local_8) break;
          iVar2 = FUN_0077d640(local_8,local_c);
          fVar6 = (float)iVar2;
          if (fVar6 < local_18) {
            puVar3 = (undefined1 *)FUN_0050ce30(local_8,local_c);
            *puVar3 = 0;
            fVar6 = local_18;
          }
        }
      }
      else {
        iVar2 = FUN_0077d640(DAT_02ce99a0 + -1,local_c);
        local_10 = (float)iVar2 - fVar5;
        for (local_8 = DAT_02ce99a0 + -2; local_10 = local_10 - fVar5, DAT_02ce99c0 <= local_8;
            local_8 = local_8 + -1) {
          iVar2 = FUN_0077d640(local_8,local_c);
          fVar6 = (float)iVar2;
          if ((float)iVar2 < local_10) {
            puVar3 = (undefined1 *)FUN_0050ce30(local_8,local_c);
            *puVar3 = 0;
            fVar6 = local_10;
          }
          local_10 = fVar6;
        }
      }
    }
    uVar4 = FUN_00822e60();
    FUN_007d6a70(&DAT_0087a44c,uVar4,uVar1,uVar7);
  }
  return;
}

