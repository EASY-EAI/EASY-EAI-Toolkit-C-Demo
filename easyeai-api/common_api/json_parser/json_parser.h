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
 
#ifndef JSON_PARSER_H
#define JSON_PARSER_H

#include <stdint.h>


#if defined(__cplusplus)
extern "C" {
#endif

extern int32_t get_int32_from_json(const char *json_str, const char *key);
extern int32_t get_string_from_json(const char *json_str, const char *key, char *data, uint32_t dataLen);
extern int32_t get_object_from_json(const char *json_str, const char *key, char *data, uint32_t dataLen);

extern int32_t get_list_size_from_json(const char *json_str, const char *list_key);
extern int32_t get_int32_from_list(const char *json_str, const char *list_name, int pos, const char *key);
extern int32_t get_string_from_list(const char *json_str, const char *list_name, int pos, const char *key, char *data, uint32_t dataLen);

extern void clear_json_cache();
//type为空，默认按string处理
extern void add_json_cache(const char *key, const char *type, const char *value);
extern int32_t create_json_string(char *json_string, uint32_t dataLen);

#if defined(__cplusplus)
}
#endif
#endif // JSON_PARSER_H