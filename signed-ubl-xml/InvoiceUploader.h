#pragma once

#include <iostream>
#include <string>

#include <CkHttpRequest.h>
#include <CkHttp.h>
#include <CkHttpResponse.h>

class InvoiceUploader
{
private:
	std::string _pfxPath;
	std::string _pfxPassword;

public:
	InvoiceUploader(const std::string& pfx_path, const std::string& pfx_password);

	bool UploadInvoice(const std::string& invoice_path);
};

