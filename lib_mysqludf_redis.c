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

/**
 * redis_command2
 * 
 * executes the argument commandstring and returns its output.
 */
DLLEXP 
my_bool redis_command2_init(
	UDF_INIT *initid
,	UDF_ARGS *args
,	char *message
);

DLLEXP 
void redis_command2_deinit(
	UDF_INIT *initid
);

DLLEXP 
char* redis_command2(
	UDF_INIT *initid
,	UDF_ARGS *args
,	char* result
,	unsigned long* length
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
	UDF_INIT *initid
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
	UDF_INIT *initid
){
/**
 * empty function
*/
}

char* lib_mysqludf_redis_info(
	UDF_INIT *initid
,	UDF_ARGS *args
,	char* result
,	unsigned long* length
,	char *is_null
,	char *error
){
	strcpy(result,LIBVERSION);
	*length = strlen(LIBVERSION);
	return result;
}


my_bool redis_command_init(
	UDF_INIT *initid
,	UDF_ARGS *args
,	char *message
){
	unsigned int i=0;
	if(args->arg_count == 1
	&& args->arg_type[i]==STRING_RESULT){
		return 0;
	} else {
		strcpy(
			message
		,	"Expected exactly one string type parameter"
		);		
		return 1;
	}
}
void redis_command_deinit(
	UDF_INIT *initid
){
}
my_ulonglong redis_command(
	UDF_INIT *initid
,	UDF_ARGS *args
,	char *is_null
,	char *error
){
	return system(args->args[0]);
}

my_bool redis_command2_init(
	UDF_INIT *initid
,	UDF_ARGS *args
,	char *message
){
	unsigned int i=0;
	if(args->arg_count == 1
	&& args->arg_type[i]==STRING_RESULT){
		return 0;
	} else {
		strcpy(
			message
		,	"Expected exactly one string type parameter"
		);		
		return 1;
	}
}
void redis_command2_deinit(
	UDF_INIT *initid
){
}
char* redis_command2(
	UDF_INIT *initid
,	UDF_ARGS *args
,	char* result
,	unsigned long* length
,	char *is_null
,	char *error
){
	FILE *pipe;
	char line[1024];
	unsigned long outlen, linelen;

	result = malloc(1);
	outlen = 0;

	pipe = popen(args->args[0], "r");

	while (fgets(line, sizeof(line), pipe) != NULL) {
		linelen = strlen(line);
		result = realloc(result, outlen + linelen);
		strncpy(result + outlen, line, linelen);
		outlen = outlen + linelen;
	}

	pclose(pipe);

	if (!(*result) || result == NULL) {
		*is_null = 1;
	} else {
		result[outlen] = 0x00;
		*length = strlen(result);
	}

	return result;
}


#endif /* HAVE_DLOPEN */
