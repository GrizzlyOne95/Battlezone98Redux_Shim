
char FUN_00461d10(undefined4 param_1)

{
  int local_10;
  int local_c;
  char local_5;
  
  local_5 = FUN_004ce1c0(param_1,"[AiTasks]");
  if (local_5 != '\0') {
    local_5 = FUN_004ce910(param_1,&local_10,4);
    for (local_c = 0; (local_5 != '\0' && (local_c < local_10)); local_c = local_c + 1) {
      FUN_005d7370(param_1);
    }
  }
  return local_5;
}

