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
#include <stdbool.h>

#if defined(__cplusplus)
extern "C" {
#endif

extern bool string_is_json_object(const char *json_str);


extern int32_t get_int32_from_json(const char *json_str, const char *key);
extern int32_t get_string_from_json(const char *json_str, const char *key, char *data, uint32_t dataLen);
extern int32_t get_object_from_json(const char *json_str, const char *key, char *data, uint32_t dataLen);
extern int32_t get_list_from_json(const char *json_str, const char *key, char *data, uint32_t dataLen);

extern int32_t get_list_size_from_json(const char *json_str, const char *list_key);
extern int32_t get_object_from_list(const char *json_str, const char *list_name, int pos, char *data, uint32_t dataLen);
extern int32_t get_int32_from_list(const char *json_str, const char *list_name, int pos, const char *key);
extern int32_t get_string_from_list(const char *json_str, const char *list_name, int pos, const char *key, char *data, uint32_t dataLen);



extern void *create_json_object();
extern void  add_null_to_object(void *pObj, const char * const key);
extern void  add_bool_to_object(void *pObj, const char * const key, bool bTorF);
extern void  add_number_to_object(void *pObj, const char * const key, double number);
extern void  add_string_to_object(void *pObj, const char * const key, const char * const string);
extern void *add_object_to_object(void *pParentObj, const char * const subObjName);
extern void  add_object_to_object2(void *pParentObj, const char * const subObjName, void *pSubObj);
extern void  add_object_to_object3(void *pParentObj, const char * const subObjName, char *pSubObjSrt);
extern void *create_item_object(const char *contents);
extern void *create_list_object();
extern void  add_item_to_list(void *pList, void *pItem);
extern void *add_list_to_object(void *pParentObj, const char * const listName);
extern void  add_list_to_object2(void *pParentObj, const char * const listName, void *pListObj);
extern char *object_data(void *pObject, bool bIsUnformatted);
extern void  free_data(char *pData);
// 说明：
//     1、该接口类似于free。
//     2、free掉某个JSON对象(含数组对象)的话，挂在它下面的子对象也会全部被free掉。因此只用free掉根节点即可
extern int32_t delete_json_object(void *pObject);

#if defined(__cplusplus)
}
#endif
#endif // JSON_PARSER_H