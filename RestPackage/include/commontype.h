#ifndef _COMMON_TYPE_H_
#define _COMMON_TYPE_H_

#pragma once;
#pragma warning( disable: 4251 )		// 导出类的成员使用STL模板，报warning4251

#ifdef WIN32
#ifdef RESTFUL_EXPORTS
#define RESTFUL_API	__declspec(dllexport)
#else
#define RESTFUL_API __declspec(dllimport)
#endif
#else
#define RESTFUL_API
#endif

namespace RESTFULLSPACE
{
	typedef enum
	{
		HEADER_ACCEPT = 0,
		HEADER_ACCEPT_CHARSET,
		HEADER_ACCEPT_DATETIME,
		HEADER_ACCEPT_ENCODING,
		HEADER_ACCEPT_LANGUAGE,
		HEADER_ACCEPT_RANGES,
		HEADER_AUTHORIZATION,
		HEADER_CACHE_CONTROL,
		HEADER_COOKIE,
		HEADER_CONNECTION,
		HEADER_CONTENT_ENCODING,
		HEADER_CONTENT_LENGTH,
		HEADER_CONTENT_LOCATION,
		HEADER_CONTENT_MD5,
		HEADER_CONTENT_RANGE,
		HEADER_CONTENT_TYPE,
		HEADER_DATE,
		HEADER_ETAG,
		HEADER_EXPECT,
		HEADER_EXPIRES,
		HEADER_FORM,
		HEADER_HOST,
		HEADER_IF_MATCH,
		HEADER_IF_MODIFIED_SINCE,
		HEADER_IF_NONE_MATCH,
		HEADER_IF_RANGE,
		HEADER_IF_UNMODIFIED_SINCE,
		HEADER_LAST_MODIFIED,
		HEADER_LOCATION,
		HEADER_MAX_FORWARDS,
		HEADER_ORIGIN,
		HEADER_PRAGMA,
		HEADER_PROXY_AUTHENTICATE,
		HEADER_PROXY_AUTHORIZATION,
		HEADER_RANGE,
		HEADER_REFERER,
		HEADER_RETRY_AFTER,
		HEADER_SERVER,
		HEADER_TE,
		HEADER_TRAILER,
		HEADER_TRANSFER_ENCODING,
		HEADER_UPGRADE,
		HEADER_USER_AGENT,
		HEADER_VARY,
		HEADER_VIA,
		HEADER_WARNING,
		HEADER_WWW_AUTHENTICATE,
		HEADER_IBASETOKEN,
		HEADER_NULL = 48
	}HTTP_HEADER_TYPE_E;					//Http 消息头

	typedef enum
	{
		REST_REQUEST_MODE_GET = 0,
		REST_REQUEST_MODE_POST,
		REST_REQUEST_MODE_PUT,
		REST_REQUEST_MODE_DELETE
	}REST_REQUEST_MODE_E;	//Rest消息模式

	typedef enum
	{
		REST_SUCCESS =0,
		REST_FAIL,
		REST_INVALID_PARAM,
		REST_NULL = -1
	}REST_RESP_CODE_E;			//Rest返回消息码

	const std::string str_headerMap[HEADER_NULL] = 
	{
		"Accept",
		"Accept-Charset",
		"Accept-Datetime",
		"Accept-Encoding",
		"Accept-Language",
		"Accept-Ranges",
		"Authorization",
		"Cache-Control",
		"Cookie",
		"Connection",
		"Content-Encoding",
		"Content-Length",
		"Content-Location",
		"Content-MD5",
		"Content-Range",
		"Contern-Type",
		"Date",
		"ETag",
		"Expect",
		"Expires",
		"Form",
		"Host",
		"If-Match",
		"If-Modified-Since",
		"If-None-Match",
		"If-Range",
		"If-Unmodified-Since",
		"Last-Modified",
		"Location",
		"Max-Forwards",
		"Origin",
		"Pragma",
		"Proxy-Authenticate",
		"Proxy-Authorization",
		"Range",
		"Referer",
		"Retry-After",
		"Server",
		"TE",
		"Trailer",
		"Transfer-Encoding",
		"Upgrade",
		"User-Agent",
		"Vary",
		"Via",
		"Warning",
		"www-Authenticate",
		"iBaseToken"
	};

}

#endif