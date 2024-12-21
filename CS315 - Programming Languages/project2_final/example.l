%option yylineno
alphabetic [A-Za-z_$]
digit [0-9]
sign [+-]
anyChar [./n]
alphanumeric ({alphabetic}|{digit})
%%
\/\/(.)+ ;
\"(.)*\" return (TEXT);
begin return(BEGINN);
end return (ENDD);
iff return (IFF);
if return (IF);
else return (ELSE);
loop return (LOOP);
true return (BOOL_TRUE);
false return (BOOL_FALSE);
sensor return (SENSOR);
string return (STRING);
bool return (BOOLEAN);
int return (INT);
float return (FLOAT);
list return (LIST);
obj return (OBJECT);
void return (VOID);
func return (FUNCTION);
static return (STATIC);
return return (RETURN);
connectToURL return (CONNECT_TO_URL);
getTime return (GET_TIME);
getInput return (GET_INPUT);
sendInput return (SEND_INPUT);
print return (PRINT);
length return (LENGTH);
this return (THIS);
getSensors return (GET_SENSORS);
getSensorInput return(GET_SENSOR_INPUT);
turnOnSwitch return(TURN_ON_SWITCH);
turnOffSwitch return(TURN_OFF_SWITCH);
getSwitch return(GET_SWITCH);
getName return(GET_NAME);
\=\= return (IS_EQUAL_OP);
\!\= return (IS_NOT_EQUAL_OP);
\> return (GREATER_OP);
\>\= return (GREATER_OR_EQUAL_OP);
\<\= return (LESS_OR_EQUAL_OP);
\< return (LESS_OP);
\= return (ASSIGN_OP);
\+ return (ADD_OP);
\- return (SUB_OP);
\* return (MUL_OP);
\/ return (DIV_OP);
\& return (AND_OP);
\| return (OR_OP);
\! return (NOT_OP);
\; return (SEMI_COLON);
\: return (COLON);
\, return (COMMA);
\. return (DOT);
\{ return (LCURL);
\} return (RCURL);
\( return (LP);
\) return (RP);   
\[ return (LSQUARE); 
\] return (RSQUARE);
{alphabetic}{alphanumeric}*  return(IDENTIFIER);
{sign}?{digit}+ return(INT_VALUE);
{sign}?{digit}*(\.)?{digit}+ return(FLOAT_VALUE);
[ \t\n] ;
%%
int yywrap() {return 1;}
