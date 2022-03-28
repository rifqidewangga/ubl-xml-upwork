#include "InvoiceUploader.h"

InvoiceUploader::InvoiceUploader(const std::string& pfx_path, const std::string& pfx_password)
    : _pfxPath(pfx_path), _pfxPassword(pfx_password)
{
}

bool InvoiceUploader::UploadInvoice(const std::string& invoice_path)
{
    //  The ContentType, HttpVerb, and Path properties should
    //  always be explicitly set.
    CkHttpRequest req;
    req.put_HttpVerb("POST");
    req.put_Path("/receiveMyUpload.aspx");
    req.put_ContentType("multipart/form-data");

    bool success = req.AddFileForUpload("invoice.xml", "../Samples/invoice.xml");
    if (success != true) {
        std::cout << req.lastErrorText() << "\r\n";
        return false;
    }

    CkHttp http;

    //  ----------------------------------------------------------------------------
    //  IMPORTANT:
    //  HTTP uploads require a counterpart implementation on the server, written in any desired language
    //  such as C#, Classic ASP, PHP, etc., which consumes the upload being sent.
    //  See: ASP.NET Receive Upload
    //  ----------------------------------------------------------------------------

    success = http.SetSslClientCertPfx(_pfxPath.c_str(), _pfxPassword.c_str());
    if (success != true) {
        std::cout << http.lastErrorText() << "\r\n";
        return false;
    }

    //  Do the upload.
    bool useSslTls = true;
    CkHttpResponse* resp = http.SynchronousRequest("www.example.com", 443, useSslTls, req);
    if (http.get_LastMethodSuccess() != true) {
        std::cout << http.lastErrorText() << "\r\n";
        return false;
    }

    std::cout << "response status code = " << resp->get_StatusCode() << "\r\n";
    std::cout << "response body:" << "\r\n";
    std::cout << resp->bodyStr() << "\r\n";

    delete resp;

    return true;
}
