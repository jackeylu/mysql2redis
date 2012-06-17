/* 
	This library is free software; you can redistribute it and/or
	modify it under the terms of the GNU Lesser General Public
	License as published by the Free Software Foundation; either
	version 2.1 of the License, or (at your option) any later version.
	
	This library is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
	Lesser General Public License for more details.
	
	You should have received a copy of the GNU Lesser General Public
	License along with this library; if not, write to the Free Software
	Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/
#if defined(_WIN32) || defined(_WIN64) || defined(__WIN32__) || defined(WIN32)
#define DLLEXP __declspec(dllexport) 
#else
#define DLLEXP
#endif

#ifdef STANDARD
#include <string.h>
#include <stdlib.h>
#include <time.h>
#ifdef __WIN__
typedef unsigned __int64 ulonglong;
typedef __int64 longlong;
#else
typedef unsigned long long ulonglong;
typedef long long longlong;
#endif /*__WIN__*/
#else
#include <my_global.h>
#include <my_sys.h>
#endif
#include <mysql.h>
#include <m_ctype.h>
#include <m_string.h>
#include <stdlib.h>

#include <ctype.h>

/**
 * hiredis head file
 */
#include <hiredis/hiredis.h>

/*
 * self-defined head file
 */
#include "utils.h"


#ifdef HAVE_DLOPEN
#ifdef	__cplusplus
extern "C" {
#endif

#define LIBVERSION "lib_mysqludf_redis version 0.0.1"

#ifdef __WIN__
#define SETENV(name,value)		SetEnvironmentVariable(name,value);
#else
#define SETENV(name,value)		setenv(name,value,1);		
#endif

DLLEXP 
my_bool lib_mysqludf_redis_info_init(
	UDF_INIT *initid
,	UDF_ARGS *args
,	char *message
);

DLLEXP 
void lib_mysqludf_redis_info_deinit(
	UDF_INIT *initid
);

DLLEXP 
char* lib_mysqludf_redis_info(
	UDF_INIT *initid
,	UDF_ARGS *args
,	char* result
,	unsigned long* length
,	char *is_null
,	char *error
);

/**
 * redis_command
 * 
 * execute a redis command
 */
DLLEXP 
my_bool redis_command_init(
	UDF_INIT *initid
,	UDF_ARGS *args
,	char *message
);


DLLEXP 
void redis_command_deinit(
	UDF_INIT *initid
);

DLLEXP 
my_ulonglong redis_command(
	UDF_INIT *initid
,	UDF_ARGS *args
,	char *is_null
,	char *error
);


#ifdef	__cplusplus
}
#endif

/**
 * lib_mysqludf_redis_info
 */
my_bool lib_mysqludf_redis_info_init(
	UDF_INIT *initid __attribute__((__unused__))
,	UDF_ARGS *args
,	char *message
){
	my_bool status;
	if(args->arg_count!=0){
		strcpy(
			message
		,	"No arguments allowed (udf: lib_mysqludf_redis_info)"
		);
		status = 1;
	} else {
		status = 0;
	}
	return status;
}

void lib_mysqludf_redis_info_deinit(
	UDF_INIT *initid __attribute__((__unused__))
){
/**
 * empty function
*/
}

char* lib_mysqludf_redis_info(
	UDF_INIT *initid __attribute__((__unused__)),
	UDF_ARGS *args __attribute__((__unused__)),
	char* result,
	unsigned long* length,
	char *is_null __attribute__((__unused__)),
	char *error __attribute__((__unused__)))
{
	strcpy(result,LIBVERSION);
	*length = strlen(LIBVERSION);
	return result;
}


/**
 * redis_command implementation
 *
 * redis_command(host,port,command)
 *
 */
my_bool redis_command_init(
	UDF_INIT *initid __attribute__((__unused__))
,	UDF_ARGS *args
,	char *message
){
	if(args->arg_count == 3 && 
		args->arg_type[0]==STRING_RESULT &&
		args->arg_type[1]==INT_RESULT &&
		args->arg_type[2]==STRING_RESULT)
	{

		args->maybe_null = 0; // each parameter could not be NULL

		char *host = args->args[0];
		unsigned long host_len = args->lengths[0];
		long long port = *((long long*)args->args[1]);
		char *cmd = args->args[2];
		unsigned long cmd_len = args->lengths[3];

		if(!check_host(host) || !check_ip(host))
		{
			snprintf(message,MYSQL_ERRMSG_SIZE,
				"The first parameter is not a valid host or ip address");
			return 2;
		}

		if(port <= 0)
		{
			snprintf(message,MYSQL_ERRMSG_SIZE,
				"The second parameter must be an integer bigger than zero");
			return 2;
		}

		if(strlen(cmd) <=0 || NULL == cmd)
		{
			snprintf(message,MYSQL_ERRMSG_SIZE,"The third parameter error,[%s]\n",
					cmd);
			return 2;
		}
		// everthing looks OK.
		return 0;
		
		} else {
			snprintf(message,MYSQL_ERRMSG_SIZE,
				"redis_command(host,port,command) Expected exactly 3  parameteres, a string, an integer and a string" );		
			return 1;
		}

}
void redis_command_deinit(UDF_INIT *initid __attribute__((__unused__))){
	// nonthing need to be cleanup
}
/**
 * redis_command
 *
 * the implementation
 *
 * see the MySQL error log for the fprintf output
 *
 * @return 0 everything is OK
 *         1 connection error, check the host/port
 *         2 error with an NULL reply , it is so weird
 *         3 command may be not a valid command, or other error
 */
my_ulonglong redis_command(
		UDF_INIT *initid __attribute__((__unused__)),
		UDF_ARGS *args,
		char *is_null __attribute__((__unused__)),
		char *error __attribute__((__unused__))){
	char *host = args->args[0];
	long long port = *((long long*)args->args[1]);
	char *cmd = args->args[2];

	// about the redis
	redisContext *c = NULL;
	redisReply *reply = NULL;

	c = redisConnect(host,port);
	if (c->err)
	{
		fprintf(stderr,"connection error on (%s/%ld): %s\n",
				host,port,c->errstr);

		redisFree(c);
		c = NULL;
		return 1; 
	}

	reply = redisCommand(c,cmd);
	if(NULL == reply)
	{
		fprintf(stderr,"redisCommand %s,error: %s\n",
			cmd,c->errstr);
		redisFree(c);
		c = NULL;
		return 2;
	}


	if(REDIS_REPLY_ERROR==reply->type)
	{
		fprintf(stderr,"redisCommand \"%s\" reply error:%s\n",
			cmd,NULL == reply->str ? "NULL" : reply->str);
		freeReplyObject(reply);
		reply = NULL;
		redisFree(c);
		c = NULL;

		return 3;

	}

	// do the clean work
	freeReplyObject(reply);
	reply = NULL;
	redisFree(c);
	c = NULL;

	return 0;
}



#endif /* HAVE_DLOPEN */
