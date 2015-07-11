#include "restful.h"

namespace RESTFULLSPACE
{

	RestResponse::RestResponse()
	{

	}

	RestResponse::~RestResponse()
	{
  
	}

	void RestResponse::setResponseData(std::string& value)
	{

	}

	RestRequest::RestRequest():m_jsBody(0)
	{
		m_mapHeader.clear();
		m_strPutBodyData.clear();
		m_strResponseData.clear();
		m_vecHeaders.clear();

		// 添加消息头
		std::string tempStrHeader;

		tempStrHeader.clear();
		tempStrHeader = str_headerMap[HEADER_CONTENT_TYPE] + ":text/html;charset=utf-8";
		m_mapHeader.insert(std::make_pair<HTTP_HEADER_TYPE_E, std::string>(HEADER_CONTENT_TYPE, tempStrHeader));

		tempStrHeader.clear();
		tempStrHeader = str_headerMap[HEADER_CONNECTION] + ":Keep-Alive";
		m_mapHeader.insert(std::make_pair<HTTP_HEADER_TYPE_E, std::string>(HEADER_CONNECTION, tempStrHeader));

		tempStrHeader.clear();
		tempStrHeader = str_headerMap[HEADER_CACHE_CONTROL] + ":no-cache";
		m_mapHeader.insert(std::make_pair<HTTP_HEADER_TYPE_E, std::string>(HEADER_CACHE_CONTROL, tempStrHeader));

		tempStrHeader.clear();
		tempStrHeader = str_headerMap[HEADER_PRAGMA] + ":no-cache";
		m_mapHeader.insert(std::make_pair<HTTP_HEADER_TYPE_E, std::string>(HEADER_ACCEPT_LANGUAGE, tempStrHeader));

	}

	RestRequest::~RestRequest()
	{
		m_mapHeader.clear();
		//m_jsBody;
		m_strPutBodyData.clear();
		m_strResponseData.clear();
		m_vecHeaders.clear();
	}

	void RestRequest::RestInit()
	{
		curl_global_init(CURL_GLOBAL_DEFAULT);		// 初始化libcurl
	}

	void RestRequest::RestUnInit()
	{
		curl_global_cleanup();									//去初始化libcurl
	}

	bool RestRequest::HeaderAddProperty(const HTTP_HEADER_TYPE_E property, const string value)
	{
		return true;
	}

	bool RestRequest::BodyAddProperty(const string name, const string value)
	{
		return true;
	}

	size_t RestRequest::writeRespBodyData(const void* ptr, size_t size, size_t nmemb, void* stream)
	{
		return 0;
	}

	size_t RestRequest::writeRespHeadData(const void* ptr, size_t size, size_t nmemb, void* stream)
	{
		return 0;
	}

	size_t RestRequest::writeRespEmptyHeadData(const void* ptr, size_t size, size_t nmemb, void* stream)
	{
		return 0;
	}

	int RestRequest::SendRequest(
		const string url, 
		const REST_REQUEST_MODE_E requestMode, 
		RestResponse& response, 
		vector<string>& vecHeaders,
		bool isRecvHeader)
	{
		CURL* hCurl = NULL;
		hCurl = curl_easy_init();			// libcurl 初始化curl指针
		if (NULL == hCurl)
		{
			return REST_NULL;
		}

		curl_easy_setopt(hCurl, CURLOPT_URL, url.c_str());	// provide the URL to use in the request
		curl_easy_setopt(hCurl, CURLOPT_SSLVERSION, CURL_SSLVERSION_TLSv1);	// set preferred TLS/SSL version; Attention: Now TLSv1 is much more in security 
		curl_easy_setopt(hCurl, CURLOPT_SSL_VERIFYPEER, 0L); // verify the peer's SSL certificate
		curl_easy_setopt(hCurl, CURLOPT_SSL_VERIFYHOST, 0L); // verify the certificate's name against host
		curl_easy_setopt(hCurl, CURLOPT_HEADER, 0L); // pass headers to the data stream

		// set headers
		struct curl_slist* ptrHeaders = NULL;	// libcurl组装Header的指针，将 headers添加到此结构体
		HeaderMap::iterator iter = m_mapHeader.begin();
		HeaderMap::iterator iterEnd = m_mapHeader.end();
		for ( ; iter != iterEnd; iter++)
		{
			ptrHeaders = curl_slist_append(ptrHeaders, iter->second.c_str());
		}

		int iNum = vecHeaders.size();				// 将额外的headers加入进来
		for (int i=0; i< iNum; i++)
		{
			ptrHeaders = curl_slist_append(ptrHeaders, vecHeaders[i].c_str());		// 此处注意header 的格式，可能需要转换
		}
		curl_easy_setopt(hCurl, CURLOPT_HTTPHEADER, ptrHeaders);

		curl_easy_setopt(hCurl, CURLOPT_WRITEFUNCTION, writeRespBodyData);	// 将返回消息体写入
		curl_easy_setopt(hCurl, CURLOPT_WRITEDATA, this);	// 用该类的对象，来接受消息

		if (isRecvHeader)		// 是否接受返回的消息头
		{
			curl_easy_setopt(hCurl, CURLOPT_HEADERFUNCTION, writeRespHeadData);	// 将返回的消息头写入
		}
		else
		{
			curl_easy_setopt(hCurl, CURLOPT_HEADERFUNCTION, writeRespHeadData);	// 不接受返回的消息头，所以写一个空的消息头
		}
		curl_easy_setopt(hCurl, CURLOPT_WRITEDATA, this);

		// set request mode
		std::string strBodyData;			// put，post请求，附带的body
		strBodyData.clear();

		switch(requestMode)
		{
		case REST_REQUEST_MODE_GET:
			curl_easy_setopt(hCurl, CURLOPT_HTTPGET, 1L);
			break;
		case REST_REQUEST_MODE_POST:
			break;
		case REST_REQUEST_MODE_PUT:
			break;
		case REST_REQUEST_MODE_DELETE:
			break;
		default:
			curl_slist_free_all(ptrHeaders);
			curl_easy_cleanup(hCurl);
			return REST_INVALID_PARAM;
		}

		// set error response
		char errorBuffer[256];
		memset(errorBuffer, 0, 256);
		curl_easy_setopt(hCurl, CURLOPT_ERRORBUFFER, errorBuffer);

		// send the request
		CURLcode res = curl_easy_perform(hCurl);
		if (CURLE_OK != res)
		{
			if(isRecvHeader)
			{

			}

			curl_slist_free_all(ptrHeaders);
			curl_easy_cleanup(hCurl);
			
			return REST_FAIL;
		}
		//set response
		response.setResponseData(m_strResponseData);

		curl_slist_free_all(ptrHeaders);
		curl_easy_cleanup(hCurl);		// libcurl 清除curl指针
		return REST_SUCCESS;
	}
}