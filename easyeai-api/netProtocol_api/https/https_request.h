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
 
#ifndef HTTPS_REQUEST_H
#define HTTPS_REQUEST_H

#include <stdint.h>

#define CA_CERT_FILE "/etc/ca-bundle.crt"

#if defined(__cplusplus)
extern "C" {
#endif

extern void set_customer_crt(const char *crt_file);
extern void clear_multipart();
extern void add_multipart_form_data(const char *key, const char *value);
extern int32_t send_data_to_Https(const char *server, const char *func, char *result, uint32_t result_length);
extern int32_t send_data_to_Http(const char *server, const char *func, char *result, uint32_t result_length);
extern int32_t send_json_to_Https(const char *server, const char *func, const char *json, char *result, uint32_t result_length);
extern int32_t send_json_to_Http(const char *server, const char *func, const char *json, char *result, uint32_t result_length);
extern int32_t get_file_from_https(const char *url, const char *func, const char *filePath);
extern int32_t get_file_from_http(const char *url, const char *func, const char *filePath);

#if defined(__cplusplus)
}
#endif
#endif // HTTPS_REQUEST_H
