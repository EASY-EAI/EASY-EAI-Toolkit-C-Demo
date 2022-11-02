/**
 *
 * Copyright 2021 by Guangzhou Easy EAI Technologny Co.,Ltd.
 * website: www.easy-eai.com
 *
 * Author: Jiehao.Zhong <zhongjiehao@easy-eai.com>
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * License file for more details.
 * 
 */

#ifndef LOG_MANAGER_H
#define LOG_MANAGER_H

#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

#define PD_DEFAULT_LOG_PATH 	"/userdata/logs"	//日志的默认存放目录

// 定义打印形式 (每次只能选择其中一样)
#define PRINT_TO_NONE	    0       // 不打印任何东西
#define PRINT_TO_LOCAL      1       // 打印到本地shell
#define PRINT_TO_FILE       2       // 打印到同名.log文件

extern int32_t printLog(char const *filePath, int lineNum, char const *funcName, int logLevel, char const *logCon, va_list args);
extern int32_t preSet_defalut_log_path(const char *path);
extern void log_manager_init(const char * const strConfigPath, const char * const strModuleName);


// printfMsg仅头文件内部使用，不建议被外部调用
inline int32_t printMsg(char const *filePath, int lineNum, char const *funcName, int logLevel, char const *logCon, ...){
    va_list args;
    va_start(args, logCon); //把参数列表栈指针定位到logCon上
    return printLog(filePath, lineNum, funcName, logLevel, logCon, args);
}
// 定义打印级别
#define PRINT_LEVEL_NONE    0       // 不输出打印信息
#define PRINT_LEVEL_ERROR   1       // 错误信息, 否定判断时添加
#define PRINT_LEVEL_DEBUG   2       // 调试信息, 调试时添加
#define PRINT_LEVEL_TRACE   3       // 堆栈跟踪, 跟踪时添加
#define PRINT_TRACE(str, args...) \
	printMsg(__FILE__, __LINE__, __FUNCTION__, PRINT_LEVEL_TRACE, str, ##args)
#define PRINT_DEBUG(str, args...) \
	printMsg(__FILE__, __LINE__, __FUNCTION__, PRINT_LEVEL_DEBUG, str, ##args)
#define PRINT_ERROR(str, args...) \
	printMsg(__FILE__, __LINE__, __FUNCTION__, PRINT_LEVEL_ERROR, str, ##args)

#ifdef __cplusplus
}
#endif

#endif


