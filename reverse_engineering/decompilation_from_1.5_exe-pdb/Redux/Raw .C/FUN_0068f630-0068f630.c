
void FUN_0068f630(undefined4 *param_1)

{
  int iVar1;
  
  FUN_006a5fd0("AI   Team %d Unit %p",(int)*(char *)(param_1 + 4),*param_1);
  iVar1 = FUN_006a0f70(param_1);
  if (iVar1 == 0) {
    FUN_0068fb10(param_1);
  }
  else {
    FUN_006a5fd0("AI_PartIntoTeam: Special Force Unit %p ignored\n",*param_1);
  }
  return;
}

