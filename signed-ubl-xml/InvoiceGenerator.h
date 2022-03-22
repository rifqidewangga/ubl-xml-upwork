#pragma once

#include <sstream>
#include <iomanip>
#include <chrono>
#include <fstream>
#include <iostream>

#include <CkXml.h>
#include <CkStringBuilder.h>
#include "Invoice.h"
#include "XMLSigner.h"

#define PIH_TEMP_FILENAME "pih.txt"

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

	std::string lastXmlQR;
	
	std::string GetString(double val);

	void PopulateXml(Invoice invoice);

	void CheckInvoiceType(Invoice invoice);
	void InitializeEmptyXml();
	void PopulateUBLExt(Invoice invoice);
	void PopulateBasicInfo(Invoice invoice);
	void PopulateDocumentReferences(Invoice invoice);
	void PopulateSupplierPartyInfo();
	void PopulateCustomerPartyInfo(Invoice invoice);
	void PopulateDeliveryDate(Invoice invoice);
	void PopulatePatmentMeans(Invoice invoice);
	void PopulateTaxTotal(Invoice invoice);
	void PopulateLegalMonetaryTotal(Invoice invoice);
	void PopulateInvoiceLines(Invoice invoice);

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

inline std::string time_stamp(const std::string& fmt = "%FT%TZ")
{
	auto bt = localtime_xp(std::time(0));
	char buf[64];
	return { buf, std::strftime(buf, sizeof(buf), fmt.c_str(), &bt) };
}