#include "restful.h"

namespace RESTFULLSPACE
{

	RestResponse::RestResponse()
	{

	}

	RestResponse::~RestResponse()
	{

	}

	RestRequest::RestRequest()
	{

	}

	RestRequest::~RestRequest()
	{

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

	int RestRequest::SendRequest(
		const string url, 
		const REST_REQUEST_MODE_E mode, 
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

		curl_easy_setopt(hCurl, CURLOPT_URL, url.c_str());	//provide the URL to use in the request
		curl_easy_setopt(hCurl, CURLOPT_SSLVERSION, CURL_SSLVERSION_TLSv1);	//set preferred TLS/SSL version; Attention: Now TLSv1 is much more in security 
		curl_easy_setopt(hCurl, CURLOPT_SSL_VERIFYPEER, 0L); //verify the peer's SSL certificate
		curl_easy_setopt(hCurl, CURLOPT_SSL_VERIFYHOST, 0L); //verify the certificate's name against host
		curl_easy_setopt(hCurl, CURLOPT_HEADER, 0L); //pass headers to the data stream


	

		curl_easy_cleanup(hCurl);		// libcurl 清除curl指针
		return REST_SUCCESS;
	}
}