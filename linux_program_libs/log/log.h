/*
 * =====================================================================================
 *
 *       Filename:  log.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/15/11 18:59:37
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Heaven (), zhanwenhan@163.com
 *        Company:  NDSL
 *
 * =====================================================================================
 */

#ifndef __HVN_LOG_H__
#define __HVN_LOG_H__

#include "Handle_log.h"

#define LOGGING_LEVEL(lvl)  (HVN::Handle_log::get_pinstance()->set_log_level(lvl))
#define LOGGING_TRACE(str)  (HVN::Handle_log::get_pinstance()->log_trace(str, __FILE__, __FUNCTION__, __LINE__))
#define LOGGING_INFO(str)   (HVN::Handle_log::get_pinstance()->log_info(str, __FILE__, __FUNCTION__, __LINE__))
#define LOGGING_WARN(str)   (HVN::Handle_log::get_pinstance()->log_warn(str, __FILE__, __FUNCTION__, __LINE__))
#define LOGGING_ERROR(str)  (HVN::Handle_log::get_pinstance()->log_error(str, __FILE__, __FUNCTION__, __LINE__))
#define LOGGING_FATAL(str)  (HVN::Handle_log::get_pinstance()->log_fatal(str, __FILE__, __FUNCTION__, __LINE__)) 

#endif

