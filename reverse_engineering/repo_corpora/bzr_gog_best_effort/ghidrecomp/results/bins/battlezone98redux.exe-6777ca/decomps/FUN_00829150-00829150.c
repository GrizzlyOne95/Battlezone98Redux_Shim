
void FUN_00829150(undefined4 param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 local_274 [8];
  long local_26c;
  FILE *local_268;
  int local_264;
  char local_25d;
  undefined1 local_25c [24];
  char local_244 [300];
  undefined1 local_118 [256];
  undefined1 local_18 [16];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  FUN_00827640(local_18,param_1);
  local_264 = FUN_00828850(local_18);
  iVar1 = FUN_00828940(local_264,local_118);
  if (iVar1 != 0) {
    FUN_004fbb60();
    FUN_00426a60(local_118,0);
    local_25d = FUN_00767a00(local_25c,local_274);
    FUN_004180b0();
    if (local_25d == '\0') {
      iVar1 = FUN_00827620(local_118,&DAT_008a2458);
      if (iVar1 != 0) {
        if (*(int *)(local_264 + 0x1000) == 0) {
          uVar2 = FUN_008271b0(local_118,0);
          *(undefined4 *)(local_264 + 0x1000) = uVar2;
          if (*(int *)(local_264 + 0x1000) == 0) goto LAB_0082937f;
        }
        local_26c = FUN_00827390(*(undefined4 *)(local_264 + 0x1000),local_18);
        if (local_26c == -1) {
          sprintf(&DAT_009467c0,"Could not find record \"%.16s\" in file \"%.16s\"",local_18,
                  *(int *)(local_264 + 0x1000) + 4);
        }
      }
    }
    else {
      sprintf(local_244,"%s%s%s",local_118,&DAT_00871328,local_18);
      local_268 = fopen(local_244,"rb");
      if (local_268 == (FILE *)0x0) {
        sprintf(&DAT_009467c0,"Couldn\'t open file \"%s\"",local_244);
      }
      else {
        setvbuf(local_268,(char *)0x0,4,0);
        fseek(local_268,0,2);
        local_26c = ftell(local_268);
        fclose(local_268);
      }
    }
  }
LAB_0082937f:
  FUN_0083e885();
  return;
}

