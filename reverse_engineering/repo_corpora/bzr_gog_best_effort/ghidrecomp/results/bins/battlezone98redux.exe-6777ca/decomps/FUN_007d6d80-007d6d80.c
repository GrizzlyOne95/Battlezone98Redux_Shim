
undefined4 FUN_007d6d80(undefined4 param_1,undefined4 param_2)

{
  switch(param_2) {
  case 0:
    basic_string<>("Not Implemented");
    break;
  case 1:
    basic_string<>("JSON Value Truncated");
    break;
  case 2:
    basic_string<>("JSON Syntax Error");
    break;
  case 3:
    basic_string<>("API usage error, a parameter to a function is not valid");
    break;
  case 4:
    basic_string<>(
                  "An unexpected exception occurred: this probably indicates an error with the JSON parser."
                  );
    break;
  case 5:
    basic_string<>("The parsed JSON has a different type than was requested");
    break;
  default:
    basic_string<>("API Error");
  }
  return param_1;
}

