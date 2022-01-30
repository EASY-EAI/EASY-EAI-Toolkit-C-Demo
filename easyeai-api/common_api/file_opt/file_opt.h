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

 
#ifndef FILE_OPT_H
#define FILE_OPT_H

#include <stdbool.h>
#include <stdint.h>


#if defined(__cplusplus)
extern "C" {
#endif

extern bool make_directory(const char *directory);
extern bool add_bias_for_dirpath(char *path);

#if defined(__cplusplus)
}
#endif
#endif // FILE_OPT_H