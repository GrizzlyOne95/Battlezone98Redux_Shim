
void FUN_00691450(int *param_1,int param_2,undefined4 param_3)

{
  char cVar1;
  ushort *puVar2;
  int iVar3;
  int local_41c;
  float local_418;
  int local_410;
  int local_40c;
  float afStack_408 [128];
  int aiStack_208 [128];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_40c = 0;
  local_410 = 0;
  do {
    puVar2 = (ushort *)(local_40c * 0xc + *(int *)(param_2 + 0xc));
    cVar1 = FUN_006a01f0(*puVar2,(char)*param_1);
    if (cVar1 == '\0') {
      iVar3 = FUN_00691230(*puVar2,*param_1);
      if (iVar3 != 0) goto LAB_006914ca;
      aiStack_208[local_40c] = 0;
    }
    else {
LAB_006914ca:
      aiStack_208[local_40c] = 1;
      iVar3 = FUN_006a0210(*puVar2,(char)*param_1);
      afStack_408[local_40c] =
           (float)(iVar3 + *(int *)(*(int *)(&DAT_00930fc0 + *param_1 * 4) + (uint)*puVar2 * 4)) /
           (float)*(int *)(puVar2 + 2);
      if ((local_410 == 0) || (local_418 < afStack_408[local_40c])) {
        local_418 = afStack_408[local_40c];
        local_41c = local_40c;
      }
      local_410 = local_410 + 1;
    }
    local_40c = local_40c + 1;
    if (*(int *)(param_2 + 8) <= local_40c) {
      if (0 < local_410) {
        local_40c = 0;
        do {
          if ((aiStack_208[local_40c] != 0) && ((local_40c != local_41c || (local_410 == 1)))) {
            FUN_00690df0(param_1,*(undefined2 *)(*(int *)(param_2 + 0xc) + local_40c * 0xc),param_3,
                         1,3,0);
          }
          local_40c = local_40c + 1;
        } while (local_40c < *(int *)(param_2 + 8));
      }
      FUN_0083e885();
      return;
    }
  } while( true );
}

