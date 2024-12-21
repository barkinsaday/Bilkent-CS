struct item {
	int id;
	char* request_type;//[4];
	char* value; //[64];
};

//Struct ARG is for passing multiple arguments to threads
struct arg{
   FILE* file;
   int* a;//To pass the index of thread -- WILL BE DELETED, also only used in client
   mqd_t arg_mq;//MQ1
   mqd_t arg_mq2;//MQ2
};
#define MQNAME "/justaname"
#define MQ2 "/secondmq"

