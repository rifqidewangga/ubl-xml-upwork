#pragma once

#include <format>
#include <sstream>
#include <iomanip>
#include <chrono>

#include <CkXml.h>
#include <CkStringBuilder.h>
#include "Invoice.h"
#include "XMLSigner.h"

class InvoiceGenerator
{
public:
	InvoiceGenerator();
	void Generate(Invoice invoice, std::string filepath);

	std::string GetPIH();
	std::string GetQR();

private:
	CkXml xmlToSign;
	CkXml signedXml;

	std::string PIH = "NWZlY2ViNjZmZmM4NmYzOGQ5NTI3ODZjNmQ2OTZjNzljMmRiYzIzOWRkNGU5MWI0NjcyOWQ3M2EyN2ZiNTdlOQ==";
	std::string lastXmlQR;
	
	std::string GetString(double val);

	void PopulateXml(Invoice invoice);
	void PopulateUBLExt();
	void PopulateSupplierPartyInfo();
	void PopulateCustomerPartyInfo();

	void SaveXmlToSign(std::string path);
	void SaveSignedXml(std::string path);

	void SignXML(std::string filename);
	void UpdateLastQR();
	void UpdatePIH();
};

inline std::tm localtime_xp(std::time_t timer)
{
	std::tm bt{};
#if defined(__unix__)
	localtime_r(&timer, &bt);
#elif defined(_MSC_VER)
	localtime_s(&bt, &timer);
#else
	static std::mutex mtx;
	std::lock_guard<std::mutex> lock(mtx);
	bt = *std::localtime(&timer);
#endif
	return bt;
}

// default = "YYYY-MM-DD HH:MM:SS"
inline std::string time_stamp(const std::string& fmt = "%FT%TZ")
{
	auto bt = localtime_xp(std::time(0));
	char buf[64];
	return { buf, std::strftime(buf, sizeof(buf), fmt.c_str(), &bt) };
}