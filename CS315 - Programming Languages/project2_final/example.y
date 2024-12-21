%token TEXT THIS BEGINN ENDD IF IFF ELSE LOOP BOOL_TRUE BOOL_FALSE SENSOR STRING BOOLEAN INT FLOAT LIST OBJECT VOID FUNCTION STATIC RETURN CONNECT_TO_URL GET_TIME GET_INPUT SEND_INPUT PRINT LENGTH GET_SENSORS GET_SENSOR_INPUT TURN_ON_SWITCH TURN_OFF_SWITCH GET_SWITCH GET_NAME IS_EQUAL_OP IS_NOT_EQUAL_OP GREATER_OP GREATER_OR_EQUAL_OP LESS_OR_EQUAL_OP LESS_OP ASSIGN_OP ADD_OP SUB_OP MUL_OP DIV_OP AND_OP OR_OP NOT_OP SEMI_COLON COLON COMMA DOT LCURL RCURL LP RP LSQUARE RSQUARE IDENTIFIER INT_VALUE FLOAT_VALUE
%%

/* Program Start */

program: BEGINN stmts ENDD {printf("Input program is valid!\n"); return 0;}

stmts: 	stmt | stmt stmts 
       	;

stmt: 	matched | unmatched | non_if_stmt SEMI_COLON
	;

matched: IFF LP bool_ex RP LCURL stmts RCURL ELSE LCURL stmts RCURL
	 ;

unmatched: IF LP bool_ex RP LCURL stmts RCURL
	   ;

non_if_stmt: assign | func_call | return_stmt | loop | static_func
	     ;

assign: type IDENTIFIER ASSIGN_OP expr | chain ASSIGN_OP expr
	;

return_stmt: RETURN expr
	     ;

/* Expressions */

chain: IDENTIFIER | call_array | chain DOT IDENTIFIER  | chain DOT call_array
       ;

expr: arith_expr | TEXT | object 
		 | array | bool_ex | call_array
		 ;

arith_expr: arith_expr ADD_OP term
	    | arith_expr SUB_OP term
	    | term
	    ;

term: term MUL_OP exp
      | term DIV_OP exp | exp
      ;

exp:  LP arith_expr RP | IDENTIFIER | constant_value | func_call
      ;

bool_ex: bool_ex OR_OP bool_term 
	 | bool_term
	 ;

bool_term: bool_term AND_OP bool_factor 
	   | bool_factor
	 ;

bool_factor: NOT_OP bool_exp | bool_exp 
	   ;

bool_exp: LP bool_ex RP | bool_value | arith_expr comparison arith_expr
	;

call_array: IDENTIFIER LSQUARE expr RSQUARE
	    ;

/* Functions */

func_call: chain LP call_list RP | chain LP RP | built_in_func
	   ;

static_func: STATIC type FUNCTION IDENTIFIER LP decleration_list RP LCURL stmts RCURL 
	     | STATIC VOID FUNCTION IDENTIFIER LP decleration_list RP LCURL stmts RCURL 
	     | STATIC type FUNCTION IDENTIFIER LP  RP LCURL stmts RCURL 
	     | STATIC VOID FUNCTION IDENTIFIER LP  RP LCURL stmts RCURL 
	     ;

object_func: type FUNCTION IDENTIFIER LP decleration_list RP LCURL stmts RCURL 
	     | VOID FUNCTION IDENTIFIER LP decleration_list RP LCURL stmts RCURL 
	     | type FUNCTION IDENTIFIER LP  RP LCURL stmts RCURL 
	     | VOID FUNCTION IDENTIFIER LP RP LCURL stmts RCURL 
	     ;

built_in_func: chain DOT CONNECT_TO_URL LP call_list RP
	       | PRINT LP call_list RP | GET_TIME LP RP
	       | chain DOT  GET_INPUT LP RP
	       | chain DOT SEND_INPUT LP call_list RP
	       | chain DOT LENGTH LP RP
	       | THIS DOT GET_SENSORS LP RP
	       | chain DOT GET_SENSORS LP RP
	       | chain DOT GET_SENSOR_INPUT LP RP
	       | chain DOT TURN_ON_SWITCH LP call_list RP
	       | chain DOT TURN_OFF_SWITCH LP call_list RP
	       | chain DOT GET_SWITCH LP call_list RP
	       | chain DOT GET_NAME LP RP
	       ;

call_list: expr COMMA call_list
	   | expr 
	   ;

decleration_list:  type IDENTIFIER COMMA decleration_list 
	   	   | type IDENTIFIER 
	           ;

/* Types */

type: prim | LIST | OBJECT | SENSOR
      ;

prim: BOOLEAN | INT | FLOAT | STRING
      ;

bool_value: BOOL_TRUE | BOOL_FALSE
	    ;

constant_value: INT_VALUE | FLOAT_VALUE
		;

/* Object Decleration */
object: LCURL properties methods RCURL | LCURL properties RCURL
	;

properties: type IDENTIFIER COLON expr 
	    |type IDENTIFIER COLON expr COMMA properties
	    ;

methods: object_func | object_func COMMA methods 
	 ;

/* List Declaration */

array: LSQUARE call_list RSQUARE
       ;

/* LOOPS */

loop: LOOP LP bool_ex RP LCURL stmts RCURL
      ;

/* Operators */
comparison: IS_EQUAL_OP | IS_NOT_EQUAL_OP
	    | GREATER_OP | GREATER_OR_EQUAL_OP
	    | LESS_OP | LESS_OR_EQUAL_OP
	    ;

%%
#include "lex.yy.c"
int yyerror(char* s){
  fprintf(stderr, "%s on line %d\n",s, yylineno);
  return 1;
}

int main(){
  yyparse();
  return 0;
}
