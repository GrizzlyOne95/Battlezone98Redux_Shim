
void FUN_00695340(void *param_1)

{
  undefined4 uVar1;
  int local_8;
  
  FUN_006a5fd0("AI_Team::Delete Begins\n");
  FUN_0069f010(*(undefined4 *)((int)param_1 + 0x598),0,*(int *)((int)param_1 + 0x78) + -1,0,
               *(int *)((int)param_1 + 0x7c) + -1);
  FUN_006930e0(param_1);
  std::_Destroy_range<struct_std::_Wrap_alloc<class_std::allocator<unsigned_char>_>_>(param_1);
  FUN_00695130(param_1);
  FUN_00693140(param_1);
  if (*(int *)((int)param_1 + 0x60) != 0) {
    *(undefined4 *)((int)param_1 + 0x60) = 0;
  }
  FUN_006a5fd0("AI_Team::Delete   freeing all squads\n");
  FUN_006a8760((int)param_1 + 0x1c,"Schedule\\ai_team.cpp",0x1b7);
  for (local_8 = 0; local_8 < *(int *)((int)param_1 + 0x24); local_8 = local_8 + 1) {
    uVar1 = FUN_0069d590((int)param_1 + 0x1c,local_8);
    FUN_006a8900(uVar1);
  }
  for (local_8 = 0; local_8 < *(int *)((int)param_1 + 0x38); local_8 = local_8 + 1) {
    uVar1 = FUN_0069d590((int)param_1 + 0x30,local_8);
    FUN_006a8900(uVar1);
  }
  FUN_006a5fd0("AI_Team::Delete   freeing linked list of pointers to attack_squads\n");
  FUN_0069d280((int)param_1 + 0x30);
  FUN_006a5fd0("AI_Team::Delete   freeing linked list of pointers to squads\n");
  FUN_0069d280((int)param_1 + 0x1c);
  FUN_006a5fd0("AI_Team::Delete   freeing linked list of pointers to units\n");
  FUN_0069d280((int)param_1 + 8);
  FUN_006a5fd0("AI_Team::Delete   freeing targets\n");
  FUN_00694ed0(param_1);
  if (*(int *)((int)param_1 + 0xa4) == 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = FUN_00695530(1);
  }
  FUN_006a5fd0("AI_Team::Delete   freeing team structure memory\n",uVar1);
  free(param_1);
  FUN_006a5fd0("AI_Team::Delete Ends\n");
  return;
}

