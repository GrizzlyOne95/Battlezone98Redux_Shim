
undefined4 FUN_00699250(char param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = isalnum((int)param_1);
  if (iVar1 == 0) {
    if (param_1 == ';') {
      uVar2 = 2;
    }
    else if (param_1 == '\"') {
      uVar2 = 2;
    }
    else if (param_1 == '{') {
      uVar2 = 2;
    }
    else if (param_1 == '}') {
      uVar2 = 2;
    }
    else if (param_1 == '\'') {
      uVar2 = 2;
    }
    else if (param_1 == '=') {
      uVar2 = 2;
    }
    else if (param_1 == '!') {
      uVar2 = 2;
    }
    else if (param_1 == '<') {
      uVar2 = 2;
    }
    else if (param_1 == '>') {
      uVar2 = 2;
    }
    else if (param_1 == '.') {
      uVar2 = 2;
    }
    else if (param_1 == ',') {
      uVar2 = 2;
    }
    else if (param_1 == '(') {
      uVar2 = 2;
    }
    else if (param_1 == ')') {
      uVar2 = 2;
    }
    else if (param_1 == '[') {
      uVar2 = 2;
    }
    else if (param_1 == ']') {
      uVar2 = 2;
    }
    else if (param_1 == '*') {
      uVar2 = 2;
    }
    else if (param_1 == '^') {
      uVar2 = 2;
    }
    else if (param_1 == '+') {
      uVar2 = 2;
    }
    else if (param_1 == '/') {
      uVar2 = 2;
    }
    else if (param_1 == '-') {
      uVar2 = 2;
    }
    else if (param_1 == '#') {
      uVar2 = 2;
    }
    else if (param_1 == '_') {
      uVar2 = 1;
    }
    else {
      uVar2 = 0;
    }
  }
  else {
    uVar2 = 1;
  }
  return uVar2;
}

