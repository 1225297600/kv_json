/********************************************************************************
* @name: kv_json.h
* @author: zhangzhilin
* @description: 1225297600@qq.com
* @version: 1.0
* @date:  2025-4-29
* @brief: The function of JSON decode and encode
********************************************************************************/
#ifndef __KV_JSON_H
#define __KV_JSON_H
#include <stdint.h>
#include <stdbool.h>

/**
 * @brief 格式化 JSON 字符串，保留可打印字符（不包括空格）
 * @param buf 输入的 JSON 字符串缓冲区
 * @param len 缓冲区的长度
 * @return 处理后字符串的长度
 */
uint32_t kv_json_format(char *buf, uint32_t len);


/**
 * @brief 解析 JSON 字符串，并调用回调函数处理每个键值对
 * @param buf 输入的 JSON 字符串缓冲区
 * @param len 缓冲区的长度
 * @param callback 处理键值对的回调函数
 * @return 成功返回 0，失败返回相应的错误码
 * @note 函数会调用kv_json_format，会改变原本buf字符串的内容
 */
int kv_json_decode_poller(char *buf, uint32_t len, int (*callback)(uint16_t index, char *key, uint16_t key_len, char *value, uint16_t value_len));


#endif

/* kv_json.h file end */
