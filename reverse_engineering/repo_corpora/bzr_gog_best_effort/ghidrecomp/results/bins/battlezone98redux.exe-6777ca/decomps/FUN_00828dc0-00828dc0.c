
void FUN_00828dc0(undefined4 param_1,size_t *param_2,void *param_3,int param_4)

{
  int iVar1;
  size_t sVar2;
  undefined4 uVar3;
  undefined1 local_280 [8];
  void *local_278;
  int local_274;
  char local_26d;
  FILE *local_26c;
  undefined1 local_268 [24];
  char local_250 [300];
  undefined1 local_124 [256];
  undefined1 local_24 [16];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008651fb;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_00827640(local_24,param_1,local_14);
  local_274 = FUN_00828850(local_24);
  iVar1 = FUN_00828940(local_274,local_124);
  if (iVar1 != 0) {
    FUN_004fbb60();
    FUN_00426a60(local_124,0);
    local_8 = 0;
    local_26d = FUN_00767a00(local_268,local_280);
    local_8 = 0xffffffff;
    FUN_004180b0();
    if (local_26d == '\0') {
      iVar1 = FUN_00827620(local_124,&DAT_008a2458);
      if (iVar1 != 0) {
        if (*(int *)(local_274 + 0x1000) == 0) {
          uVar3 = FUN_008271b0(local_124,0);
          *(undefined4 *)(local_274 + 0x1000) = uVar3;
          if (*(int *)(local_274 + 0x1000) == 0) goto LAB_008290d6;
        }
        if (param_3 == (void *)0x0) {
          __aligned_offset_malloc(*(size_t *)(local_274 + 0x1000),(size_t)local_24,(size_t)param_2);
        }
        else {
          FUN_008275a0(*(undefined4 *)(local_274 + 0x1000),local_24,param_2,param_3,param_4);
        }
      }
    }
    else {
      sprintf(local_250,"%s%s%s",local_124,&DAT_00871328,local_24);
      local_26c = fopen(local_250,"rb");
      if (local_26c == (FILE *)0x0) {
        sprintf(&DAT_009467c0,"Couldn\'t open file \"%s\"",local_250);
      }
      else {
        setvbuf(local_26c,(char *)0x0,4,0);
        fseek(local_26c,0,2);
        sVar2 = ftell(local_26c);
        *param_2 = sVar2;
        if (param_3 == (void *)0x0) {
          local_278 = malloc(*param_2);
        }
        else {
          if (param_4 < (int)*param_2) {
            fclose(local_26c);
            goto LAB_008290d6;
          }
          local_278 = param_3;
        }
        fseek(local_26c,0,0);
        sVar2 = fread(local_278,*param_2,1,local_26c);
        if (sVar2 == 0) {
          sprintf(&DAT_009467c0,"Could not read file \"%s\"",local_250);
          if (param_3 == (void *)0x0) {
            free(local_278);
          }
          fclose(local_26c);
        }
        else {
          fclose(local_26c);
        }
      }
    }
  }
LAB_008290d6:
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

