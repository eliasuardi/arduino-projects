
boolean isContain(char* content, char* line)
{
  char* r = NULL;
  r = strstr(content, line);
  if(r) return true;  else  return false;
}

int getValueLength(char* line)
{
  int num;
  char*t;
  t = strtok(line," ");
  t=strtok(NULL, " ");
  num = atoi(t);
  
  return num;
}
